/*******************************************************************************
 * This example sends a valid LoRaWAN packet with sensed data by HX711 sensor,
 * using frequency and encryption settings matching those of
 * The Things Network.
 *
 * Note: LoRaWAN per sub-band duty-cycle limitation is enforced (1% in g1,
 *  0.1% in g2).
 *
 * Required Library: 
 *    * https://github.com/matthijskooijman/arduino-lmic 
 *    * https://github.com/bogde/HX711
 * 
 * Require Hardware:
 *    * HX711 sensor 
 *    * LoRa Shield + Arduino UNO   
 *    * Dragino LG01 gateway. 
 *******************************************************************************/

#include <lmic.h>
#include <hal/hal.h>
#include <SPI.h>
#include <String.h>
#include <math.h>
#include "HX711.h"

// LoRaWAN NwkSKey, network session key
// This is the default Semtech key, which is used by the prototype TTN
// network initially.
//ttn
static const PROGMEM u1_t NWKSKEY[16] = { 0x0C, 0xD7, 0xCE, 0xBC, 0x2F, 0x3A, 0xF4, 0xE1, 0x13, 0x27, 0x93, 0xE0, 0x04, 0x46, 0x62, 0x55 };

// LoRaWAN AppSKey, application session key
// This is the default Semtech key, which is used by the prototype TTN
// network initially.
//ttn
static const u1_t PROGMEM APPSKEY[16] =  { 0xFD, 0x0C, 0xB8, 0x32, 0x32, 0x4B, 0xAC, 0x00, 0xEF, 0x31, 0xCF, 0xA1, 0x52, 0xDE, 0x0B, 0x9C };

// LoRaWAN end-device address (DevAddr)
// ttn
static const u4_t DEVADDR = 0x260112AC;


// These callbacks are only used in over-the-air activation, so they are
// left empty here (we cannot leave them out completely unless
// DISABLE_JOIN is set in config.h, otherwise the linker will complain).
void os_getArtEui (u1_t* buf) { }
void os_getDevEui (u1_t* buf) { }
void os_getDevKey (u1_t* buf) { }

static osjob_t initjob,sendjob,blinkjob;
float Weight = 0; //the weight value of the object sensed by HX711

// Schedule TX every this many seconds (might become longer due to duty
// cycle limitations).
const unsigned TX_INTERVAL = 20; //duty cycle,i.e., the time interval for the uplink transmission of sensed data

// Pin mapping
const lmic_pinmap lmic_pins = {
    .nss = 10,
    .rxtx = LMIC_UNUSED_PIN,
    .rst = 9,
    .dio = {2, 6, 7},
};
void do_send(osjob_t* j){
    // Check if there is not a current TX/RX job running
    if (LMIC.opmode & OP_TXRXPEND) {
        Serial.println("OP_TXRXPEND, not sending");
    } else {
        // Prepare upstream data transmission at the next possible time.
        Weight = Get_Weight();  //calculate the weight value
        Weight = float(Weight/1000); //unit: kg
        char hx711_data[8]={0}; //store the weight value
        int i,j,k;
        for(i = 0; i<4; i++){
          hx711_data[i] = int(Weight*pow(10,i))%10+48; //transform int value to char value
        }
        for(j = i; j>0; j--){
          hx711_data[j+1] = hx711_data[j];  
        }
        hx711_data[j+1] = '.'; //add the decimal point for the float value
        k = strlen(hx711_data);
        hx711_data[k+1] = 'k'; //add the numerical unit
        hx711_data[k+2] = 'g';
        LMIC_setTxData2(1, hx711_data, strlen(hx711_data), 0); //send the sensed data to the gateway
        Serial.println("Packet queued");
        Serial.println(LMIC.freq);
    }
    // Next TX is scheduled after TX_COMPLETE event.
}

void onEvent (ev_t ev) {
    Serial.print(os_getTime());
    Serial.print(": ");
    Serial.println(ev);
    switch(ev) {
        case EV_SCAN_TIMEOUT:
            Serial.println("EV_SCAN_TIMEOUT");
            break;
        case EV_BEACON_FOUND:
            Serial.println("EV_BEACON_FOUND");
            break;
        case EV_BEACON_MISSED:
            Serial.println("EV_BEACON_MISSED");
            break;
        case EV_BEACON_TRACKED:
            Serial.println("EV_BEACON_TRACKED");
            break;
        case EV_JOINING:
            Serial.println("EV_JOINING");
            break;
        case EV_JOINED:
            Serial.println("EV_JOINED");
            break;
        case EV_RFU1:
            Serial.println("EV_RFU1");
            break;
        case EV_JOIN_FAILED:
            Serial.println("EV_JOIN_FAILED");
            break;
        case EV_REJOIN_FAILED:
            Serial.println("EV_REJOIN_FAILED");
            break;
        case EV_TXCOMPLETE:
            Serial.println("EV_TXCOMPLETE (includes waiting for RX windows)");
            if(LMIC.dataLen) {
                // data received in rx slot after tx
                Serial.print("Data Received: ");
                Serial.write(LMIC.frame+LMIC.dataBeg, LMIC.dataLen);
                Serial.println();
            }
            // Schedule next transmission
            os_setTimedCallback(&sendjob, os_getTime()+sec2osticks(TX_INTERVAL), do_send); 
            break;
        case EV_LOST_TSYNC:
            Serial.println("EV_LOST_TSYNC");
            break;
        case EV_RESET:
            Serial.println("EV_RESET");
            break;
        case EV_RXCOMPLETE:
            // data received in ping slot
            Serial.println("EV_RXCOMPLETE");
            break;
        case EV_LINK_DEAD:
            Serial.println("EV_LINK_DEAD");
            break;
        case EV_LINK_ALIVE:
            Serial.println("EV_LINK_ALIVE");
            break;
         default:
            Serial.println("Unknown event");
            break;
    }
}

void setup() {
    Serial.begin(9600);
    while(!Serial);
    Serial.println("Starting");
    #ifdef VCC_ENABLE
    // For Pinoccio Scout boards
    pinMode(VCC_ENABLE, OUTPUT);
    digitalWrite(VCC_ENABLE, HIGH);
    delay(1000);
    #endif

    // LMIC init
    os_init();
    // Reset the MAC state. Session and pending data transfers will be discarded.
    LMIC_reset();
    //LMIC_setClockError(MAX_CLOCK_ERROR * 1/100);
    // Set static session parameters. Instead of dynamically establishing a session
    // by joining the network, precomputed session parameters are be provided.
    #ifdef PROGMEM
    // On AVR, these values are stored in flash and only copied to RAM
    // once. Copy them to a temporary buffer here, LMIC_setSession will
    // copy them into a buffer of its own again.
    uint8_t appskey[sizeof(APPSKEY)];
    uint8_t nwkskey[sizeof(NWKSKEY)];
    memcpy_P(appskey, APPSKEY, sizeof(APPSKEY));
    memcpy_P(nwkskey, NWKSKEY, sizeof(NWKSKEY));
    LMIC_setSession (0x1, DEVADDR, nwkskey, appskey);
    #else
    // If not running an AVR with PROGMEM, just use the arrays directly 
    LMIC_setSession (0x1, DEVADDR, NWKSKEY, APPSKEY);
    #endif
    
    // Disable link check validation
    LMIC_setLinkCheckMode(0);

    // TTN uses SF9 for its RX2 window.
    LMIC.dn2Dr = DR_SF9;
    
    // Set data rate and transmit power (note: txpow seems to be ignored by the library)
    LMIC_setDrTxpow(DR_SF7,14);
    LMIC.freq = 433000000;  // Tx frequency setting

    Init_Hx711(); //initialize the HX711 module
    Get_Maopi();    //calibration the values of HX711
    Serial.println("Weight Measurement\n");
    // Start job
    do_send(&sendjob);
}

void loop() {
    os_runloop_once();
}



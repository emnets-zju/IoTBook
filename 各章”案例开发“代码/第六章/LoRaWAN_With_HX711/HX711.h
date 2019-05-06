#ifndef __HX711__H__
#define __HX711__H__

#include <Arduino.h>
#include <SPI.h>
#include <RH_RF95.h>

//the connections for HX711 and LoRa Shield
#define HX711_SCK 4
#define HX711_DT 3 

extern void Init_Hx711();
extern unsigned long HX711_Read(void);
extern long Get_Weight();
extern void Get_Maopi();

#endif

# -*- coding: utf-8 -*-
import time
import sys
import iothub_client
from iothub_client import IoTHubClient, IoTHubClientError, IoTHubTransportProvider, IoTHubClientResult
from iothub_client import IoTHubMessage, IoTHubMessageDispositionResult, IoTHubError
# Using grovepi lib to enable shield
import grovepi
# Chainable LED setting
pin = 7
numleds = 1
grovepi.pinMode(pin,"OUTPUT")
time.sleep(1)
## test colors used in grovepi.chainableRgbLed_test()
testColorBlack = 0   # 0b000 #000000
testColorWhite = 7   # 0b111 #FFFFFF
# patterns used in grovepi.chainableRgbLed_pattern()
thisLedOnly = 0
allLedsExceptThis = 1
thisLedAndInwards = 2
thisLedAndOutwards = 3

RECEIVE_CONTEXT = 0
WAIT_COUNT = 10
RECEIVED_COUNT = 0
RECEIVE_CALLBACKS = 0
# config of Azure SDK
PROTOCOL = IoTHubTransportProvider.MQTT
CONNECTION_STRING = "HostName=VoiceLED.azure-devices.net;DeviceId=LED;SharedAccessKey=bA3gAxN9daAFy5fXZ5vFE+Tck6HjqRdy2mGWRp/tmPs="

def receive_message_callback(message, counter):
    global RECEIVED_COUNT
    global RECEIVE_CALLBACKS
    message_buffer = message.get_bytearray()
    size = len(message_buffer)
    print ( "Received Message [%d]:" % RECEIVED_COUNT  )
    msg_data = message_buffer[:size].decode('utf-8') # 收到的信息
    print("Recieved control order: %s" % msg_data)
    print(time.strftime('%Y-%m-%d %H:%M:%S',time.localtime(time.time())))
    if msg_data == "open":
        grovepi.chainableRgbLed_test(pin, numleds, testColorWhite)
    elif msg_data == "close":
        grovepi.chainableRgbLed_test(pin, numleds, testColorBlack)
    else:
        print("Do nothing!")
    RECEIVED_COUNT += 1
    RECEIVE_CALLBACKS += 1
    print ( "    Total calls received: %d" % RECEIVE_CALLBACKS )
    print ("    Command: %s" % msg_data[7:-1])
    return IoTHubMessageDispositionResult.ACCEPTED

def iothub_client_init():
    client = IoTHubClient(CONNECTION_STRING, PROTOCOL)
    client.set_message_callback(receive_message_callback, RECEIVE_CONTEXT)
    return client

def print_last_message_time(client):
    try:
        last_message = client.get_last_message_receive_time()
        print ( "Last Message: %s" % time.asctime(time.localtime(last_message)) )
        print ( "Actual time : %s" % time.asctime() )
    except IoTHubClientError as iothub_client_error:
        if iothub_client_error.args[0].result == IoTHubClientResult.INDEFINITE_TIME:
            print ( "No message received" )
        else:
            print ( iothub_client_error )


def iothub_client_init():
    client = IoTHubClient(CONNECTION_STRING, PROTOCOL)
    client.set_message_callback(receive_message_callback, RECEIVE_CONTEXT)
    return client

def iothub_client_sample_run():
    try:
        client = iothub_client_init()
        while True:
            print ( "IoTHubClient waiting for commands, press Ctrl-C to exit" )
            status_counter = 0
            while status_counter <= WAIT_COUNT:
                status = client.get_send_status()
                print ( "Send status: %s" % status )
                time.sleep(10)
                status_counter += 1

    except IoTHubError as iothub_error:
        print ( "Unexpected error %s from IoTHub" % iothub_error )
        return
    except KeyboardInterrupt:
        print ( "IoTHubClient sample stopped" )
    print_last_message_time(client)

if __name__ == '__main__':
    print ( "Starting the IoT Hub Python sample..." )
    print ( "    Protocol %s" % PROTOCOL )
    print ( "    Connection string=%s" % CONNECTION_STRING )
    iothub_client_sample_run()
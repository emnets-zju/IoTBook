# Copyright (c) Microsoft. All rights reserved.
# Licensed under the MIT license. See LICENSE file in the project root for full license information.

import random
import time
import sys

# Using the Python Device SDK for IoT Hub:
#   https://github.com/Azure/azure-iot-sdk-python
# The sample connects to a device-specific MQTT endpoint on your IoT Hub.
import iothub_client
# pylint: disable=E0611
from iothub_client import IoTHubClient, IoTHubClientError, IoTHubTransportProvider, IoTHubClientResult
from iothub_client import IoTHubMessage, IoTHubMessageDispositionResult, IoTHubError, DeviceMethodReturnValue

# Using grovepi lib to enable shield
import grovepi

# Chainable LED setting
pin = 7
numleds = 1
grovepi.pinMode(pin,"OUTPUT")
time.sleep(1)
## test colors used in grovepi.chainableRgbLed_test()
testColorBlack = 0   # 0b000 #000000
testColorBlue = 1    # 0b001 #0000FF
testColorGreen = 2   # 0b010 #00FF00
testColorCyan = 3    # 0b011 #00FFFF
testColorRed = 4     # 0b100 #FF0000
testColorMagenta = 5 # 0b101 #FF00FF
testColorYellow = 6  # 0b110 #FFFF00
testColorWhite = 7   # 0b111 #FFFFFF

# patterns used in grovepi.chainableRgbLed_pattern()
thisLedOnly = 0
allLedsExceptThis = 1
thisLedAndInwards = 2
thisLedAndOutwards = 3

# try:

#     print("Test 1) Initialise")

#     # init chain of leds
#     grovepi.chainableRgbLed_init(pin, numleds)
#     time.sleep(.5)

#     # change color to green
#     grovepi.storeColor(0,255,0)
#     time.sleep(.5)

#     # set led 1 to green
#     grovepi.chainableRgbLed_pattern(pin, thisLedOnly, 0)
#     time.sleep(.5)

#     # change color to red
#     grovepi.storeColor(255,0,0)
#     time.sleep(.5)

#     # set led 10 to red
#     grovepi.chainableRgbLed_pattern(pin, thisLedOnly, 9)
#     time.sleep(.5)

#     # pause so you can see what happened
#     time.sleep(2)

#     # reset (all off)
#     grovepi.chainableRgbLed_test(pin, numleds, testColorBlack)
#     time.sleep(.5)
#         print ("Test 2a) Test Patterns - black")

#     # test pattern 0 - black (all off)
#     grovepi.chainableRgbLed_test(pin, numleds, testColorBlack)
#     time.sleep(1)


#     print ("Test 2b) Test Patterns - blue")

#     # test pattern 1 blue
#     grovepi.chainableRgbLed_test(pin, numleds, testColorBlue)
#     time.sleep(1)


#     print ("Test 2c) Test Patterns - green")

#     # test pattern 2 green
#     grovepi.chainableRgbLed_test(pin, numleds, testColorGreen)
#     time.sleep(1)


#     print ("Test 2d) Test Patterns - cyan")

#     # test pattern 3 cyan
#     grovepi.chainableRgbLed_test(pin, numleds, testColorCyan)
#     time.sleep(1)


#     print ("Test 2e) Test Patterns - red")

#     # test pattern 4 red
#     grovepi.chainableRgbLed_test(pin, numleds, testColorRed)
#     time.sleep(1)
#     print ("Test 2f) Test Patterns - magenta")

#     # test pattern 5 magenta
#     grovepi.chainableRgbLed_test(pin, numleds, testColorMagenta)
#     time.sleep(1)


#     print ("Test 2g) Test Patterns - yellow")

#     # test pattern 6 yellow
#     grovepi.chainableRgbLed_test(pin, numleds, testColorYellow)
#     time.sleep(1)


    # print ("Test 2h) Test Patterns - white")

    # # test pattern 7 white
    # grovepi.chainableRgbLed_test(pin, numleds, testColorWhite)
    # time.sleep(1)


    # # pause so you can see what happened
    # time.sleep(2)

    # # reset (all off)
    # grovepi.chainableRgbLed_test(pin, numleds, testColorBlack)
    # time.sleep(.5)
# The device connection string to authenticate the device with your IoT hub.
# Using the Azure CLI:
# az iot hub device-identity show-connection-string --hub-name {YourIoTHubName} --device-id MyNodeDevice --output table
CONNECTION_STRING = "HostName=VoiceLED.azure-devices.net;DeviceId=LED;SharedAccessKey=bA3gAxN9daAFy5fXZ5vFE+Tck6HjqRdy2mGWRp/tmPs="

# Using the MQTT protocol.
PROTOCOL = IoTHubTransportProvider.MQTT
MESSAGE_TIMEOUT = 10000

# Define the JSON message to send to IoT Hub.
TEMPERATURE = 20.0
HUMIDITY = 60
MSG_TXT = "{\"temperature\": %.2f,\"humidity\": %.2f}"

INTERVAL = 1

def send_confirmation_callback(message, result, user_context):
    print ( "IoT Hub responded to message with status: %s" % (result) )

def iothub_client_init():
    # Create an IoT Hub client
    client = IoTHubClient(CONNECTION_STRING, PROTOCOL)
    return client

# Handle direct method calls from IoT Hub
def device_method_callback(method_name, payload, user_context):
    global INTERVAL
    print ( "\nMethod callback called with:\nmethodName = %s\npayload = %s" % (method_name, payload) )
    device_method_return_value = DeviceMethodReturnValue()
    if method_name == "SetLED":
        try:
            #INTERVAL = int(payload)
            if(int(payload)  == 1):
                grovepi.chainableRgbLed_test(pin, numleds, testColorWhite)
                time.sleep(1)
            elif(int(payload) == 0):
                grovepi.chainableRgbLed_test(pin, numleds, testColorBlack)
                time.sleep(1)
            # Build and send the acknowledgment.
            device_method_return_value.response = "{ \"Response\": \"Executed direct method %s\" }" % method_name
            device_method_return_value.status = 200
        except ValueError:
            # Build and send an error response.
            device_method_return_value.response = "{ \"Response\": \"Invalid parameter\" }"
            device_method_return_value.status = 400
    else:
        # Build and send an error response.
        device_method_return_value.response = "{ \"Response\": \"Direct method not defined: %s\" }" % method_name
        device_method_return_value.status = 404
    return device_method_return_value

def iothub_client_telemetry_sample_run():

    try:
        client = iothub_client_init()
        print ( "IoT Hub device sending periodic messages, press Ctrl-C to exit" )

        # Set up the callback method for direct method calls from the hub.
        client.set_device_method_callback(
            device_method_callback, None)

        while True:
            # # Build the message with simulated telemetry values.
            # temperature = TEMPERATURE + (random.random() * 15)
            # humidity = HUMIDITY + (random.random() * 20)
            # msg_txt_formatted = MSG_TXT % (temperature, humidity)
            # message = IoTHubMessage(msg_txt_formatted)

            # # Add a custom application property to the message.
            # # An IoT hub can filter on these properties without access to the message body.
            # prop_map = message.properties()
            # if temperature > 30:
            #   prop_map.add("temperatureAlert", "true")
            # else:
            #   prop_map.add("temperatureAlert", "false")

            # # Send the message.
            # print( "Sending message: %s" % message.get_string() )
            # client.send_event_async(message, send_confirmation_callback, None)
            time.sleep(INTERVAL)

    except IoTHubError as iothub_error:
        print ( "Unexpected error %s from IoTHub" % iothub_error )
        return
    except KeyboardInterrupt:
        print ( "IoTHubClient sample stopped" )

if __name__ == '__main__':
    print ( "IoT Hub Quickstart #2 - Simulated device" )
    print ( "Press Ctrl-C to exit" )
    iothub_client_telemetry_sample_run()
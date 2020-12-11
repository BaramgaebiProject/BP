import time
import serial
import string
import pynmea2
import RPi.GPIO as gpio

gpio.setmode(gpio.BCM) # maybe for LCD

#ser = serial.Serial(port='/dev/ttyAMA0', baudrate=9600, timeout=10)
while 1:
    ser = serial.Serial(port='/dev/ttyAMA0', baudrate=9600, timeout=10)
    try:
        data = ser.readline()
    except:
        print("loading")
        #wait for the serial port to churn out data
    time.sleep(0.1)

    if data[0:6] == '$GPGGA': # the long and lat data are always contained in the GPGGA string $
        msg = pynmea2.parse(data)
        latval = float(msg.lat)
        longval = float(msg.lon)
        altval = float(msg.altitude)
         
    time.sleep(0.5) #wait a little before picking the next data.




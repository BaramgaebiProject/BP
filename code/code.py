# importing
import time
import socket
import serial
import string
import pynmea2

# program init
inited_program = false

host=''
port=9000
locaddr=(host,port)

# try init
for(int i = 0; i < 10000; i++):
    try:
        sock=socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
        tello_address=('192.168.10.1',8889)
        sock.bind(locaddr)

        GPS = serial.Serial(port='/dev/ttyAMA0', baudrate=9600, timeout=10)
        time.sleep(2)
        
        Arduino = serial.Serial(port='com3', baudrate=9600, timeout=None)
        time.sleep(2)
        
        inited_program = true
        break
    except:
        time.sleep(0.01)
        continue

# if not inited then program exit
if(!inited_program):
    return

########################################################################
##                            funtions                                ##
########################################################################

# turn on drone
def drone(s):
    sock.sendto(s.encode(encoding="utf-8"),tello_address)

# gps read
def drone_loc():
    while(true):
        data = GPS.readline()
        if (data[0:6] == '$GPGGA'):
            val = pynmea2.parse(data)
            return [float(val.lat), float(val.lon), float(val.altitude)]
        
# check
def check():
    # tag card
    Arduino.wirte("CHECKID".encode())
    while(true):
        if(Arduino.in_waiting != 0):
            return_val = Arduino.readline()
            if(return_val[0] == 'N'):
                customer = return_val[1]
                break
            
    # turn on camera
    drone('streamon')
    time.sleep(0.5)
    checking = input("Same man/woman?: (Yes:0, No:1) ")
    if(checking == 0):
        Arduino.wirte("VOTE".encode())
        while(true):
            if(Arduino.in_waiting != 0):
                if(Arduino.readline() == 'N'):
                    break
                
    # turn off camera
    drone('streamoff')
    time.sleep(0.5)
    return

#########################################################################

# drone setting   
drone('command')
time.sleep(0.05)

# get target location
file = opne("./target.txt", 'r')
postions = file.readlines()
file.close()

# drone takeoff
drone('takeoff')
time.sleep(1)
Arduino.write("MOVE".encode())

# drone goes to customer
for(int i = 0; i < postions.size(); i++):
    target = postions[i]
    while(true):
        drone_pos = drone_loc()
        vector = [target[0]-drone_pos[0], target[1]-drone_pos[1], target[2]-drone_pos[2]]

        # drone arrives at customer
        if(vector[0] ** 2 + vector[1] ** 2 + vector[2] ** 2 < 50):
            drone('land')
            time.sleep(1)
            check()
            time.sleep(1)
            drone('takeoff')
            time.sleep(1)
            Arduino.write("MOVE".encode())
            break
        
        # meet hurdle
        if(Arduino.in_waiting != 0):
            if(Arduino.readline() != None):
                if(Arduino.readline()=="goUp"):
                    drone('up 500')
                if(Arduino.readline()=="goDown"):
                    drone('down 500')
                if(Arduino.readline()=="turnLeft"):
                    drone('ccw 90')
                if(Arduino.readline()=="turnRight"):
                    drone('cw 90')
                
        # go to customer
        drone("go %f %f %f 20" %(vecor[0], vecor[1], vector[2]))
        time.sleep(0.05)



        

    
        

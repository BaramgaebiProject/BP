import socket, time

host=''
port=9000
locaddr=(host,port)

sock=socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
tello_address=('192.168.10.1',8889)
sock.bind(locaddr)

def drone(a):
    sock.sendto(a.encode(encoding="utf-8"),tello_address)

drone('command')
time.sleep(3)

drone('takeoff')
time.sleep(3)

if utrSnc1 >500:
    
if utrSnc2 >500:
    
if utrSnc3 >500:
    
if utrSnc4 >500:
    
if utrSnc5 >500:
    
if utrSnc6 >500:


drone('land')
time.sleep(3)

import socket
import time

MAX_BUFFER_SIZE = 1024
HOST = "localhost"
PORT = 9045
data = "merrrrrrrr"

#creates a IPV4 based UDP socket
try:
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    print "UDP socket created"
except socket.error, msg:
    print "Failed to create socket. Error code: " + str(msg[0]) + " Message " + msg[1]

try:
    s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    s.bind((HOST, PORT))
    print "Bind complete"
except socket.error, msg:
    print "Bind failed. Error code: " + str(msg[1])

while 1:
    d = s.recvfrom(MAX_BUFFER_SIZE)
    data = d[0]
    addr = d[1]

    reply = "ok..." + data
    
    s.sendto(reply, addr)
    print "Message[" + addr[0] + ":" + str(addr[1]) + "] - " + data.strip()

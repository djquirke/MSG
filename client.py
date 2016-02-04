import socket

HOST = "localhost"
PORT = 6969

try:
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
except socket.error:
    print "Failed to create socket"

#s.bind((HOST, PORT))

while 1:
    msg = raw_input("Enter message to send: ")

    try:
        s.sendto(msg, (HOST, PORT))

        d = s.recv(1024)
        reply = d[1]
        addr = d[1]

        print "Server reply: " + d

    except socket.error, msg:
        print "Error code: " + str(msg[0]) + " Message " + msg[1]

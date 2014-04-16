#!/usr/bin/python
import socket
import sys, time

if sys.argv[1] == "-help":
    print "test.py [PORT#] [NO. of packages to send]"
    exit(); 

UDP_IP = ["128.10.12.211","128.10.12.212","128.10.12.213","128.10.12.214","128.10.12.215","128.10.12.216"]
UDP_PORT = int(sys.argv[1])
MESSAGE = "Hello, World!"

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) 

for CUR_IP in UDP_IP:
    for x in range(0, int(sys.argv[2])):
        sock.sendto(MESSAGE, (CUR_IP, UDP_PORT))



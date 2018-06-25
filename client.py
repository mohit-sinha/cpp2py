import socket
import numpy as np
#import cv2

host = '127.0.0.1'
port = 8889
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((host, port))

f = open("new.jpg", "wb")
veri = s.recv(4)
print(veri)

while True:
	veri = s.recv(255)
	if not veri:
		break
	f.write(veri)

f.close()
s.close()



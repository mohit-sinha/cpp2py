import socket
import numpy as np

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


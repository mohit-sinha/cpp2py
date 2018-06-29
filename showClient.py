import socket
import numpy as np
import cv2
from PIL import Image
from io import BytesIO
import os
import time

host = '127.0.0.1'
port = 8889
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((host, port))

size = int.from_bytes(s.recv(4), byteorder='little')
print(size)

f = open("image.jpg", "wb")

start = time.time()
# img1 = BytesIO(s.recv(size))
# img2 = Image.open(img1)
# image = np.array(img2)
# image = image[:,:,::-1]
image = cv2.imdecode(s.recv(size), 1);
print(time.time()-start)

cv2.imshow("hey", image)
cv2.waitKey(0)
cv2.destroyAllWindows()
f.close()
os.remove("image.jpg")
s.close()

start2 = time.time()
cv2.imread('vkohli.jpg')
print(time.time() - start2)


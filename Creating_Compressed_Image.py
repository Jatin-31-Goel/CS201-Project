import cv2 as cv
import numpy as py
a = 0
b = 0
i = 0

image = cv.imread("to.jpeg",0)

total = image.shape
rows = total[0]
columns = total[1]

with open("pix_1.txt") as handle :
    for line in handle :
        line = line.strip()
        if(b == columns):
            b = 0
            a = a+1
        image[a][b] = int(line)
        b = b+1

cv.imshow("Image_1",image)
cv.waitKey(0)
import cv2 as cv
import numpy as py

image = cv.imread("to.jpeg",0)

total = image.shape

rows = total[0]
columns = total[1]

image1 = cv.resize(image, (500,500))

file = open("pix.txt", 'w')

entry = str(columns) + '\n'
file.write(entry)
entry = str(rows) + '\n'
file.write(entry)

for i in range(0, rows) :
    for j in range(0, columns) :
        entry = str(image[i][j]) + '\n'
        file.write(entry)

cv.imshow("Image_1", image)
cv.waitKey(0)

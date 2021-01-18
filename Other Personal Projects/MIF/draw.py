from PIL import Image
import sys
import os
import time

if (sys.argv<=2):
    print('Please Input the pramenter argument')
    exit()

datFile = sys.argv[1]
imgFile = sys.argv[2]
dotSize = 6

f = open(datFile,'r')
img = Image.new("RGB",(1000,1100))

for i in range(0,999):
    for j in range(0,1099):
        img.putpixel([i,j],(255,255,255))

for line in f:
    xy = line.split()
    x = float(xy[0])
    y = float(xy[1])

    for i in range(-dotSize/2,dotSize/2):
        for j in range(-dotSize/2,dotSize/2):
                img.putpixel([int((x-116.38)*10000)+i,1100-int((y-39.87)*10000)+j],(255,0,0))
                img.putpixel([int((x-116.38)*10000)+i+dotSize,1100-int((y-39.87)*10000)+j],(255,0,0))
                img.putpixel([int((x-116.38)*10000)+i-dotSize,1100-int((y-39.87)*10000)+j],(255,0,0))
                img.putpixel([int((x-116.38)*10000)+i,1100-int((y-39.87)*10000)+j+dotSize],(255,0,0))
                img.putpixel([int((x-116.38)*10000)+i,1100-int((y-39.87)*10000)+j-dotSize],(255,0,0))
    # img.save('draw.png')
    # input()
f.close()
img.save(imgFile)
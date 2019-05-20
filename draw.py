from PIL import Image
import os
import time

mifFile = './data/A.mif'
imgFile = './A.png'
f = open(mifFile,'r')
img = Image.new("RGB",(1000,1100))
for i in range(0,999):
    for j in range(0,1099):
        img.putpixel([i,j],(255,255,255))
for line in f:
    xy = line.split(' ')
    x = float(xy[0])
    y = float(xy[1])
    print (int((x-116.38)*10000))
    print (int((y-39.87)*10000))
    img.putpixel([int((x-116.38)*10000),1100-int((y-39.87)*10000)],(255,0,0))
    # Extend
    img.putpixel([int((x-116.38)*10000)-1,1100-int((y-39.87)*10000)-1],(255,0,0))
    img.putpixel([int((x-116.38)*10000)+1,1100-int((y-39.87)*10000)-1],(255,0,0))
    img.putpixel([int((x-116.38)*10000)-1,1100-int((y-39.87)*10000)+1],(255,0,0))
    img.putpixel([int((x-116.38)*10000)+1,1100-int((y-39.87)*10000)+1],(255,0,0))
    img.putpixel([int((x-116.38)*10000)-1,1100-int((y-39.87)*10000)],(255,0,0))
    img.putpixel([int((x-116.38)*10000)+1,1100-int((y-39.87)*10000)],(255,0,0))
    img.putpixel([int((x-116.38)*10000),1100-int((y-39.87)*10000)+1],(255,0,0))
    img.putpixel([int((x-116.38)*10000),1100-int((y-39.87)*10000)-1],(255,0,0))
    # img.save('draw.png')
    # input()
f.close()
img.save(imgFile)
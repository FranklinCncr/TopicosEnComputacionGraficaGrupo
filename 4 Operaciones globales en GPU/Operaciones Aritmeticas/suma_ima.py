import cv2 as cv
import sys
import numpy as np

img2 = cv.imread(cv.samples.findFile("poesia.bmp"),1)
img = cv.imread(cv.samples.findFile("poesia_2.bmp"),1)

nueva_imagen=img+img2
cv.imwrite("suma_resultado_py.bmp",nueva_imagen)

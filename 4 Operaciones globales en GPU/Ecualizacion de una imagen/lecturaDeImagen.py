import cv2
import numpy as np
from matplotlib import pyplot as plt

img = cv2.imread(path+'/img.jpg',0)

histograma = cv2.calcHist([img], [0], None, [256], [0,256])

funcion = np.zeros((256,1),dtype='int')
acumulado = 0
funcion[0] = 0
for i in range(1,255):
  funcion[i] = acumulado * 255/(img.shape[0]*img.shape[1])
  acumulado += histograma[i]
funcion[255] = 255

'''
#probando si funciona
img2 = cv2.imread(path+'/img.jpg',0)
for i in range (img2.shape[0]):
  for j in range (img2.shape[1]):
    img2[i][j] = funcion[img2[i][j]]

plt.imshow(img2, cmap='gray', vmin=0, vmax=255)
'''

arch = open(path+'/img.txt','w')
for i in img:
  for j in i:
    arch.write('%d\n' % j)
arch.close()

arch = open(path+'/funcion.txt','w')
for i in funcion:
  arch.write('%d\n' % i)
arch.close()

print(img.shape)

plt.imshow(img, cmap='gray', vmin=0, vmax=255)

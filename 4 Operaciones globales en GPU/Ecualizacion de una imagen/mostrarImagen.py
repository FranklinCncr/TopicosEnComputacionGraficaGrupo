import cv2
import numpy as np
from matplotlib import pyplot as plt

h = 425
w = 640

arch = open(path+'/imgEcualizada.txt','r')

imgEcualizada = np.zeros(( h, w), dtype=int)

for i in range (h):
  for j in range(w):
    k = arch.readline()
    imgEcualizada[i][j] = int(k)

plt.imshow(imgEcualizada, cmap='gray', vmin=0, vmax=255)

arch.close()

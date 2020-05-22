import cv2 as cv
import sys
import numpy as np
from matplotlib import pyplot as plt

img2 = cv.imread(cv.samples.findFile("pirata3.jpg"),1)
img = cv.imread(cv.samples.findFile("a6.jpg"),1)

if img is None:
    sys.exit("No se puede")

def suma_ponderada(img1,a,img2,b,c,nueva_imagen):
	nueva_imagen=a*img1+b*img2+c

def rgb2gray(rgb):

    r, g, b = rgb[:,:,0], rgb[:,:,1], rgb[:,:,2]
    gray = 0.2989 * r + 0.5870 * g + 0.1140 * b

    return gray
#############ROI######
'''roi2=  img[200:500, 200:550] #img[y0:y1, x0:x1]
#print(roi1)
print(roi2)
cv.imwrite('ROI 300-350.jpg',roi2)
cv.imshow('roi2', roi2)
cv.imshow('original', img)'''

##############copiar una imagen############
'''nuevaImage = img.copy()
#nuevaImage=nuevaImage+100# a mayor numero la imágen presenta variaciones como el de 100 es 
#cv.imwrite('sumapornumero_P.jpg',nuevaImage)
nuevaImage2=nuevaImage-5
cv.imwrite('restapornumero_100_3.1.jpg',nuevaImage2)
cv.imshow("Display window",nuevaImage2)'''
###############################Cuando se suma aumentael color rojiso y verde  mientras cuando se resta aumenta el color celeste voliviendo saturado
###############################La saturación no modifica en la prueba 2 , un recuadro gris tanto restandole como sumandole dando asi que la saturación no combia con el color gris
'''
nueva_imagen=cv.add(img2,img)
cv.imshow("Suma_imagen1_a2.jpg",nueva_imagen)
cv.imwrite('Suma_imagen_prueba2_a2.jpg',nueva_imagen)'''
'''
nueva_imagen=cv.subtract(img2,img)
cv.imshow("Resta_imagen1_a2.jpg",nueva_imagen)
cv.imwrite('Resta_pirata_paisaje.jpg',nueva_imagen)
'''

#gris, histo
#cv.cvtColor(img,gris,cv.CV_BGR2GRAY)
'''nueva_imagen=img2
i=0
while i<100:
	suma_ponderada(img,i/100.0,img2,1+i/100.0,0,nueva_imagen)
	cv.imshow("Transicion.jpg", nueva_imagen);
	cv.waitKey(10)
	i+=1
'''

'''
resAW = cv.addWeighted(img,0.99,img2,0.5,0)
cv.imshow('resAW',resAW)
cv.imwrite('Suma_Ponderada_paisaje_mayor.jpg',resAW)
#el numero flotante para la primera imagen hace que se vea mayor mientras que al poner 0.5 se ve menos
#al poner el maximo aumenta el brillo
'''


#######################histograma##############
'''img = cv.imread('a6.jpg',cv.IMREAD_GRAYSCALE);
canales= [0]
bins= [256]
rango= [0, 256]
rangos= [rango]
cv.imshow('blanco_negro',img)
cv.imwrite("blanco_negro.jpg", img)
hist =cv.calcHist([img], canales, None,bins,rango)
plt.plot(hist, color='blue' )
plt.xlabel('intensidad de iluminacion')
plt.ylabel('cantidad de pixeles')
plt.show()'''



#######################histograma##############
img = cv.imread('a1.jpg');

'''
hist =cv.calcHist([img], canales, None,bins,[0, 256])
plt.plot(hist, color='blue' )
plt.xlabel('intensidad de iluminacion')
plt.ylabel('cantidad de pixeles')
plt.show()'''

'''color = ('r','g')
for i, c in enumerate(color):
    hist = cv.calcHist([img], [i], None, [256], [0, 256])
    plt.plot(hist, color = c)
    plt.xlim([0,256])
plt.show()
'''


print(img[1])
##R=2	G =1 B=0
hist = cv.calcHist([img], [2, 1], None, [64,64],[0, 256, 0, 256])
plt.plot(hist, color = 'r')
plt.show()
###esto falta cv.CV_8UC1
minval=cv.minMaxLoc(hist)[0]
maxval=cv.minMaxLoc(hist)[1]
print(minval)
print(hist)
i=0
pinta=cv.CV_8UC1
pinta = np.zeros((256, 256, 1), dtype = "uint8")
while i<64:
	j=0
	lista=[]
	while j<64:
		pinta[i][j]=255-255*hist[i][j]/maxval
		j+=1
	i+=1

cv.namedWindow("Histograma R-G", 0);

pinta = cv.UMat(np.array(pinta, dtype=np.uint8))

cv.imwrite("Histograma R-G.jpg", pinta);
'''
img = cv.imread('a1.jpg');
img = np.float32(img) #img.convertTo(im32F, CV_32F, 1.0/255.0);
img = img*1.0/255.0
pow(img, ui->doubleSpinBox->value(), im32F);
im32F.convertTo(img, CV_8U, 255);
'''

'''
img = cv.imread('equalizar.PNG');
cv.imshow("real ",img)
img_to_yuv = cv.cvtColor(img,cv.COLOR_BGR2YUV)
img_to_yuv[:,:,0] = cv.equalizeHist(img_to_yuv[:,:,0])
hist_equalization_result = cv.cvtColor(img_to_yuv, cv.COLOR_YUV2BGR)
cv.imshow("equalizacion ",hist_equalization_result)
cv.imwrite("equalizacion.jpg",hist_equalization_result)'''
k = cv.waitKey(0)
if k == ord("s"):
    cv.imwrite("starry_night.png", img)

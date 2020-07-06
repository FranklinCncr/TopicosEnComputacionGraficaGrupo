import numpy as np
import cv2

def transform(src_vertices, dst_vertices, src, dst):
	global width,height
	M = cv2.getPerspectiveTransform(src_vertices, dst_vertices)
	dst=cv2.warpPerspective(src,M,(width,height), cv2.INTER_LINEAR, cv2.BORDER_CONSTANT);
	cv2.imshow("Segundo",dst)

src=cv2.imread("im1.png")
width,height,_ = src.shape
'''
def CallBackFunc(event, x, y, flags, param):
    if event == cv2.EVENT_LBUTTONDOWN:
        print("Left button of the mouse is clicked - position (", x, ", ",y, ")")
        list_points.append([x,y])
    elif event == cv2.EVENT_RBUTTONDOWN:
        print("Right button of the mouse is clicked - position (", x, ", ", y, ")")
        list_points.append([x,y])



# Create an empty list of points for the coordinates
list_points = list()

# bind the callback function to window
windowName = 'MouseCallback'
cv2.namedWindow(windowName)

cv2.setMouseCallback(windowName, CallBackFunc)
img = cv2.imread("im1.png")
width,height,_ = img.shape
if __name__ == "__main__":
    # Check if the 4 points have been saved
    while (True):
        cv2.imshow(windowName, img)
        if len(list_points) == 4:
            # Return a dict to the YAML file
            config_data = dict(
                image_parameters = dict(
                    p2 = list_points[3],
                    p1 = list_points[2],
                    p4 = list_points[0],
                    p3 = list_points[1],
                    width_og = width,
                    height_og = height,
                    ))
            # Write the result to the config file
            break
        if cv2.waitKey(20) == 27:
            break
    cv2.destroyAllWindows()
'''
###Valores obtenidos anteriormente al hacer el click
src_vertices=[]
src_vertices.append([131,62])
src_vertices.append([204, 61])
src_vertices.append([284, 239])
src_vertices.append([62, 241])


dst_vertices=[]
dst_vertices.append([0,0])
dst_vertices.append([width, 0])
dst_vertices.append([width, height])
dst_vertices.append([0, height])
src_vertices=np.float32(src_vertices)
dst_vertices=np.float32(dst_vertices)
matrix =cv2.getPerspectiveTransform(src_vertices, dst_vertices );
print(matrix)

width=len(src[0])
height=len(src)
print(width,height)
img_transformed = cv2.warpPerspective(src,matrix,(width,height))
cv2.imshow("Primera prespectiva",img_transformed)

dst2=img_transformed
transform(src_vertices, dst_vertices, src, dst2)
cv2.imshow("Real",src)
cv2.waitKey();

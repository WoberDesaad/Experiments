import numpy as np
import cv2
from matplotlib import pyplot as plt


# Load a color image in grayscale
img_file = '2017-12-16-120447_2.jpg'
img = cv2.imread(img_file, cv2.IMREAD_GRAYSCALE)

plt.imshow(img, cmap = 'gray', imperpolation = 'bicubic')
plt.xticks([]), plt.yticks([])
plt.show()

cv2.imshow('Window Name', img)
cv2.waitKey(0)
cv2.destroyAllWindows()

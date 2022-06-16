# import the required libraries
import numpy as np
import cv2
import matplotlib.pyplot as plt
# %matplotlib inline
# read the image
image = cv2.imread('../assets/prueba.jpeg')
# calculate the edges using Canny edge algorithm
edges = cv2.Canny(image, 100, 200)
# plot the edges
cv2.imshow('Canny Edge Detection', edges)
cv2.waitKey(0)

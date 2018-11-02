#!/usr/bin/env python
# encoding: utf-8
'''
@author: 
@license: (C) Copyright 2013-2025, MIT LICENSE
@contact: liyi_whu@163.com
@software: easyssh
@file: filter.py.py
@time: 2018/10/30 23:21
@desc:
'''
import numpy as np
import cv2
from matplotlib import pyplot as plt

class filter:
    def __init__(self):
        pass

if __name__ == '__main__':
    # Load an color image in grayscale
    img = cv2.imread('../../data/speed_40.jpg')
    plt.imshow(img, cmap='gray', interpolation='bicubic')
    plt.xticks([]), plt.yticks([])  # to hide tick values on X and Y axis
    plt.show()
    cv2.namedWindow('image', cv2.WINDOW_NORMAL)
    cv2.imshow('image', img)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
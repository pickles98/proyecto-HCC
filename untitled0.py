#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Dec 28 13:16:22 2022

@author: pickles
"""
import numpy as np
import matplotlib.pyplot as plt

def make_box(box_size, space_size = None):
    if not space_size:
        space_size = box_size + 4
    box = np.zeros([space_size for x in range(3)])
    start = (space_size - box_size) // 2
    end = space_size - start
    box[start:end, start:end, start:end] = 1
    return(box)

box = make_box(box_size=3)

print(box)

print()

box1 = make_box(box_size=1)

print(box1)

print()

box2 = make_box(box_size=2)

print(box2)
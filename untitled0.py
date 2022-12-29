#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Dec 28 13:16:22 2022

@author: pickles
"""
import numpy as np
import matplotlib.pyplot as plt
import ipyvolume as ipv

space_size = 2
box = np.zeros([space_size for x in range(3)])
print(box)
print()
a = np.zeros((10,10))
print(a)
print()
a[3:-3, 3:-3] = 1.
a[4:-4, 4:-4] = 0
print(a)

lenguajes = ['Java', 'Python', 'JavaScript']
versiones = [14, 3, 6]
resultado = zip(lenguajes, versiones)
print(list(resultado))
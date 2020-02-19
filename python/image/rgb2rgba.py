#!/usr/bin/env python3
import os, sys
import numpy as np

rgb = np.fromfile(sys.argv[1], dtype='uint8');

rgba = np.zeros(int(4*rgb.shape[0]/3))

rgba[0::4] = rgb[0::3]
rgba[1::4] = rgb[1::3]
rgba[2::4] = rgb[2::3]
rgba[3::4] = 255

rgba.astype('uint8').tofile(sys.argv[2])

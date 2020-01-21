from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *

import numpy as np
import sys
from enum import Enum
import random

LIGHTPOS = [3.0, 4.0, 5.0, 1.0]

DIFFUSE_GROUND = [[0.6, 0.6, 0.6, 1.0], [0.3, 0.3, 0.3, 1.0]]
RANGE_GROUND = range(-5,5)

ex = 0.0
ez = 0.0
r = 0.0

objects = None

class Blocks(Enum):
    I = 0
    O = 1
    S = 2
    Z = 3
    J = 4
    L = 5
    T = 6
    
test = None

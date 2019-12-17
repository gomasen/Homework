from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *
import numpy as np
import sys

LIGHTPOS = [3.0, 4.0, 5.0, 1.0]
SKYBLUE = np.array([157, 204, 224, 255]) / 255
DIFFUSE_GROUND = [[0.6, 0.6, 0.6, 1.0], [0.3, 0.3, 0.3, 1.0]]
RANGE_GROUND = range(-5,5)

class Tetrimino:
    class I:
        def writeBlocks(coordinate):
            glPushMatrix()
            glTranslated(coordinate[0], 0.0, coordinate[1])
            for i in range(4):
                glMaterialfv(GL_FRONT, GL_DIFFUSE, list(SKYBLUE))
                glutSolidCube(1.0)
                glTranslated(1,0,0)
            glPopMatrix()
            

def idle():
    glutPostRedisplay()

def resize(w, h):
    glViewport(0, 0, w, h)
    
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    gluPerspective(30.0, w/h, 1.0, 100.0)

    glMatrixMode(GL_MODELVIEW)

def init():
    glClearColor(0.0, 0.0, 0.0, 1.0)

def display():
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    glLoadIdentity()
    glLightfv(GL_LIGHT0, GL_POSITION, LIGHTPOS)
    glCallList(objects)
    glFlush()

if __name__=="__main__":
    glutInit(sys.argv)
    glutInitDisplayMode(GLUT_RGBA)
    glutCreateWindow(b"GLUT prog1")
    glutDisplayFunc(display)
    glutReshapeFunc(resize)
    init()
    glutMainLoop()

from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *
import sys

r = 1.2

def init():
    glClearColor(0.0, 0.0, 0.0, 1.0)

def display():
    glClear(GL_COLOR_BUFFER_BIT)
    glBegin(GL_POLYGON)
    glVertex2d(-0.4, -0.4)
    glVertex2d( 0.4, -0.4)
    glVertex2d( 0.4,  0.4)
    glVertex2d(-0.4,  0.4)
    glEnd()
    glFlush()

def zoom(r):
    glOrtho(-r, r, -r, r, -r, r)
    display()

def mouse(button, state, x, y):
    if button == GLUT_LEFT_BUTTON and state == GLUT_DOWN:
        zoom(1/r)
    elif button == GLUT_RIGHT_BUTTON and state == GLUT_DOWN:
        zoom(r)
        
def keyboard(key, x, y):
    if key == GLUT_KEY_UP:
        zoom(1/r)
    if key == GLUT_KEY_DOWN:
        zoom(r)

if __name__ == "__main__":
    glutInitWindowPosition(100, 100)
    glutInitWindowSize(320, 240)
    glutInit(sys.argv)
    glutInitDisplayMode(GLUT_RGBA)
    glutCreateWindow(b"GLUT prog1")
    glutDisplayFunc(display)
    glutMouseFunc(mouse)
    glutSpecialFunc(keyboard)
    init()
    glutMainLoop()

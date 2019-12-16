from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *
import sys

THETA = 25
R = 0.8
n = 0

def drawLine(l):
    glBegin(GL_LINE_STRIP)
    glVertex2d(0, 0)
    glVertex2d(0, l)
    glEnd()

def v(k, l):
    def v1(rotation):
        glPushMatrix()

        glRotated(rotation, 0.0, 0.0, 1.0)
        drawLine(l)
        glTranslated(0.0,l,0.0)
        
        v(k+1, l*R)
        
    if k == 0:
        v1(0)
    else:
        if n < k:
            return 0
        else:
            v1(THETA)
            glPopMatrix()

            v1(-THETA)
            glPopMatrix()
    

def resize(w, h):
    r = 5.0
    glViewport(0, 0, w, h)
    glLoadIdentity()
    glOrtho(-r, r, -r, r, -r, r)

def init():
    glClearColor(0.0, 0.0, 0.0, 1.0)

def display():
    glClear(GL_COLOR_BUFFER_BIT)
    v(0,1)
    glFlush()

def mouse(button, state, x, y):
    global n

    if button == GLUT_LEFT_BUTTON and state == GLUT_DOWN:
        n += 1
    elif button == GLUT_RIGHT_BUTTON and state == GLUT_DOWN:
        n = 0

    display()
    print(n)


if __name__=="__main__":
    glutInit(sys.argv)
    glutInitDisplayMode(GLUT_RGBA)
    glutCreateWindow(b"GLUT prog1")
    glutDisplayFunc(display)
    glutReshapeFunc(resize)
    glutMouseFunc(mouse)
    init()
    glutMainLoop()

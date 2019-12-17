from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *
import sys

THETA = 25
NUMBER_OF_BLANCH = 3
R = 0.8

n = 0
r = 0.0

def drawLine(l):
    glBegin(GL_LINE_STRIP)
    glColor3d(0,1,0)
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
        glPopMatrix()
    else:
        if n < k:
            return 0
        else:
            for i in range(3):
                glRotated(360 / NUMBER_OF_BLANCH, 0.0, 1.0, 0.0)
                v1(THETA)
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
    global r

    glLoadIdentity()
    gluLookAt(10.0, 10.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0)
    glRotated(r, 0.0, 1.0, 0.0)

    glClear(GL_COLOR_BUFFER_BIT)
    v(0,1)
    glFlush()

def mouse(button, state, x, y):
    global n, r

    if button == GLUT_LEFT_BUTTON and state == GLUT_DOWN:
        n += 1
    elif button == GLUT_RIGHT_BUTTON and state == GLUT_DOWN:
        n = 0
    elif button == 3:
        r = 0 if r == 359 else r+1
    elif button == 4:
        r = 359 if r == 0 else r-1

    display()

if __name__=="__main__":
    glutInit(sys.argv)
    glutInitDisplayMode(GLUT_RGBA)
    glutCreateWindow(b"GLUT prog1")
    glutDisplayFunc(display)
    glutReshapeFunc(resize)
    glutMouseFunc(mouse)
    init()
    glutMainLoop()

from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *
import sys

THETA = 25
R = 0.8
n = 1
current_stage = 0

def v(k, l):
    global current_stage

    def v1(rotation):
        global current_stage

        glPushMatrix()
        current_stage += 1

        glRotated(rotation, 0.0, 0.0, 1.0)
        glBegin(GL_LINE_STRIP)
        glVertex2d(0, 0)
        glVertex2d(0, l)
        glEnd()
        glTranslated(0.0,l,0.0)
        
    if k == 0:
        v1(0)
    else:
        if n < k+1:
            if not check_drawing[k][0]:
                v1(THETA)
            check_drawing[k][0] = True
        else:
            glPopMatrix()
            v1(-THETA)
            check_drawing[k][1] = True

    
    if n > k+1:
        v(k+1, l*0.8)
    else:
        for i in range(current_stage):
            glPopMatrix()
    
    current_stage = 0

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
        n = 1

    check_drawing = []
    for i in range(1, n):
        check_drawing.append([False, False])

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

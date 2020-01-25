from Tetrimino import *

def idle():
    glutPostRedisplay()

def resize(w, h):
    glViewport(0, 0, w, h)
    
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    gluPerspective(30.0, w/h, 1.0, 100.0)
    
    gluLookAt(0, 20, -30, 0, 0, 0, 0, 0, 1)

    glMatrixMode(GL_MODELVIEW)

def init():
    gray = 1.0
    glClearColor(gray, gray, gray, 1.0)
    glEnable(GL_DEPTH_TEST)
    glEnable(GL_CULL_FACE)
    glEnable(GL_LIGHTING)
    glEnable(GL_LIGHT0)
    
def display():
    global objects, test
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    
    if not test.current_tetorimino:
        test.createTetrimino()
    else:
        test.drawTetorimino()
    
    glLoadIdentity()
    glLightfv(GL_LIGHT0, GL_POSITION, LIGHTPOS)
    glCallList(objects)

    glFlush()

def saveGroundToList():
    global objects

    objects = glGenLists(1)
    glNewList(objects, GL_COMPILE)

    # ground
    glBegin(GL_QUADS)
    glNormal3d(0.0, 1.0, 0.0)
    for j in RANGE_GROUND:
        for i in RANGE_GROUND:
            glMaterialfv(GL_FRONT, GL_DIFFUSE, \
                DIFFUSE_GROUND[(i+j)&1])
            glVertex3d(i, -0.5, j)
            glVertex3d(i, -0.5, j+1)
            glVertex3d(i+1, -0.5, j+1)
            glVertex3d(i+1, -0.5, j)
    glEnd()
    
    glEndList()

def keyboard(key, x, y):
    if 100 <= key <= 103:
        coordinate_move = np.empty(2)

        if key == GLUT_KEY_LEFT:
            coordinate_move = np.array([1,0])
        elif key == GLUT_KEY_RIGHT:
            coordinate_move = np.array([-1,0])
        elif key == GLUT_KEY_UP:
            coordinate_move = np.array([0,1])
        elif key == GLUT_KEY_DOWN:
            coordinate_move = np.array([0,-1])

        test.moveTetorimino(coordinate_move)
    
    elif key == ' ':
        test.rotateTetorimino()
    
    elif key == 'q' or key == 'Q':
        exit()

    
    display()


def main():
    global test
    
    test = Tetrimino()
    
    glutInit(sys.argv)
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH)
    glutCreateWindow(b"GLUT prog1")
    glutDisplayFunc(display)
    glutReshapeFunc(resize)
    glutKeyboardFunc(keyboard)
    glutSpecialFunc(keyboard)
    init()
    saveGroundToList()
    glutMainLoop()

if __name__=="__main__":
    main()

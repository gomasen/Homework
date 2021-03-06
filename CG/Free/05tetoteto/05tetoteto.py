from Tetrimino import *

LIGHTPOS = [3.0, 4.0, 5.0, 1.0]

DIFFUSE_GROUND = [[0.6, 0.6, 0.6, 1.0], [0.3, 0.3, 0.3, 1.0]]
RANGE_GROUND = range(-5,5)

ex = 0.0
ez = 0.0
r = 0.0

objects = None
test = None

def dropTetorimino(value):
    global test

    if test.is_tetorimino:
        test.moveTetorimino(np.array([0, -1]))

    display()
    glutTimerFunc(1000, dropTetorimino, 0)

def idle():
    glutPostRedisplay()

def resize(w, h):
    glViewport(0, 0, w, h)
    
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    gluPerspective(30.0, w/h, 1.0, 100.0)
    
    gluLookAt(0, 50, 0, 0, 0, 0, 0, 0, 1)

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
    
    if not test.is_tetorimino:
        test.createTetrimino()
    else:
        test.drawAllTetorimino()
    
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
    
    test = Tetris()

    glutInitWindowSize(1000, 1000)    
    glutInit(sys.argv)
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH)
    glutCreateWindow(b"GLUT prog1")
    glutDisplayFunc(display)
    glutReshapeFunc(resize)
    glutKeyboardFunc(keyboard)
    glutSpecialFunc(keyboard)
    init()
    saveGroundToList()
    glutTimerFunc(1000, dropTetorimino, 0)

    glutMainLoop()

if __name__=="__main__":
    main()

from Define import *

class Tetrimino:
    def __init__(self):
        self.i = self.I()
        self.o = self.O()
        self.s = self.S()
        self.z = self.Z()
        self.j = self.J()
        self.l = self.L()
        self.t = self.T()

        self.isTetorimino = False

        self.current_coordinate = np.array([0,0])
        self.current_tetorimino = None
        self.tetorimino_angle = 0
        
    class I:
        def __init__(self):
            self.to_center = np.array([1.5, 0])
            self.coordinate_list = np.array([[-1,-1]])

        def writeBlocks(self):
            glTranslated(-self.to_center[0],0,-self.to_center[1])
            for i in range(4):
                glutSolidCube(1.0)
                glTranslated(1,0,0)

    class O:
        def __init__(self):
            self.to_center = np.array([0.5, -0.5])
            self.coordinate_list = np.array([[-1,-1]])

        def writeBlocks(self):
            glTranslated(-self.to_center[0],0,-self.to_center[1])
            glutSolidCube(1.0)
            glTranslated(1,0,0)
            glutSolidCube(1.0)
            glTranslated(0,0,1)
            glutSolidCube(1.0)
            glTranslated(-1,0,0)
            glutSolidCube(1.0)

    class S:
        def __init__(self):
            self.to_center = np.array([0.5, -0.5])
            self.coordinate_list = np.array([[-1,-1]])

        def writeBlocks(self):
            glTranslated(-self.to_center[0],0,-self.to_center[1])
            glTranslated(0,0,-1)
            glutSolidCube(1.0)
            glTranslated(1,0,0)
            glutSolidCube(1.0)
            glTranslated(0,0,1)
            glutSolidCube(1.0)
            glTranslated(1,0,0)
            glutSolidCube(1.0)

    class Z:
        def __init__(self):
            self.to_center = np.array([1, -0.5])
            self.coordinate_list = np.array([[-1,-1]])

        def writeBlocks(self):
            glTranslated(-self.to_center[0],0,-self.to_center[1])
            glutSolidCube(1.0)
            glTranslated(1,0,0)
            glutSolidCube(1.0)
            glTranslated(0,0,-1)
            glutSolidCube(1.0)
            glTranslated(1,0,0)
            glutSolidCube(1.0)

    class J:
        def __init__(self):
            self.to_center = np.array([1, -0.5])
            self.coordinate_list = np.array([[-1,-1]])

        def writeBlocks(self):
            glTranslated(-self.to_center[0],0,-self.to_center[1])
            glutSolidCube(1.0)
            glTranslated(0,0,-1)
            glutSolidCube(1.0)
            glTranslated(1,0,0)
            glutSolidCube(1.0)
            glTranslated(1,0,0)
            glutSolidCube(1.0)

    class L:
        def __init__(self):
            self.to_center = np.array([1, -0.5])
            self.coordinate_list = np.array([[-1,-1]])

        def writeBlocks(self):
            glTranslated(-self.to_center[0],0,-self.to_center[1])
            glTranslated(0,0,-1)
            glutSolidCube(1.0)
            glTranslated(1,0,0)
            glutSolidCube(1.0)
            glTranslated(1,0,0)
            glutSolidCube(1.0)
            glTranslated(0,0,1)
            glutSolidCube(1.0)

    class T:
        def __init__(self):
            self.to_center = np.array([1, -0.5])
            self.coordinate_list = np.array([[-1,-1]])

        def writeBlocks(self):
            glTranslated(-self.to_center[0],0,-self.to_center[1])
            glTranslated(0,0,-1)
            glutSolidCube(1.0)
            glTranslated(1,0,0)
            glutSolidCube(1.0)
            glTranslated(0,0,1)
            glutSolidCube(1.0)
            glTranslated(1,0,-1)
            glutSolidCube(1.0)

    def createTetrimino(self):
        tetorimino = random.randint(0, 6)

        if tetorimino == Blocks.I.value:
            self.current_tetorimino = self.i
        if tetorimino == Blocks.O.value:
            self.current_tetorimino = self.o
        if tetorimino == Blocks.S.value:
            self.current_tetorimino = self.s
        if tetorimino == Blocks.Z.value:
            self.current_tetorimino = self.z
        if tetorimino == Blocks.J.value:
            self.current_tetorimino = self.j
        if tetorimino == Blocks.L.value:
            self.current_tetorimino = self.l
        if tetorimino == Blocks.T.value:
            self.current_tetorimino = self.t

        self.drawTetorimino()

    def drawTetorimino(self):
        glPushMatrix()
        glTranslated(self.current_coordinate[0], 0, self.current_coordinate[1])
        glRotated(np.rad2deg(self.tetorimino_angle), 0,1,0)
        self.current_tetorimino.writeBlocks()
        
        glPopMatrix()

    def moveTetorimino(self, move_list):
        self.current_coordinate = self.current_coordinate + move_list
        self.drawTetorimino()

    def rotateTetorimino(self):
        if self.tetorimino_angle <= 3/2 * np.pi:
            self.tetorimino_angle += np.pi/2
        else:
            self.tetorimino_angle = 0

        
        rotation_matrix = np.array([[np.cos(self.tetorimino_angle), -np.sin(self.tetorimino_angle)], \
                                    [np.sin(self.tetorimino_angle), np.cos(self.tetorimino_angle)]])

        # self.current_coordinate[0] = self.current_coordinate[0] * np.cos(self.tetorimino_angle) - self.current_coordinate[1] * np.sin(self.tetorimino_angle)
        # self.current_coordinate[1] = self.current_coordinate[0] * np.sin(self.tetorimino_angle) + self.current_coordinate[1] * np.cos(self.tetorimino_angle)

        # self.current_coordinate = self.current_coordinate

        # self.current_coordinate = self.current_coordinate
   
        self.drawTetorimino()

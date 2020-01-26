from Define import *

from enum import Enum
import random


class Blocks(Enum):
    I = 0
    O = 1
    S = 2
    Z = 3
    J = 4
    L = 5
    T = 6

class Tetrimino:
    def __init__(self):
        self.i = self.I()
        self.o = self.O()
        self.s = self.S()
        self.z = self.Z()
        self.j = self.J()
        self.l = self.L()
        self.t = self.T()

        self.is_tetorimino = False

        self.current_coordinate = np.array([0,10])
        self.current_tetorimino = None
        self.tetorimino_angle = 0

        self.tetorimino_list = np.array([[[-1,-1], -1]])
        
    class I:
        def __init__(self):
            self.to_center = np.array([1.5, 0])
            self.tetorimino_number = Blocks.I.value

        def writeBlocks(self):
            glTranslated(-self.to_center[0],0,-self.to_center[1])
            for i in range(4):
                glutSolidCube(1.0)
                glTranslated(1,0,0)

    class O:
        def __init__(self):
            self.to_center = np.array([0.5, -0.5])
            self.tetorimino_number = Blocks.O.value

        def writeBlocks(self):
            glTranslated(-self.to_center[0],0,-self.to_center[1])
            glutSolidCube(1.0)
            glTranslated(1,0,0)
            glutSolidCube(1.0)
            glTranslated(0,0,-1)
            glutSolidCube(1.0)
            glTranslated(-1,0,0)
            glutSolidCube(1.0)

    class S:
        def __init__(self):
            self.to_center = np.array([0.5, -0.5])
            self.tetorimino_number = Blocks.S.value

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
            self.tetorimino_number = Blocks.Z.value

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
            self.tetorimino_number = Blocks.J.value

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
            self.tetorimino_number = Blocks.L.value

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
            self.tetorimino_number = Blocks.T.value

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

    def drawAllTetorimino(self):
        for tetorimino in self.tetorimino_list[1:]:
            print(tetorimino)
            tet = self.classifyTetorimino(tetorimino[1])
            self.drawTetorimino(tetorimino[0], tet)
        
        if self.is_tetorimino:
            self.drawTetorimino(self.current_coordinate, self.current_tetorimino, True)

    def classifyTetorimino(self, tetorimino_number):
        tetorimino = None

        if tetorimino_number == Blocks.I.value:
            tetorimino = self.i
        if tetorimino_number == Blocks.O.value:
            tetorimino = self.o
        if tetorimino_number == Blocks.S.value:
            tetorimino = self.s
        if tetorimino_number == Blocks.Z.value:
            tetorimino = self.z
        if tetorimino_number == Blocks.J.value:
            tetorimino = self.j
        if tetorimino_number == Blocks.L.value:
            tetorimino = self.l
        if tetorimino_number == Blocks.T.value:
            tetorimino = self.t
        
        return tetorimino

    def createTetrimino(self):
        self.is_tetorimino = True
        tetorimino = random.randint(0, 6)

        self.current_tetorimino = self.classifyTetorimino(tetorimino)

        self.drawAllTetorimino()

    def drawTetorimino(self, coordinate, tetorimino, is_current=False):
        glPushMatrix()

        glTranslated(coordinate[0], 0, coordinate[1])
        if is_current:
            glRotated(np.rad2deg(self.tetorimino_angle), 0,1,0)
        tetorimino.writeBlocks()
        
        glPopMatrix()

        if self.current_coordinate[1] <= -10 and is_current:
            self.is_tetorimino = False
            self.current_coordinate = np.array([0,10])
            self.tetorimino_angle = 0
            self.current_tetorimino = None

            self.tetorimino_list = np.append(self.tetorimino_list, np.array([[coordinate.tolist(), tetorimino.tetorimino_number]]), axis=0)
            print(self.tetorimino_list)

    def moveTetorimino(self, move_list):
        self.current_coordinate = self.current_coordinate + move_list

    def rotateTetorimino(self):
        if self.tetorimino_angle <= 3/2 * np.pi:
            self.tetorimino_angle += np.pi/2
        else:
            self.tetorimino_angle = 0

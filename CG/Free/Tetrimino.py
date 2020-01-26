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

class Tetorimino:
    def __init__(self, center, tetorimino, angle):
        self.center_coordinate = center
        self.tetorimino = tetorimino
        self.angle = angle
        self.is_current = True

        self.reloadCoordinateOfBlocks()

    def reloadCoordinateOfBlocks(self):
        self.coordinate = np.array([[-1,-1]])
        self.coordinate = self.tetorimino.calcCoordinateOfBlocks(self.center_coordinate, self.coordinate)
        self.coordinate = np.delete(self.coordinate, 0, axis=0)

class Tetris:
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

        self.tetorimino_list = np.empty(0, dtype=object)
        
    class I:
        def __init__(self):
            self.to_center = np.array([1.5, 0])
            self.tetorimino_number = Blocks.I.value

        def writeBlocks(self):
            glTranslated(-self.to_center[0],0,-self.to_center[1])
            for i in range(4):
                glutSolidCube(1.0)
                glTranslated(1,0,0)
        
        def calcCoordinateOfBlocks(self, coordinate, coordinate_list):
            coo = coordinate - self.to_center
            for i in range(4):
                coordinate_list = np.append(coordinate_list, np.array([coo]), axis=0)
                coo[0] += 1
            
            return coordinate_list

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
        
        def calcCoordinateOfBlocks(self, coordinate, coordinate_list):
            coo = coordinate - self.to_center

            coordinate_list = np.append(coordinate_list, np.array([coo]), axis=0)
            coo[0] += 1
            coordinate_list = np.append(coordinate_list, np.array([coo]), axis=0)
            coo[1] -= 1
            coordinate_list = np.append(coordinate_list, np.array([coo]), axis=0)
            coo[0] -= 1
            coordinate_list = np.append(coordinate_list, np.array([coo]), axis=0)

            return coordinate_list

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

        def calcCoordinateOfBlocks(self, coordinate, coordinate_list):
            coo = coordinate - self.to_center

            coo[1] -= 1
            coordinate_list = np.append(coordinate_list, np.array([coo]), axis=0)
            coo[0] += 1
            coordinate_list = np.append(coordinate_list, np.array([coo]), axis=0)
            coo[1] += 1
            coordinate_list = np.append(coordinate_list, np.array([coo]), axis=0)
            coo[0] += 1
            coordinate_list = np.append(coordinate_list, np.array([coo]), axis=0)

            return coordinate_list

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

        def calcCoordinateOfBlocks(self, coordinate, coordinate_list):
            coo = coordinate - self.to_center

            coordinate_list = np.append(coordinate_list, np.array([coo]), axis=0)
            coo[0] += 1
            coordinate_list = np.append(coordinate_list, np.array([coo]), axis=0)
            coo[1] -= 1
            coordinate_list = np.append(coordinate_list, np.array([coo]), axis=0)
            coo[0] += 1
            coordinate_list = np.append(coordinate_list, np.array([coo]), axis=0)

            return coordinate_list

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

        def calcCoordinateOfBlocks(self, coordinate, coordinate_list):
            coo = coordinate - self.to_center

            coordinate_list = np.append(coordinate_list, np.array([coo]), axis=0)
            coo[1] -= 1
            coordinate_list = np.append(coordinate_list, np.array([coo]), axis=0)
            coo[0] += 1
            coordinate_list = np.append(coordinate_list, np.array([coo]), axis=0)
            coo[0] += 1
            coordinate_list = np.append(coordinate_list, np.array([coo]), axis=0)

            return coordinate_list

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

        def calcCoordinateOfBlocks(self, coordinate, coordinate_list):
            coo = coordinate - self.to_center

            coo[1] -= 1
            coordinate_list = np.append(coordinate_list, np.array([coo]), axis=0)
            coo[0] += 1
            coordinate_list = np.append(coordinate_list, np.array([coo]), axis=0)
            coo[0] += 1
            coordinate_list = np.append(coordinate_list, np.array([coo]), axis=0)
            coo[1] += 1
            coordinate_list = np.append(coordinate_list, np.array([coo]), axis=0)

            return coordinate_list

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

        def calcCoordinateOfBlocks(self, coordinate, coordinate_list):
            coo = coordinate - self.to_center

            coo[1] -= 1
            coordinate_list = np.append(coordinate_list, np.array([coo]), axis=0)
            coo[0] += 1
            coordinate_list = np.append(coordinate_list, np.array([coo]), axis=0)
            coo[1] += 1
            coordinate_list = np.append(coordinate_list, np.array([coo]), axis=0)
            coo[0] += 1
            coo[1] -= 1
            coordinate_list = np.append(coordinate_list, np.array([coo]), axis=0)

            return coordinate_list

    def drawAllTetorimino(self):
        for tetorimino in self.tetorimino_list:
            if tetorimino.is_current:
                self.drawTetorimino(tetorimino, True)
            else:
                self.drawTetorimino(tetorimino)

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

        init_coordinate = np.array([0,10])
        init_angle = 0
        init_tetorimino = self.classifyTetorimino(tetorimino)

        tetorimino_obj = Tetorimino(init_coordinate, init_tetorimino, init_angle)
        self.tetorimino_list = np.append(self.tetorimino_list, tetorimino_obj)
        self.current_tetorimino = self.tetorimino_list[-1]

        self.drawAllTetorimino()

    def drawTetorimino(self, tetorimino, is_current=False):
        glPushMatrix()

        glTranslated(tetorimino.center_coordinate[0], 0, tetorimino.center_coordinate[1])
   
        glRotated(np.rad2deg(tetorimino.angle), 0,1,0)
        tetorimino.tetorimino.writeBlocks()
        
        glPopMatrix()

        if self.current_tetorimino.center_coordinate[1] <= -10 and is_current:
            self.is_tetorimino = False
            self.current_tetorimino.is_current = False
            self.current_tetorimino = None

    def moveTetorimino(self, move_list):
        if self.is_tetorimino:

            if 2 <= self.current_tetorimino.tetorimino.tetorimino_number <= 6:
                move_list[0] += 0.5
            
            self.current_tetorimino.center_coordinate = self.current_tetorimino.center_coordinate + move_list
            self.current_tetorimino.reloadCoordinateOfBlocks()

            for tet_past in self.tetorimino_list[:-1]:
                for block_coordinate in tet_past.coordinate:
                    for b_c_current in self.current_tetorimino.coordinate:
                        if b_c_current[0] == block_coordinate[0] and b_c_current[1] == block_coordinate[1]:
                            self.current_tetorimino.center_coordinate = self.current_tetorimino.center_coordinate - move_list
                            print("aaa")
                            break

    def rotateTetorimino(self):
        if self.current_tetorimino.angle <= 3/2 * np.pi:
            self.current_tetorimino.angle += np.pi/2
        else:
            self.current_tetorimino.angle = 0

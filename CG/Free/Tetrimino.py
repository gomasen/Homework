from Define import *

class Tetrimino:
    def __init__(self):
        self.block_list = np.array([[[-1,-1], 10]])
        
    def createTetrimino(self, coordinate):
        kind = random.randint(0, 6)
        glPushMatrix()
        glTranslated(coordinate[0], 0, coordinate[1])
        
        if kind == Blocks.I.value:
            self.writeI()
        if kind == Blocks.O.value:
            self.writeO()
        if kind == Blocks.S.value:
            self.writeS()
        if kind == Blocks.Z.value:
            self.writeZ()
        if kind == Blocks.J.value:
            self.writeJ()
        if kind == Blocks.L.value:
            self.writeL()
        if kind == Blocks.T.value:
            self.writeT()

        self.block_list = np.append(self.block_list, [[[coordinate[0], coordinate[1]], kind]])
        
        glPopMatrix()

    def writeI(self):
        for i in range(4):
            glutSolidCube(1.0)
            glTranslated(1,0,0)
        
    def writeO(self):
        glutSolidCube(1.0)
        glTranslated(1,0,0)
        glutSolidCube(1.0)
        glTranslated(0,0,1)
        glutSolidCube(1.0)
        glTranslated(-1,0,0)
        glutSolidCube(1.0)

    def writeS(self):
        glTranslated(0,0,-1)
        glutSolidCube(1.0)
        glTranslated(1,0,0)
        glutSolidCube(1.0)
        glTranslated(0,0,1)
        glutSolidCube(1.0)
        glTranslated(1,0,0)
        glutSolidCube(1.0)

    def writeZ(self):
        glutSolidCube(1.0)
        glTranslated(1,0,0)
        glutSolidCube(1.0)
        glTranslated(0,0,-1)
        glutSolidCube(1.0)
        glTranslated(1,0,0)
        glutSolidCube(1.0)

    def writeJ(self):
        glutSolidCube(1.0)
        glTranslated(0,0,-1)
        glutSolidCube(1.0)
        glTranslated(1,0,0)
        glutSolidCube(1.0)
        glTranslated(1,0,0)
        glutSolidCube(1.0)

    def writeL(self):
        glTranslated(0,0,-1)
        glutSolidCube(1.0)
        glTranslated(1,0,0)
        glutSolidCube(1.0)
        glTranslated(1,0,0)
        glutSolidCube(1.0)
        glTranslated(0,0,1)
        glutSolidCube(1.0)

    def writeT(self):
        glTranslated(0,0,-1)
        glutSolidCube(1.0)
        glTranslated(1,0,0)
        glutSolidCube(1.0)
        glTranslated(0,0,1)
        glutSolidCube(1.0)
        glTranslated(1,0,-1)
        glutSolidCube(1.0)

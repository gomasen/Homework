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
        
    class I:
        def __init__(self):
            self.to_center = np.array([1.5, 0])
            self.coordinate_list = np.array([[-1,-1]])

        def writeBlocks(self):
            for i in range(4):
                glutSolidCube(1.0)
                glTranslated(1,0,0)

    class O:
        def __init__(self):
            self.to_center = np.array([1.5, 0])
            self.coordinate_list = np.array([[-1,-1]])

        def writeBlocks(self):
            glutSolidCube(1.0)
            glTranslated(1,0,0)
            glutSolidCube(1.0)
            glTranslated(0,0,1)
            glutSolidCube(1.0)
            glTranslated(-1,0,0)
            glutSolidCube(1.0)

    class S:
        def __init__(self):
            self.to_center = np.array([1.5, 0])
            self.coordinate_list = np.array([[-1,-1]])

        def writeBlocks(self):
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
            self.to_center = np.array([1.5, 0])
            self.coordinate_list = np.array([[-1,-1]])

        def writeBlocks(self):
            glutSolidCube(1.0)
            glTranslated(1,0,0)
            glutSolidCube(1.0)
            glTranslated(0,0,-1)
            glutSolidCube(1.0)
            glTranslated(1,0,0)
            glutSolidCube(1.0)

    class J:
        def __init__(self):
            self.to_center = np.array([1.5, 0])
            self.coordinate_list = np.array([[-1,-1]])

        def writeBlocks(self):
            glutSolidCube(1.0)
            glTranslated(0,0,-1)
            glutSolidCube(1.0)
            glTranslated(1,0,0)
            glutSolidCube(1.0)
            glTranslated(1,0,0)
            glutSolidCube(1.0)

    class L:
        def __init__(self):
            self.to_center = np.array([1.5, 0])
            self.coordinate_list = np.array([[-1,-1]])

        def writeBlocks(self):
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
            self.to_center = np.array([1.5, 0])
            self.coordinate_list = np.array([[-1,-1]])

        def writeBlocks(self):
            glTranslated(0,0,-1)
            glutSolidCube(1.0)
            glTranslated(1,0,0)
            glutSolidCube(1.0)
            glTranslated(0,0,1)
            glutSolidCube(1.0)
            glTranslated(1,0,-1)
            glutSolidCube(1.0)

    def createTetrimino(self, coordinate):
        tetorimino = random.randint(0, 6)
        glPushMatrix()
        glTranslated(coordinate[0], 0, coordinate[1])
        
        if tetorimino == Blocks.I.value:
            self.i.writeBlocks()
        if tetorimino == Blocks.O.value:
            self.o.writeBlocks()
        if tetorimino == Blocks.S.value:
            self.s.writeBlocks()
        if tetorimino == Blocks.Z.value:
            self.z.writeBlocks()
        if tetorimino == Blocks.J.value:
            self.j.writeBlocks()
        if tetorimino == Blocks.L.value:
            self.j.writeBlocks()
        if tetorimino == Blocks.T.value:
            self.t.writeBlocks()
        
        glPopMatrix()

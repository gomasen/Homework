#include "ppmload.h"

enum Dither{
	BAYER, HALFTONE, SCREW, TSCREW, MIDDLE, DOT
};

int selectDitherMethod(){
	int dither;

	printf("どの型でディザ法をしますか？\n");
	printf("0: Bayer型, 1: ハーフトーン型, 2: Screw型, \n3: Screw(変形)型, 4: 中間値強調型, 5: ドット集中型\n");
	scanf("%d", &dither);
	printf("%d\n", dither);

	return dither;
}

void setToDitherArray(int dither[][4], int arr[][4]){
	for (int j = 0; j < 4; j++){
		for (int i = 0; i < 4; i++){
			arr[j][i] = dither[j][i];
		}
	}
}

int ditherBinarization(int dither, ppmimg *img1, ppmimg *img2, int x, int y){
	int dither_array[4][4] = {0};

	int bayer[4][4]    = {{0,8,2,10},  {12,4,14,6}, {3,11,1,9}, {15,7,13,5}};
	int halftone[4][4] = {{10,4,6,8},  {12,0,2,14}, {7,9,11,5}, {3,15,13,1}};
	int screw[4][4]    = {{13,7,6,12}, {8,1,0,5},   {9,2,3,4},  {14,10,11,15}};
	int tscrew[4][4]   = {{15,4,8,12}, {11,0,1,5},  {7,3,2,9},  {14,10,6,13}};
	int middle[4][4]   = {{12,4,8,14}, {11,0,2,6},  {7,3,1,10}, {15,9,5,13}};
	int dot[4][4]      = {{13,4,8,14}, {10,0,1,7},  {6,3,2,11}, {15,9,5,13}};

	switch(dither){
		case BAYER:    setToDitherArray(bayer, dither_array);    break;
		case HALFTONE: setToDitherArray(halftone, dither_array); break;
		case SCREW:    setToDitherArray(screw, dither_array);    break;
		case TSCREW:   setToDitherArray(tscrew, dither_array);   break;
		case MIDDLE:   setToDitherArray(middle, dither_array);   break;
		case DOT:      setToDitherArray(dot, dither_array);      break;
		default: return -1;
	}

	if (x+7 <= img1->iwidth && y+7 <= img1->iheight){
		for(int j = 0; j < 4; j++){
			for(int i = 0; i < 4; i++){
				RGBColor value = getPnmPixel(img1, x+i, y+j);
				(value.R >= (dither_array[j][i]*16+8)) ? value.R = value.G = value.B = 255 : value.R = value.G = value.B = 0;
				setPnmPixel(img2, x+i, y+j, value);
			}
		}
	}

	return 1;
}

int main(void){
	struct ppmimg *image1=NULL,*image2=NULL,*image3=NULL;
	int dither = selectDitherMethod();

	image1 = makeimagestruct(image1);
	image2 = makeimagestruct(image2);
	image3 = makeimagestruct(image3);

	loadppmimage("Lenna_gray.ppm",image1);
	cloneppmimage(image1,image2);

	image3 = createppmimage(image3,image1->iwidth,image1->iheight,image1->cmode);

	for(int j=0;j<image1->iheight;j++){
		for(int i=0;i<image1->iwidth;i++){
			if (!ditherBinarization(dither, image1, image3, i, j))
				break;
		}
	}

	switch(dither){
		case BAYER:
			saveppmimage(image3,"bayer.ppm");
		break;
		case HALFTONE:
			saveppmimage(image3,"halftone.ppm");
		break;
		case SCREW:
			saveppmimage(image3,"screw.ppm");
		break;
		case TSCREW:
			saveppmimage(image3,"tscrew.ppm");
		break;
		case MIDDLE:
			saveppmimage(image3,"middle.ppm");
		break;
		case DOT:
			saveppmimage(image3,"dot.ppm");
		break;
		default: break;
	}

	deleteppmimg(image1);
	deleteppmimg(image2);
	deleteppmimg(image3);

	return 0;
}
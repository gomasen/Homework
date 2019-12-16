#include "ppmload.h"

int selectSizeOfMosaic(){
	int size;

	printf("モザイクのサイズを選んでください。\n");
	printf("1: 8x8 or 2: 16x16\n");
	scanf("%d", &size);

	switch(size){
		case 1: size = 8; break;
		case 2: size = 16; break;
		default: size = -1; break;
	}

	return size;
}

void mosiac(int size, ppmimg *img1, ppmimg *img2, int x, int y){
	int color[3] = {0};

	if (x+7 <= img1->iwidth && y+7 <= img1->iheight){
		for(int j = 0; j < size; j++){
			for(int i = 0; i < size; i++){
				color[0] += getPnmPixel(img1, x+i, y+j).R;
				color[1] += getPnmPixel(img1, x+i, y+j).G;
				color[2] += getPnmPixel(img1, x+i, y+j).B;
			}
		}

		for(int i = 0; i < 3; i++){
			color[i] /= size*size;
		}

		RGBColor new_color;
		new_color.R = color[0];
		new_color.G = color[1];
		new_color.B = color[2];

		for(int j = 0; j < size; j++){
			for(int i = 0; i < size; i++){
				setPnmPixel(img2, x+i, y+j, new_color);
			}
		}
	}
}

int main(void){
	struct ppmimg *image1=NULL,*image2=NULL,*image3=NULL;
	int mosaic_size = selectSizeOfMosaic();
	if (mosaic_size == -1) return -1;


	image1 = makeimagestruct(image1);
	image2 = makeimagestruct(image2);
	image3 = makeimagestruct(image3);

	loadppmimage("Black_hole.ppm",image1);
	cloneppmimage(image1,image2);

	image3 = createppmimage(image3,image1->iwidth,image1->iheight,image1->cmode);

	for(int j=0;j<image1->iheight;j+=mosaic_size){
		for(int i=0;i<image1->iwidth;i+=mosaic_size){
			mosiac(mosaic_size, image1, image3, i, j);
		}
	}

	switch(mosaic_size){
		case 8:	 saveppmimage(image3,"mosaic_8.ppm");  break;
		case 16: saveppmimage(image3,"mosaic_16.ppm"); break;
	}

	deleteppmimg(image1);
	deleteppmimg(image2);
	deleteppmimg(image3);

	return 0;
}
#include "ppmload.h"

void cvtGray(ppmimg *src, ppmimg *dst, int sw);
int inputCvtMethod();
unsigned char max(RGBColor *);
unsigned char min(RGBColor *);
void createLUT(unsigned char *);
int inputToneNum();

int main(void){
	struct ppmimg *image1=NULL,*image2=NULL,*image3=NULL;
	int sw;
	unsigned char **pixel_value;
	int i;

	image1 = makeimagestruct(image1);
	image2 = makeimagestruct(image2);
	image3 = makeimagestruct(image3);

	loadppmimage("Black_hole.ppm",image1);
	cloneppmimage(image1,image2);
	image3 = createppmimage(image3,image1->iwidth,image1->iheight,image1->cmode);

	sw = inputCvtMethod();
	cvtGray(image1, image3, sw);

	saveppmimage(image3,"Converted.ppm");
	deleteppmimg(image1);
	deleteppmimg(image2);
	deleteppmimg(image3);

	return 0;
}

void cvtGray(ppmimg *src, ppmimg *dst, int sw){
	unsigned char tone[256] = {0};

	createLUT(tone);

	for(int j=0;j<src->iheight;j++){
		for(int i=0;i<src->iwidth;i++){
			unsigned char Y = 0;
			struct RGBColor trgb = getPnmPixel(src,i,j);

			switch(sw){
				case 0: Y = trgb.G; break;
				case 1: Y = (trgb.R + trgb.G + trgb.B) / 3; break;
				case 2: Y = (max(&trgb) + min(&trgb)) / 2; break;
				case 3: Y = 0.298912 * trgb.R + 0.586611 * trgb.G + 0.114478 * trgb.B; break;
			}

			trgb.R = tone[Y];
			trgb.G = tone[Y];
			trgb.B = tone[Y];

			setPnmPixel(dst,i,j,trgb);
		}
	}

	puts("Gray image created...\n");
}

int inputCvtMethod(){
	int ans;

	puts("�ǂ̕��@�ŃO���C�X�P�[���ɕϊ����܂����H\n");
	puts("0 : G-channel");
	puts("1 : �P������");
	puts("2 : ���Ԓl");
	puts("3 : NTST���d����");
	printf("Ans : ");

	scanf("%d", &ans);

	return ans;
}

unsigned char max(RGBColor *rgb){
	if(rgb->R >= rgb->G && rgb->R >= rgb->B){
		return rgb->R;
	}
	if(rgb->G >= rgb->R && rgb->G >= rgb->B){
		return rgb->G;
	}
	if(rgb->B >= rgb->R && rgb->B >= rgb->G){
		return rgb->B;
	}
}

unsigned char min(RGBColor *rgb){
	if(rgb->R <= rgb->G && rgb->R <= rgb->B){
		return rgb->R;
	}
	if(rgb->G <= rgb->R && rgb->G <= rgb->B){
		return rgb->G;
	}
	if(rgb->B <= rgb->R && rgb->B <= rgb->G){
		return rgb->B;
	}
}

void createLUT(unsigned char tone[]){
	int num = inputToneNum();
	int i, j;

	for (i = 0; i < 256; i += 256 / num){
		for (j = i; j < 256; j++){
			tone[j] = i;
		}
	}
}


int inputToneNum()
{
	int num;

	printf("�~������I�����Ă��������B");
	puts("2, 4, 8, 16, 32, 64, 128");

	scanf("%d", &num);

	return num;
}
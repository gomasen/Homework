#include "ppmload.h"

int main(void){
	struct ppmimg *image1=NULL,*image2=NULL,*image3=NULL;

	image1 = makeimagestruct(image1);
	image2 = makeimagestruct(image2);
	image3 = makeimagestruct(image3);

	loadppmimage("Lenna_gray.ppm",image1);

	cloneppmimage(image1,image2);

	image3 = createppmimage(image3,image1->iwidth,image1->iheight,image1->cmode);

	for(int j=0;j<image1->iheight;j++){
		for(int i=0;i<image1->iwidth;i++){
			struct RGBColor trgb = getPnmPixel(image1,i,j);
			(trgb.R >= 128) ? trgb.R = trgb.G = trgb.B = 255 : trgb.R = trgb.G = trgb.B = 0;
			setPnmPixel(image3,i,j,trgb);
		}
	}
	saveppmimage(image3,"threshold.ppm");

	deleteppmimg(image1);
	deleteppmimg(image2);
	deleteppmimg(image3);

	return 0;
}
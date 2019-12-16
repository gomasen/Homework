#include "ppmload.h"

//#define RED
//#define BLUE
#define GREEN

void main(void){
	struct ppmimg *image1=NULL,*image2=NULL,*image3=NULL;
	char save_name[20];

	image1 = makeimagestruct(image1);
	image2 = makeimagestruct(image2);
	image3 = makeimagestruct(image3);
	loadppmimage("BlackHole.ppm",image1);
	cloneppmimage(image1,image2);
	image3 = createppmimage(image3,image1->iwidth,image1->iheight,image1->cmode);
	for(int j=0;j<image1->iheight;j++){
		for(int i=0;i<image1->iwidth;i++){
			struct RGBColor trgb = getPnmPixel(image1,i,j);
			if(image1->cmode == 1){
				trgb.dens = 255 - trgb.dens;
			}else{
#ifdef RED
				trgb.B = trgb.G = 0;
				sprintf(save_name, "RedBlackHole.ppm");
#endif

#ifdef BLUE
				trgb.R = trgb.G = 0;
				sprintf(save_name, "BlueBlackHole.pgm");
#endif

#ifdef GREEN
				trgb.R = trgb.B = 0;
				sprintf(save_name, "GreenBlackHole.pgm");
#endif
			}
			setPnmPixel(image3,i,j,trgb);
		}
	}
	saveppmimage(image3, save_name);
	deleteppmimg(image1);
	deleteppmimg(image2);
	deleteppmimg(image3);
}
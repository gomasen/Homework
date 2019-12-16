#include "ppmload.h"

int main(void){
	struct ppmimg *image1=NULL,*image2=NULL,*image3=NULL,*image4=NULL;

	image1 = makeimagestruct(image1);
	image2 = makeimagestruct(image2);
	image3 = makeimagestruct(image3);
    image4 = makeimagestruct(image4);

    loadppmimage("milkdrop.ppm", image1);
	loadppmimage("Lenna.ppm",image2);
    loadppmimage("Lenna_gray.ppm", image3);

	image4 = createppmimage(image4,image1->iwidth,image1->iheight,image1->cmode);

	for(int j=0;j<image1->iheight;j++){
		for(int i=0;i<image1->iwidth;i++){
			struct RGBColor g1 = getPnmPixel(image1,i,j);
			struct RGBColor g2 = getPnmPixel(image2,i,j);
            struct RGBColor g3 = getPnmPixel(image3,i,j);
            struct RGBColor g;

			float alpha = g3.R / 255.0;

            g.R = (1 - alpha)*g1.R + alpha * g2.R;
            g.G = (1 - alpha)*g1.G + alpha * g2.G;
            g.B = (1 - alpha)*g1.B + alpha * g2.B;

			setPnmPixel(image4,i,j,g);
		}
	}

	saveppmimage(image4,"alfaBlend.ppm");

	deleteppmimg(image1);
	deleteppmimg(image2);
	deleteppmimg(image3);
	deleteppmimg(image4);

	return 0;
}
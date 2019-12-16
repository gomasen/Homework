#include "ppmload.h"

//#define RGB_AVERAGE
#define NTSC_WEIGHTED_AVERAGE

void main(void){
	struct ppmimg *image1 = NULL, *image2 = NULL, *image3 = NULL;
	char filename[20];

	image1 = makeimagestruct(image1);
	image2 = makeimagestruct(image2);
	image3 = makeimagestruct(image3);

	loadppmimage("BlackHole.ppm", image1);
	cloneppmimage(image1, image2);
	image3 = createppmimage(image3, image1->iwidth, image1->iheight, image1->cmode);

	for (int j = 0; j<image1->iheight; j++){
		for (int i = 0; i<image1->iwidth; i++){
			struct RGBColor trgb = getPnmPixel(image1, i, j);
			if (image1->cmode == 1){
				trgb.dens = 255 - trgb.dens;
			}
			else{
#ifdef RGB_AVERAGE
				trgb.R = trgb.G = trgb.B = (trgb.R + trgb.G + trgb.B) / 3.0;
				sprintf(filename, "RGBAvarageBlackHole.pgm");
#endif

#ifdef NTSC_WEIGHTED_AVERAGE
				trgb.R = trgb.G = trgb.B = 0.298912*trgb.R + 0.586611*trgb.G + 0.114478*trgb.B;
				sprintf(filename, "NTSC_BlackHole.pgm");
#endif
			}
			setPnmPixel(image3, i, j, trgb);
		}
	}

	saveppmimage(image3, filename);

	deleteppmimg(image1);
	deleteppmimg(image2);
	deleteppmimg(image3);
}
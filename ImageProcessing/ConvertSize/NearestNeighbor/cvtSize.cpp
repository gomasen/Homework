#include "ppmload.h"

float inputCvtSize(){
    float size;

    printf("何倍に変換しますか？\n: ");
    scanf("%f", &size);

    return size;
}

int main(void){
	struct ppmimg *image1=NULL,*image2=NULL,*image3=NULL;

    float size = inputCvtSize();
    int cvted_size[2];

	image1 = makeimagestruct(image1);
	image2 = makeimagestruct(image2);
	image3 = makeimagestruct(image3);
	loadppmimage("Black_hole.ppm",image1);
	cloneppmimage(image1,image2);

    cvted_size[0] = image1->iwidth * size;
    cvted_size[1] = image1->iheight * size;

	image3 = createppmimage(image3,cvted_size[0],cvted_size[1],image1->cmode);

	for(int j=0;j<image3->iheight;j++){
		for(int i=0;i<image3->iwidth;i++){

            int xp = (int)(i / size);
            int yp = (int)(j / size);

            if(xp < image1->iwidth && yp < image1->iheight){
                struct RGBColor trgb = getPnmPixel(image1,xp,yp);
    			setPnmPixel(image3,i,j,trgb);
            }
		}
	}
	saveppmimage(image3,"conveted.ppm");
	deleteppmimg(image1);
	deleteppmimg(image2);
	deleteppmimg(image3);

	return 0;
}
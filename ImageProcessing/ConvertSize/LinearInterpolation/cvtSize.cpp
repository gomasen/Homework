#include "ppmload.h"

float inputCvtSize(){
    float size;

    printf("���{�ɕϊ����܂����H\n: ");
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

            if(xp < image1->iwidth-1 && yp < image1->iheight-1){
                float a = i / size - xp;
                float b = j / size - yp;

                RGBColor new_color;
                new_color.R = new_color.G = new_color.B = 0;
                struct RGBColor color[4];

                color[0] = getPnmPixel(image1, xp, yp);
                color[1] = getPnmPixel(image1, xp+1, yp);
                color[2] = getPnmPixel(image1, xp, yp+1);
                color[3] = getPnmPixel(image1, xp+1, yp+1);

                unsigned color_element[4];
                RGBColor new_element;

                new_element.R = (int)((1-a)*(1-b)*color[0].R + a*(1-b)*color[1].R + (1-a)*b*color[2].R + a*b*color[3].R);
                new_color.R += new_element.R;

                new_element.G = (int)((1-a)*(1-b)*color[0].G + a*(1-b)*color[1].G + (1-a)*b*color[2].G + a*b*color[3].G);
                new_color.G += new_element.G;

                new_element.B = (int)((1-a)*(1-b)*color[0].B + a*(1-b)*color[1].B + (1-a)*b*color[2].B + a*b*color[3].B);
                new_color.B += new_element.B;

    			setPnmPixel(image3,i,j,new_color);
            }
		}
	}

	saveppmimage(image3,"conveted_0.66.ppm");

	deleteppmimg(image1);
	deleteppmimg(image2);
	deleteppmimg(image3);

	return 0;
}
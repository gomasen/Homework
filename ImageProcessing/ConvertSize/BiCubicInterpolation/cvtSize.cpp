#include "ppmload.h"

#define SHRINK
// #define EXPANSION

float inputCvtSize(){
    float size;

    printf("‰½”{‚ÉŠg‘å‚µ‚Ü‚·‚©H\n: ");
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

    int a = -0.5;

    float parameter[5];
    parameter[0] = a + 3.0;
    parameter[1] = a + 2.0;
    parameter[2] = -a * 4.0;
    parameter[3] = a * 8.0;
    parameter[4] = a * 5.0;

	for(int j=0;j<image3->iheight;j++){
		for(int i=0;i<image3->iwidth;i++){

            float x0 = i / size;
            float y0 = j / size;

            int xp = (int)(i / size);
            int yp = (int)(j / size);

            if(xp >= 1 && xp < image1->iwidth - 2 && yp >= 1 && yp < image1->iheight - 2){
                float color_element[3] = {0};
                RGBColor trgb;

                for(int k = -1; k <= 2; k++){
                    for (int l = -1; l <= 2; l++){
                        int x = xp + k;
                        int y = yp + l;

                        float disx = (x-x0 < 0) ? -(x-x0) : x-x0;
                        float disy = (y-y0 < 0) ? -(y-y0) : y-y0;

                        float weight = 0.0;

                        if (disx <= 1.0)
                            weight = 1.0 - parameter[0]*disx*disx + parameter[1]*disx*disx*disx;
                        else if (disx <= 2.0)
                            weight = parameter[2] + parameter[3]*disx + parameter[4]*disx*disx*disx;
                        else
                            continue;
                    
                        if (disy <= 1.0)
                            weight = 1.0 - parameter[0]*disy*disy + parameter[1]*disy*disy*disy;
                        else if (disy <= 2.0)
                            weight = parameter[2] + parameter[3]*disy + parameter[4]*disy*disy*disy;
                        else
                            continue;
                        
                        RGBColor rgb = getPnmPixel(image1, x, y);

                        color_element[0] += (rgb.R * weight > 255) ? 255 : rgb.R * weight;
                        color_element[1] += (rgb.G * weight > 255) ? 255 : rgb.G * weight;
                        color_element[2] += (rgb.B * weight > 255) ? 255 : rgb.B * weight;
                    }
                }

                trgb.R = color_element[0];
                trgb.G = color_element[1];
                trgb.B = color_element[2];

    			setPnmPixel(image3,i,j,trgb);
            }
		}
	}

#ifdef SHRINK
	saveppmimage(image3,"conveted_0.66.ppm");
#endif

#ifdef EXPANSION
	saveppmimage(image3,"conveted_2.7.ppm");
#endif

	deleteppmimg(image1);
	deleteppmimg(image2);
	deleteppmimg(image3);

	return 0;
}
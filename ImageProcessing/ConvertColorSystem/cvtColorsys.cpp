#include "ppmload.h"

struct CMYColor{
    unsigned char C, M, Y;
};
struct CMYKColor{
    unsigned char C, M, Y, K;
};
struct HSVColor{
    float H, S, V;
};

void Rgb2Cmy(RGBColor *rgb, CMYKColor *cmy);
void Rgb2Cmyk(RGBColor *rgb, CMYKColor *cmyk);
void Rgb2Hsv(RGBColor *rgb, HSVColor *hsv);
void Hsv2Rgb(HSVColor *hsv, RGBColor *rgb);

int main(void){
	struct ppmimg *image1=NULL,*image2=NULL,*image3=NULL;

	image1 = makeimagestruct(image1);
	image2 = makeimagestruct(image2);
	image3 = makeimagestruct(image3);

	loadppmimage("Black_hole.ppm",image1);
	cloneppmimage(image1,image2);
	image3 = createppmimage(image3,image1->iwidth,image1->iheight,image1->cmode);

	for(int j=0;j<image1->iheight;j++){
		for(int i=0;i<image1->iwidth;i++){
			struct RGBColor trgb = getPnmPixel(image1,i,j);
            struct HSVColor thsv;

            Rgb2Hsv(&trgb, &thsv);

            /*************** A ****************/
            // thsv.S = 100;
            /**********************************/
 
            /*************** B ****************/
            // if (thsv.H > 180) thsv.H -= 180;
            // else              thsv.H += 180;
            /**********************************/

            Hsv2Rgb(&thsv, &trgb);

			setPnmPixel(image3,i,j,trgb);
		}
	}

	// saveppmimage(image3,"cvtColorsys_A.ppm");
	// saveppmimage(image3,"cvtColorsys_B.ppm");
	saveppmimage(image3,"cvtColorsys.ppm");

	deleteppmimg(image1);
	deleteppmimg(image2);
	deleteppmimg(image3);

	return 0;
}

void Rgb2Cmy(RGBColor *rgb, CMYColor *cmy){
    cmy->C = 255 - rgb->R;
    cmy->M = 255 - rgb->G;
    cmy->Y = 255 - rgb->B;
}

unsigned char min(unsigned char c, unsigned char m, unsigned char y){
    if (c <= m && c <= y) return c;
    if (m <= c && m <= y) return m;
    if (y <= c && y <= m) return y;
}

void Rgb2Cmyk(RGBColor *rgb, CMYKColor *cmyk){
    cmyk->C = 255 - rgb->R;
    cmyk->M = 255 - rgb->G;
    cmyk->Y = 255 - rgb->B;
    cmyk->K = min(cmyk->C, cmyk->M, cmyk->Y);
}

unsigned char Max(unsigned char r, unsigned char g, unsigned char b){
    if (r >= g && r >= b) return r;
    if (g >= r && g >= b) return g;
    if (b >= r && b >= g) return b;
}
unsigned char Min(unsigned char r, unsigned char g, unsigned char b){
    if (r <= g && r <= b) return r;
    if (g <= r && g <= b) return g;
    if (b <= r && b <= g) return b;
}

void Rgb2Hsv(RGBColor *rgb, HSVColor *hsv){
    unsigned char max, min;

    int r, g, b;

    max = Max(rgb->R, rgb->G, rgb->B);
    min = Min(rgb->R, rgb->G, rgb->B);
    
    hsv->S = float(max - min) / max * 100;
    hsv->V = max / 255.0 * 100;

    if (rgb->R == rgb->G && rgb->G == rgb->B){
        hsv->H = 0;
    }
    else if (max == rgb->R){
        hsv->H = 60 * (rgb->G - rgb->B) / (max - min) + 0; 
    }
    else if (max == rgb->G){
        hsv->H = 60 * (rgb->B - rgb->R) / (max - min) + 120; 
    }
    else if (max == rgb->B){
        hsv->H = 60 * (rgb->R - rgb->G) / (max - min) + 240; 
    }

    if (hsv->H < 0) hsv->H += 360;
}

void Hsv2Rgb(HSVColor *hsv, RGBColor *rgb){
    int Hi, F, M, N, K;
    int max, min;

    max = hsv->V / 100.0 * 255;
    min = max - ((hsv->S / 100.0) * max);

    if (0 <= hsv->H < 60){
        rgb->R = max;
        rgb->G = (hsv->H / 60.0) * (max - min) + min;
        rgb->B = min;
    }
    else if (hsv->H < 120){
        rgb->R = ((120 - hsv->H) / 60.0) * (max - min) + min;
        rgb->G = max;
        rgb->B = min;
    }
    else if (hsv->H < 180){
        rgb->R = min;
        rgb->G = max;
        rgb->B = ((hsv->H - 120) / 60.0) * (max - min) + min;
    }
    else if (hsv->H < 240){
        rgb->R = min;
        rgb->G = ((240 - hsv->H) / 60.0) * (max - min) + min;
        rgb->B = max;
    }
    else if (hsv->H < 300){
        rgb->R = ((hsv->H - 240) / 60.0) * (max - min) + min;
        rgb->G = min;
        rgb->B = max;
    }
    else if (hsv->H < 360){
        rgb->R = min;
        rgb->G = max;
        rgb->B = ((360 - hsv->H) / 60.0) * (max - min) + min;
    }
}
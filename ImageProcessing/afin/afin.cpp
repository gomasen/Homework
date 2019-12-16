#include "ppmload.h"

struct parameter{
	float a, b, c, d;
	float m, n;
};

parameter inputParameter();

int main(void){
	struct ppmimg *image1=NULL,*image2=NULL,*image3=NULL;
	struct parameter p;

	image1 = makeimagestruct(image1);
	image2 = makeimagestruct(image2);
	image3 = makeimagestruct(image3);

	loadppmimage("Black_hole.ppm",image1);
	cloneppmimage(image1,image2);

	image3 = createppmimage(image3,image1->iwidth,image1->iheight,image1->cmode);

	p = inputParameter();

	float d = p.a*p.d - p.b*p.c;
	printf("d = %f\n", d);

	float revA[2][2] = {0};
	
	if (d != 0){
		revA[0][0] = 1 / d * p.d;
		revA[0][1] = 1 / d * -p.b;
		revA[1][0] = 1 / d * -p.c;
		revA[1][1] = 1 / d * p.a;
	}

	for(int j=0;j<image1->iheight;j++){
		int x, y;
		x = y = 0;
		for(int i=0;i<image1->iwidth;i++){
			struct RGBColor rgb;

			if (d == 0){
				x = i-p.m;
				y = j-p.n;
			}
			else{
				x = revA[0][0]*(i-p.m) + revA[0][1]*(j-p.n) + 0.5;
				y = revA[1][0]*(i-p.m) + revA[1][1]*(j-p.n) + 0.5;		
			}

			if (x > 0 && x <= image1->iwidth && y > 0 && y <= image1->iheight)
				rgb = getPnmPixel(image1, x, y);
			else
				rgb.R = rgb.G = rgb.B = 255;

			setPnmPixel(image3,i,j,rgb);
		}
	}

	saveppmimage(image3,"afin.ppm");

	deleteppmimg(image1);
	deleteppmimg(image2);
	deleteppmimg(image3);

	return 0;
}

parameter inputParameter(){
	parameter p;
	
	puts("s—ñ‚Ì—v‘f‚ğ“ü—Í‚µ‚Ä‚­‚¾‚³‚¢");
	printf("A[0][0] : "); scanf("%f", &p.a);
	printf("A[0][1] : "); scanf("%f", &p.b);
	printf("A[1][0] : "); scanf("%f", &p.c);
	printf("A[1][1] : "); scanf("%f", &p.d);

	puts("•½sˆÚ“®—Ê‚ğ“ü—Í‚µ‚Ä‚­‚¾‚³‚¢");
	printf("B[0] : "); scanf("%f", &p.m);
	printf("B[1] : "); scanf("%f", &p.n);

	return p;
}
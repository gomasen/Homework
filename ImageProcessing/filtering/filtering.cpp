#include "ppmload.h"

enum METHOD{
	RANK, MIDDLE, MODE, GAUSSIAN, SHARP
};

int selectMethodForFiltering(){
	int method;

	printf("どの方法でフィルタリングを書けますか？\n");
	printf("0 -> ランク値フィルタ\n");
	printf("1-> 中央値フィルタ\n");
	printf("2 -> 最頻値フィルタ\n");
	printf("3 -> ガウシアンフィルタ\n");
	printf("4 -> 鮮鋭化フィルタ\n");

	scanf("%d", &method);

	return method;
}

void setNumToFilter(RGBColor filter[][3], ppmimg *image1, int x, int y){
	if ((x >= 1 && y >= 1) || (x < image1->iwidth-1 && y < image1->iheight-1)){
		for (int j = 0; j < 3; j++){
			for (int i = 0; i < 3; i++){
				filter[j][i] = getPnmPixel(image1, x-i-1, y-j-1);
			}
		}
	}
	else{
		for (int j = 0; j < 3; j++){
			for(int i = 0; i < 3; i++){
				if (0 > x-i-1 < image1->iwidth-1 || 0 > y-j-1 < image1->iheight-1){
					filter[j][i].R = 0;
					filter[j][i].G = 0;
					filter[j][i].B = 0;
				}
				else
					filter[j][i] = getPnmPixel(image1, x-i-1, y-j-1);
			}
		}
	}
}

unsigned long counterSwap = 0;
unsigned long counterComp = 0;

int compare(int a, int b)
{
	counterComp++;
	return (a<b);
}

void swap(int *d, int a, int b)
{
	int tmp;

	counterSwap++;
	tmp = d[a];
	d[a] = d[b];
	d[b] = tmp;
}

void quicksort(int *data, int left, int right)
{
	int pivot;
	int small, large;

	if (left < right) {
		small = left;
		large = right;
		pivot = data[(left + right) / 2];
		while (small <= large){
			while (compare(data[small], pivot)) small++;
			while (compare(pivot, data[large])) large--;
			if (small <= large){
				swap(data, small++, large--);

			}
		}

		if (left < large)  quicksort(data, left, large);
		if (small < right) quicksort(data, small, right);
	}
}

void calcRankFilter(RGBColor filter[][3]){
	int sort[9];
	int k = 0;

	for(int j = 0; j < 3; j++){
		for(int i = 0; i < 3; i++){
			sort[k++] = filter[j][i].R;
		}
	}

	quicksort(sort, 0, 8);

	for(int j = 0; j < 3; j++){
		for(int i = 0; i < 3; i++){
			if (filter[j][i].R != 0){
				filter[j][i].R = sort[0];
				filter[j][i].G = sort[0];
				filter[j][i].B = sort[0];
			}
		}
	}

}

void calcMiddleFilter(RGBColor filter[][3]){
	int sort[9];
	int k = 0;

	for(int j = 0; j < 3; j++){
		for(int i = 0; i < 3; i++){
			sort[k++] = filter[j][i].R;
		}
	}

	quicksort(sort, 0, 8);

	for(int j = 0; j < 3; j++){
		for(int i = 0; i < 3; i++){
			if (filter[j][i].R != 0){
				filter[j][i].R = sort[5];
				filter[j][i].G = sort[5];
				filter[j][i].B = sort[5];
			}
		}
	}

}

void calcModeFilter(RGBColor filter[][3]){
	int val[255] = {0};
	int mode = 0;

	for(int j = 0; j < 3; j++){
		for(int i = 0; i < 3; i++){
			val[filter[j][i].R]++;
		}
	}

	for(int i = 0; i < 255; i++){
		if(val[i] > val[mode]) mode = i;
	}

	for(int j = 0; j < 3; j++){
		for(int i = 0; i < 3; i++){
			if (filter[j][i].R != 0){
				filter[j][i].R = mode;
				filter[j][i].G = mode;
				filter[j][i].B = mode;
			}
		}
	}

}

void calcGaussianFilter(RGBColor filter[][3]){
	int sum = 0;
	int gaussian[3][3] = {{1,2,1}, {2,4,2}, {1,2,1}};

	for(int j = 0; j < 3; j++){
		for(int i = 0; i < 3; i++){
			sum += filter[j][i].R * gaussian[j][i];
		}
	}

	sum /= 16;

	for(int j = 0; j < 3; j++){
		for(int i = 0; i < 3; i++){
			if (filter[j][i].R != 0){
				filter[j][i].R = sum;
				filter[j][i].G = sum;
				filter[j][i].B = sum;
			}
		}
	}

}

void calcSharpFilter(RGBColor filter[][3]){
	double sum = 0;
	double sharp[3][3] = {{0.0,-1.0,0.0}, {-1.0,5.0,-1.0}, {0.0,-1.0,0.0}};

	for(int j = 0; j < 3; j++){
		for(int i = 0; i < 3; i++){
			sum += filter[j][i].R * sharp[j][i];
		}
	}

	(sum < 0) ? sum = 0 : sum = sum;
	(sum > 255) ? sum = 255 : sum = sum;

	for(int j = 0; j < 3; j++){
		for(int i = 0; i < 3; i++){
			if (filter[j][i].R != 0){
				filter[j][i].R = sum;
				filter[j][i].G = sum;
				filter[j][i].B = sum;
			}
		}
	}

}

int main(void){
	struct ppmimg *image1=NULL,*image2=NULL,*image3=NULL;
	int method = selectMethodForFiltering();
	RGBColor filter[3][3];

	image1 = makeimagestruct(image1);
	image2 = makeimagestruct(image2);
	image3 = makeimagestruct(image3);

	if (method == MIDDLE) loadppmimage("inunoise.pgm",image1);
	else				  loadppmimage("inussg.pgm",image1);
	cloneppmimage(image1,image2);

	image3 = createppmimage(image3,image1->iwidth,image1->iheight,image1->cmode);

	for(int j=0;j<image1->iheight;j++){
		for(int i=0;i<image1->iwidth;i++){
			setNumToFilter(filter, image1, i, j);			

			switch(method){
				case RANK:
					calcRankFilter(filter); break;
				case MIDDLE:
					calcMiddleFilter(filter); break;
				case MODE:
					calcModeFilter(filter); break;
				case GAUSSIAN:
					calcGaussianFilter(filter); break;
				case SHARP:
					calcSharpFilter(filter); break;
			}

			setPnmPixel(image3,i,j,filter[1][1]);
		}
	}


	switch(method){
		case RANK:
			saveppmimage(image3,"rank.pgm"); break;
		case MIDDLE:
			saveppmimage(image3,"middle.pgm"); break;
		case MODE:
			saveppmimage(image3,"mode.pgm"); break;
		case GAUSSIAN:
			saveppmimage(image3,"gaussian.pgm"); break;
		case SHARP:
			saveppmimage(image3,"sharp.pgm"); break;
	}

	deleteppmimg(image1);
	deleteppmimg(image2);
	deleteppmimg(image3);

	return 0;
}
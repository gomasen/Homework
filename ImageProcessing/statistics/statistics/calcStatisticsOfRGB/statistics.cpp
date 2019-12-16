#include "ppmload.h"

// #define GRAY
// #define RED
// #define GREEN
#define BLUE

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


float calcAverage(ppmimg *image){
	int sum = 0;

	for (int j = 0; j < image->iheight; j++){
		for (int i = 0; i < image->iwidth; i++){

			struct RGBColor trgb = getPnmPixel(image, i, j);

#ifdef GRAY 
			sum += trgb.R;
#endif

#ifdef RED
			sum += trgb.R;
#endif

#ifdef GREEN
			sum += trgb.G;
#endif

#ifdef BLUE
			sum += trgb.B;
#endif
		}
	}

	return sum / (image->iwidth * image->iheight);
}

float calcVariance(ppmimg *image, float average){

	int sum = 0;

	for (int j = 0; j < image->iheight; j++){
		for (int i = 0; i < image->iwidth; i++){

			struct RGBColor trgb = getPnmPixel(image, i, j);

#ifdef GRAY
			sum += pow(trgb.R - average, 2);
#endif

#ifdef RED
			sum += pow(trgb.R - average, 2);
#endif

#ifdef GREEN
			sum += pow(trgb.G - average, 2);
#endif

#ifdef BLUE
			sum += pow(trgb.B - average, 2);
#endif

		}
	}

	return sum / (image->iwidth * image->iheight);
}

void substitution(int *val, ppmimg *image){

	for (int j = 0; j < image->iheight; j++){
		for (int i = 0; i < image->iwidth; i++){
			struct RGBColor trgb = getPnmPixel(image, i, j);

#ifdef GRAY
			val[trgb.R]++;
#endif

#ifdef RED
			val[trgb.R]++;
#endif

#ifdef GREEN
			val[trgb.G]++;
#endif

#ifdef BLUE
			val[trgb.B]++;
#endif
		}
	}
}

int calcMinimun(int *val){
	for (int i = 0; i < 256; i++){
		if (val[i] != 0)
			return i;
	}
}

int calcMaximam(int *val){
	for (int i = 255; i >= 0; i--){
		if (val[i] != 0)
			return i;
	}
}

float calcMedian(int *val, int max){
	int count = 0;

	for (int i = 0; i < 256; i++){
		count += val[i];
		if (count >= max / 2)
			return i;
	}
}

float calcMode(int *val){
	int max = 0;

	for (int i = 0; i < 256; i++){
		if (val[max] < val[i])
			max = i;
	}

	return max;
}

int main(void){
	struct ppmimg *image1 = NULL, *image2 = NULL;

	image1 = makeimagestruct(image1);
	image2 = makeimagestruct(image2);

#ifdef GRAY
	loadppmimage("NTSC_BlackHole.ppm", image1);
#endif

#ifdef RED
	loadppmimage("RedBlackHole.ppm", image1);
#endif

#ifdef GREEN
	loadppmimage("GreenBlackHole.ppm", image1);
#endif

#ifdef BLUE
	loadppmimage("BlueBlackHole.ppm", image1);
#endif

	cloneppmimage(image1, image2);

	float average, variance;
	average = calcAverage(image1);
	variance = calcVariance(image1, average);

	int val[256] = { 0 };
	substitution(val, image1);

	int min, max;
	min = calcMinimun(val);
	max = calcMaximam(val);
	
	float median;
	int max_index = image1->iwidth * image1->iheight - 1;
	median = calcMedian(val, max_index);
	
	float mode;
	mode = calcMode(val);

	printf("average = %f, variance = %f\n", average, variance);
	printf("MaximamValue = %d, MinimumValue = %d\n", max, min);
	printf("median = %f, mode = %f\n", median, mode);

	deleteppmimg(image1);
	deleteppmimg(image2);

	return 0;
}
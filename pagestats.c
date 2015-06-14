#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
# include "lru.c"
# include "queue.c"
# include "extra.c"

int x [10000];
int sizeOfArray = 0;
FILE *myfile;


void pagestatistics (int frameMin, int frameMax, int increm, int pagesim, int pagestat);


int main (int argc, char *argv[]) {


	int min;
	int max;
	int increment;
	int pagesim = 0;
	int pagestat = 1;
	FILE *myfile;

	printf("\n");

	//not enough or too many args
	if (argc < 5) {
		printf("ERROR: There are not enough command line arguments\n");
		exit(0);
	}
	else if (argc > 5	) {
		printf("ERROR: There are too many command line arguments\n");
		exit(0);
	}

	//incorrect page frame input
	if (sscanf(argv[1], "%d", &min) && sscanf(argv[2], "%d", &max)) {
		if (min > max) {
			printf("ERROR: Minimum cannot be greater than the max page references\n");
			exit(0);
		}
		else if (min > 100 || max > 100) {
			printf("ERROR: Total number of physical memory frames can't be greater than 100\n");
			exit(0);
		}
		else if (min < 2 || max < 2) {
			printf("ERROR: Total number of physical memory frames can't be less than 2\n");
			exit (0);
		}
	}

	//incorrect increment 
	if (sscanf(argv[3], "%d", &increment)) {
		if (increment < 1) {
			printf("ERROR: Increment input is not a positive number\n");
			exit (0);
		}
	}
	else {
		printf("ERROR: Increment input is not an int value\n");
	}

	//input file errors
	if ( (myfile = fopen (argv[4],"r")) == NULL) {
		printf("ERROR: Incorrect file name\n");
		exit(0);
	}

	//copy textfile into array
	int num;
	int j = 0;

	//input file exists but is empty 
	while (fscanf(myfile, "%d",&num) > 0) {
		x[j] = num;
		j++;
		sizeOfArray++;
	}
	fclose(myfile);

	pagestatistics (min, max, increment, pagesim, pagestat);


	return 0;
}

void pagestatistics (int frameMin, int frameMax, int increm, int pagesim, int pagestat) {
	int i;
	int row = 4;
	int j;
	int col = ((frameMax-frameMin)/increm)+1;
	int frame = frameMin;
	if ( (myfile = fopen ("pagestats.txt","w")) == NULL) {
		printf("Error opening file\n");
		exit (0);
	}

	for (i = 0; i < row; i++) {
		frame = frameMin;
		fprintf(myfile,"\n");
		printf("\n");
		for (j = 0; j < col; j++) {
			if (i == 0) {
				fprintf(myfile,"%4d", frame);
				fprintf(myfile,"%2s","");
				frame+=increm;
			}
			else if (i == 1){
				int capacity = frame;
				initQueue(capacity); 
				fifo (frame, x, sizeOfArray, pagesim, pagestat, myfile);
				frame += increm;
			}
			else if (i == 2) {
				int capacity = frame;
				initArray(capacity); 
				lrufunc (frame, x, sizeOfArray, pagesim, pagestat, myfile);
				frame += increm;
			} 
			else if (i == 3) {
				int capacity = frame;
				initializeSec(capacity); 
				secondChance (frame, x, sizeOfArray, pagesim, pagestat, myfile);
				frame += increm;
		}
	}

}


}








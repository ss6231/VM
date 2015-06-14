#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.c"
#include "lru.c"
# include "extra.c"

//initialize variables that are created in this file 
//note that x is the array that stores the page references found in the input file 
int x [10000];
int sizeOfArray = 0;

void pagesimulator (int frameMax, char *algo, int pagesim, int pagestat);


int main (int argc, char *argv[]) {
	
	int capacity;
	FILE *myfile;
	char *algorithm = NULL;
	int pagesim = 1;
	int pagestat = 0;

	printf("\n");

	//not enough or too many args
	if (argc < 4) {
		printf("ERROR: There are not enough command line arguments\n");
		exit(EXIT_SUCCESS);
	}
	else if (argc > 4) {
		printf("ERROR: There are too many command line arguments\n");
		exit(EXIT_SUCCESS);
	}

	//input file errors
	if ( (myfile = fopen (argv[2],"r")) == NULL) {
		printf("ERROR: Incorrect file name\n");
		exit(EXIT_SUCCESS);
	}

	//incorrect page frame input
	if (sscanf(argv[1], "%d", &capacity)) {
		if (capacity > 100) {
			printf("ERROR: Total number of physical memory frames can't be greater than 100\n");
			exit(EXIT_SUCCESS);
		}
		else if (capacity < 1) {
			printf("ERROR: Total number of physical memory frames can't be less than 1\n");
			exit (EXIT_SUCCESS);
		}
	}

	//incorrect lru or fifo argument
	if (strcmp(argv[3], "fifo") != 0 && strcmp(argv[3], "lru")!= 0 && strcmp(argv[3], "extra")!= 0 ) {
		printf("ERROR: Invalid page replacement algorithm\n");
		exit(EXIT_SUCCESS);
	}

	int num;

	//copy textfile into array
	int j = 0;
	while (fscanf(myfile, "%d",&num) > 0) {
		x[j] = num;
		j++;
		sizeOfArray++;
	}
	fclose(myfile);

	if (strcmp(argv[3], "fifo") == 0) {
		algorithm = "fifo";
	}
	else if (strcmp(argv[3], "lru") == 0) {
		algorithm = "lru";
	}
	else if (strcmp(argv[3], "extra") == 0)
		algorithm = "extra";

	//call pagesim algorithm
	pagesimulator (capacity, algorithm, pagesim, pagestat);


	return 0;
}

void pagesimulator (int frameMax, char *algo, int pagesim, int pagestat) {
	int capacity;
	//pagesim for fifo input
	if (strcmp(algo, "fifo") == 0) {
		capacity = frameMax;
		initQueue(capacity);
		//the last argument in fifo () expects a file to write to, which is needed in pagestats.c but not in pagesim so NULL is being passed
		fifo(capacity,x,sizeOfArray,pagesim, pagestat, NULL);
	}
	//pagesim for lru input
	else if (strcmp(algo, "lru") == 0) {
		capacity = frameMax;
		initArray(capacity);
		//NULL as the last argument is used because pagesim does not write to a file
		lrufunc (capacity,x, sizeOfArray, pagesim, pagestat, NULL);
	}
	else if (strcmp(algo, "extra") == 0) {
		capacity = frameMax;
		initializeSec(frameMax);
		//the last argument in fifo () expects a file to write to, which is needed in pagestats.c but not in pagesim so NULL is being passed
		secondChance(capacity,x,sizeOfArray,pagesim, pagestat, NULL);
	}

}








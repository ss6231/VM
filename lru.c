#include <stdio.h>
#include <string.h>

typedef struct {
	int num;
	int timeAdded;

} lru;


lru array [10000];
int capacity;
int time = 0;
int idex = 0;

void toString2 (int);
int inCache (int);
int replaceSmallest (int, int, int);
void initArray (int cap);
void lrufunc (int cap, int x[], int sizeOfArray, int pagesim, int pagestat, FILE *myfile);

int inCache (int item) {
	idex = 0;
	int i;
	int inCache = 0;
	lru *pointer = array;
	for (i = 0; i < capacity; i++) {
		if (pointer->num == item) {
			inCache = 1;
			idex = i;
			break;
		}
		pointer++;
	}
	return inCache;
}

int replaceSmallest (int x, int time, int capacity) {
	int i;
	int replace = 0;
	int pagefault = 0;
	lru *pointer = array;
	int leastused = pointer->timeAdded;
	if (inCache(x)) {
		(pointer+idex)->timeAdded = time++;
		pagefault = 0;
		return pagefault;
	}
	pagefault = 1;
	for (i = 0; i < capacity; i++) {
		if ((pointer->timeAdded) < leastused) {
			leastused = pointer->timeAdded;
			replace = i;
		}
		pointer++;
	}
	pointer = array;
	(pointer + replace)->num = x;
	(pointer+replace)->timeAdded = time++;
	return pagefault;
}

void initArray (int cap) {
	lru *ptr = array;
	int i;
	time = 0;
	for (i = 0; i < cap; i++) {
		ptr->num = -1;
		ptr->timeAdded = 0;
		ptr++;
	}
}

void toString2 (int a) {
	int j;
	lru *ptr = array;
	for (j = 0; j < capacity; j++) {
		if (ptr->num != -1) {
			if (j == capacity-1) {
			printf("%2d]  ",ptr->num);
				if (a == 1) {
					printf("F");
				}
				printf("\n");
			}
			else {
				printf("%2d|",ptr->num);
			}
		}
		else {
			if (j == capacity-1) {
				printf("  ]  ");
				if (a == 1) {
					printf("F");
				}
				printf("\n");
			}
			else {
				printf("  |");
			}
		}
		ptr++;
	
	}
}

void lrufunc (int cap, int x [], int sizeOfArray, int pagesim, int pagestat, FILE *myfile) {
	int denominator = 0;
	int spaces = 2;
	capacity = cap;
	int pagefault;
	int numPageFaults = 0;
	lru* ptr = array;
	int i;
	for (i = 0; i < sizeOfArray; i++) {
		pagefault = 0;
		if (x[i] < 0) {
			printf("ERROR: %d is not a valid page reference\n", x[i]);
			continue;
		}
		if (!inCache(x[i]) && time < capacity) {
			ptr->num = x[i];
			ptr->timeAdded = time++;
			ptr++;
		}

		else if (time >= capacity) {
			denominator++;
			pagefault = replaceSmallest (x[i], time, capacity);
			if (pagefault == 1) {
				numPageFaults++;
			}
			else {
				time++;
			}
		}
		if (pagesim == 1) {
			printf("%2d:  [",x[i]);
			toString2(pagefault);
		}
	}
	
	if (pagesim == 1) {
		printf("\nMiss rate: %.2f%% \n\n", (float)numPageFaults/denominator*100);
	}
	else if (pagestat == 1) {
		fprintf(myfile, "%*.2f ",spaces,(float)numPageFaults/denominator*100);
		printf("LRU, %d frames: Miss rate = %d / %d = %.2f%%\n",capacity,numPageFaults, denominator, (float)numPageFaults/denominator*100);
	}

}








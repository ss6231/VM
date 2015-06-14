#include <stdio.h>

typedef struct {
	int num;
	int rbit;

} secchance;

secchance secQueue[100];
int f = 0;
int b = 0;
int max;
int sizeofQ;
int ind;


void add (int item);
void delete ();
void initializeSec (int);
void secondChance (int capacity, int x [],int sizeOfArray,int pagesim, int pagestat, FILE *myfile);
int inQ (int);
void printOut (int);



void initializeSec (int cap) {
	int i;
	f = 0;
	b = 0;
	sizeofQ = 0;
	secchance *ptr = secQueue;
	for (i = 0; i < cap; i++) {
		ptr->num = -1;
		ptr->rbit = 0;
		ptr++;
	}
}

void add (int item) {
	secchance *pointer = secQueue;
	(pointer+b)->num = item;
	(pointer+b)->rbit = 1;
	sizeofQ++;
	b=(b+1)%max;
}

void delete () {
	f=(f+1)%max;
	sizeofQ--;
}

int inQ (int x) {
	int i;
	int inQueue = 0;
	secchance *ptr = secQueue;
	for (i = 0; i < sizeofQ; i++) {
		if (ptr->num == x) {
			ind = i;
			inQueue = 1;
			return inQueue;
		}
		ptr++;
	}
	return inQueue;
}


void secondChance (int capacity, int x [],int sizeOfArray,int pagesim, int pagestat, FILE *myfile) {
	secchance* pointer = secQueue;
	max = capacity;
	int denominator = 0;
	int numPageFaults = 0;
	int sp = 3;
	int pagefault;
	int i;
	for (i = 0; i < sizeOfArray; i++) {
		pagefault = 0;
		if (x[i] < 0) {
			printf("ERROR: %d is not a valid page reference\n", x[i]);
			continue;
		}
		if (!inQ(x[i]) && sizeofQ < max) {
			add(x[i]);
		}

		else if (inQ(x[i]) && sizeofQ == capacity) {
			denominator++;
			if ((pointer+ind)->rbit == 0) {
				(pointer+ind)->rbit = 1;
			}
			if (ind == b) {
				b = (b+1)%max;
			}
			pagefault = 0;
		}
		else if (!inQ(x[i]) && sizeofQ == capacity) {

			pagefault = 1;
			denominator++;
			numPageFaults++;
			while ((pointer+b)->rbit == 1) {
				(pointer+b)->rbit=0;
				b = (b+1)%max;
			}
			delete();
			add(x[i]);
		}
		if (pagesim == 1) {
			printf ("%2d: [", x[i]);
			printOut(pagefault);
		}

	}
	if (pagesim == 1) {
	printf("\nMiss rate: %.2f%% \n\n", (float)numPageFaults/denominator*100);
	}
	else if (pagestat == 1) {
		fprintf(myfile, "%*.2f ",sp,(float)numPageFaults/denominator*100);
		printf("EXTRA, %d frames: Miss rate = %d / %d = %.2f%%\n",capacity,numPageFaults, denominator, (float)numPageFaults/denominator*100);
	}
}


	void printOut (int a){
		int j;
		secchance *ptr = secQueue;
		for (j = 0; j < max; j++) {
			if (ptr->num != -1) {
				if (j == max-1) {
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
				if (j == max-1) {
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




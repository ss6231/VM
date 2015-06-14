# include <stdio.h>



int queue [100];
int capacity;
int size;
int front;
int back;


void enqueue (int);
int dequeue ();
void toString (int);
int inQueue(int);
void initQueue (int);
void fifo (int cap, int x [], int sizeOfArray, int pagesim, int pagestat, FILE *myfile);


void enqueue (int x) {
		queue[back] = x;
		size++;
		back = (back+1)%capacity;

}

int dequeue () {
	int item = queue[front];
	front = (front+1)%capacity;
	size--;
	return item;

}

void initQueue (int cap) {
	front = 0;
	back = 0;
	size = 0;
	int i;
	for (i = 0; i < cap; i++) {
		queue[i] = -1;
	}
	
}

int inQueue (int a) {
	int i; 
	int inQueue = 0;
	for (i = 0; i < size; i++) {
		if (a == queue[i]) {
			inQueue = 1;
		}
	}
	return inQueue;
}

void toString (int a) {
	int j;
	for (j = 0; j < capacity; j++) {
		if (queue[j] != -1) {
			if (j == capacity-1) {
			printf("%2d]  ",queue[j]);
				if (a == 1) {
					printf("F");
				}
				printf("\n");
			}
			else {
				printf("%2d|",queue[j]);
			}
		}
		//else queue[j] is 0 either because the queue is empty at this index or because the input is actually 0
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
	}
	
	}

void fifo (int cap, int x [], int sizeOfArray, int pagesim, int pagestat, FILE *myfile) {
	int denominator = 0;
	int numPageFaults = 0;
	int space = 3;
	int pagefault;
	int i;
	capacity = cap;
	for (i = 0; i < sizeOfArray; i++) {
		pagefault = 0;
		if (x[i] < 0) {
			printf("ERROR: %d is not a valid page reference\n", x[i]);
			continue;
		}
		if (!inQueue(x[i]) && size < capacity) {
			enqueue(x[i]);
		}
		else if (inQueue(x[i]) && size == capacity) {
			denominator++;
		}
		else if (!inQueue(x[i]) && size == capacity) {
			pagefault = 1;
			denominator++;
			numPageFaults++;
			int deq = dequeue();
			enqueue(x[i]);
		}
		if (pagesim == 1) {
			printf ("%2d: [", x[i]);
			toString(pagefault);
		}
	}
	if (pagesim == 1) {
		printf("\nMiss rate: %.2f%% \n\n", (float)numPageFaults/denominator*100);
	}
	else if (pagestat == 1) {
		fprintf(myfile, "%*.2f ",space,(float)numPageFaults/denominator*100);
		printf("FIFO, %d frames: Miss rate = %d / %d = %.2f%%\n",capacity,numPageFaults, denominator, (float)numPageFaults/denominator*100);
	}

}

READ ME

1) lru.c, queue.c, and secchance.c should be compiled separately with -c command in gcc
2) Then run pagesim.c with the following arguments: 1) the total number of physical memory
frames (maximum 100), 2) an input filename where a sequence of page refereces is stored, 3) the chosen algorithm, either 'lru', 'fifo', or 'extra' for clock algorithm. The output will print the simulation of a page replacement that occurs in VM.
3) Then do the same for pagestats.c with the following arguments:  1) the minimum number of frames
(no less than 2), 2) the maximum number of frames (no more than 100), 3) the frame number increment (positive
integer), 4) the input file name containing the page references. The output will print out lru, fifo, and clock algorithm miss rates.
4) pageseq.out is the randomly generated sequence of numbers 
5) pagestats.txt is the output file produces from pagestats.c



*NOTE ABOUT CLOCK ALGORITHM:

The clock algorithm is an approximation on FIFO and LRU in addition to having a pointer to the potential next victim for replacement. Initially, when a page is loaded, it's rbit is set to 1. When a page is looking to be replaced, the first thing that is checked is its rbit. If it is 0, it is replaced, otherwise the rbit is set to 0 and the next victim is advanced to the next page until the pointer comes across a page that has a 0 rbit. This is implemented similarly to a circular queue. As the name suggests, the algorithm gives a "second chance" to each page. An old page that has been referenced is probably in use and should not be swapped instead of a new page that has yet to be referenced. In terms of its efficiency, the clock algorithm runs slightly better than FIFO when viewed over time (evidently so with the existence of the rbit). 

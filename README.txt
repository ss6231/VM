READ ME

1) lru.c, queue.c, and secchance.c should be compiled separately with -c command in gcc
2) Then compile and run page.c with the desired command line arguments (the valid algorithm command line args are "lru", "queue", or "extra")
3) Then do the same for pagestats.c
4) pageseq.out is the randomly generated sequence of numbers from pagegenerator.c
5) pagestats.txt is the output file produces from pagestats.c



*NOTE ABOUT EXTRA CREDIT:
I implemented the second chance/clock algorithm, which is an approximation of FIFO and LRU but with using 1 rbit for each page. There were many different ways to implement this algorithm which resulted in different frame outputs, but I went with the one described here: http://courses.cs.tamu.edu/bart/cpsc410/Supplements/Slides/page-rep3.pdf

The clock algorithm is an approximation on FIFO and LRU in addition to having a pointer to the potential next victim for replacement. Initially, when a page is loaded, it's rbit is set to 1. When a page is looking to be replaced, the first thing that is checked is its rbit. If it is 0, it is replaced, otherwise the rbit is set to 0 and the next victim is advanced to the next page until the pointer comes across a page that has a 0 rbit. This is implemented similarly to a circular queue. As the name suggests, the algorithm gives a "second chance" to each page. An old page that has been referenced is probably in use and should not be swapped instead of a new page that has yet to be referenced. In terms of its efficiency, the clock algorithm runs slightly better than FIFO when viewed over time (evidently so with the existence of the rbit). 
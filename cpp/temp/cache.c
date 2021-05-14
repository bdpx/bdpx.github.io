
#include <stdio.h>
//#include <sys/times.h>
//#include <sys/types.h>
#include <time.h>

#define CACHE_MIN (1024) /* smallest cache */
#define CACHE_MAX (1024*1024) /* largest cache */
#define SAMPLE 10 /* to get a larger time sample */

int x[CACHE_MAX]; /* array going to stride through */

double get_seconds(void)
{ /* routine to read time */
return (double)clock()/CLOCKS_PER_SEC;
}

void main() {
int register i, index, stride, limit, temp;
int steps, tsteps, csize;
double sec0, sec; /* timing variables */
for (csize=CACHE_MIN; csize <= CACHE_MAX; csize=csize*2)
for (stride=1; stride <= csize/2; stride=stride*2) {
sec = 0; /* initialize timer */
limit = csize-stride+1; /* cache size this loop */
steps = 0;
do { /* repeat until collect 1 second */
sec0 = get_seconds(); /* start timer */
for (i=SAMPLE*stride;i!=0;i=i-1) /* larger sample */
for (index=0; index < limit; index=index+stride)
x[index] = x[index] + 1; /* cache access */
steps = steps + 1; /* count while loop iterations */
sec = sec + (get_seconds() - sec0);/* end timer */

} while (sec < 1.0); /* until collect 1 second */
/* Repeat empty loop to subtract loop overhead */
tsteps = 0; /* used to match no. while iterations */
do { /* repeat until same no. iterations as above */
sec0 = get_seconds(); /* start timer */
for (i=SAMPLE*stride;i!=0;i=i-1) /* larger sample */
for (index=0; index < limit; index=index+stride)
temp = temp + index; /* dummy code */
tsteps = tsteps + 1; /* count while iterations */
sec = sec - (get_seconds() - sec0);/* - overhead */
} while (tsteps<steps); /* until = no. iterations */
printf("Size:%7d Stride:%7d read+write:%4.0lf ns\n",
csize*sizeof(int), stride*sizeof(int), (double)
sec*1e9/(steps*SAMPLE*stride*((limit-1)/stride+1)));
}; /* end of both outer for loops */
}
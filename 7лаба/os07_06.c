#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

int main() {
	int count = 0;
	struct timespec start, end, process;
	clock_gettime(CLOCK_REALTIME, &start);
	for (;;) {
		count++;
		clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &process);
		if (process.tv_sec == 2) break;
	}
	clock_gettime(CLOCK_REALTIME, &end);
	printf("iterations: %d\n", count);
	printf("time: %ld ns\n", (end.tv_sec * 1000000000 + end.tv_nsec) - (start.tv_sec * 1000000000 + start.tv_nsec));

	exit(0);
}

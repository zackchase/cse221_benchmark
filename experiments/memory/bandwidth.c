#include <time.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <inttypes.h>

#define THRESHOLD 10000000000000000

static __inline__ unsigned long long int rdtsc(void)
{
    unsigned long long int x;
    __asm__ volatile (".byte 0x0f, 0x31" : "=A" (x));
    return x;
}

int* make_array(int size){
    int* arr = malloc(size * sizeof(int));
    int i;
    for (i = 0; i < size; i++) {
        arr[i] = rand() % size;
    }
    return arr;
}


int main() {
	
	int* arr;
	int i;
	int sum = 0;
	long long start = 0;
	long long end = 0;
	long long total_diff = 0;

	int size = 1024 * 1024 * 16 / 4;
	arr = make_array(size);

	FILE *fp = fopen("garbage.txt", "a");   //open file for writing data

	start = rdtsc();
	for (i = 0; i < size; i+=10) {
		arr[i] = 123;
		arr[i+1] = 123;
		arr[i+2] = 123;
		arr[i+3] = 123;
		arr[i+4] = 123;
		arr[i+5] = 123;
		arr[i+6] = 123;
		arr[i+7] = 123;
		arr[i+8] = 123;
		arr[i+9] = 123;
	}
	end = rdtsc();
	if ((end-start) < THRESHOLD) {
		total_diff = (end - start);
		// fprintf(fp, "%d\n", sum);
		printf("%llu\n", total_diff);
	}
    fclose(fp);
    free(arr);
	return 0;
}
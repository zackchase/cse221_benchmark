// #include <time.h>
// #include <time.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <sys/types.h>
// #include <unistd.h>
// #include <string.h>

// int main(int argc, char **argv)
// {
//  srand(time(NULL));

//     float avg_diff;
//     int fart = 0;
//     int start = 0;
//     int end = 0;

//     int i;
//     int n = 14;

//     int **p_int = (int**)malloc(n * sizeof(int));
//     printf("address of p_int: %p\n", p_int );
//     for (i = 1; i <= n; i++) {
//      p_int[i] = makeArray((i+2));
//      printf("address of ptr to size %d: %p\n", (1 << (i+2)), (int*)p_int[i] );
//      // printf("value of blah: %d\n", (int)p_int[i][i]);
//     }

//     int iter = 0;
//     int iterations = 100000;
//     int blah;
//     int j;
//     for (i = 1; i <= n; i++) {
//         // printf("address of ptr to size %d: %p\n", (1 << (i+2)), (int*)p_int[i] );
//         while (iter < iterations) {
//             if (j == (1 << (i+2)) ) {
//                 j = 0;
//             } else {
//                 j = iter;
//             }   
//             start = rdtsc();
//             blah = (long)p_int[i][j];
//             // printf("%d\n", blah);
//             end = rdtsc();
//             avg_diff += (end - start);
//             iter++;
//         }
//         printf("avg diff for array size 2^%d: %f \n", (i+2), avg_diff/iterations);
//         avg_diff = 0;
//         iter = 0;
//     }   

//     return 0;
// }






// http://stackoverflow.com/questions/21369381/measuring-cache-latencies

#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define ONE p = (char **)*p;
#define FIVE    ONE ONE ONE ONE ONE
#define TEN     FIVE FIVE
#define FIFTY   TEN TEN TEN TEN TEN
#define HUND FIFTY FIFTY
#define FIVEHUND HUND HUND HUND HUND HUND 
#define THOU FIVEHUND FIVEHUND


//prototype
void makeArray(long double);
void accessArray(char *, long double, char**);

static __inline__ unsigned long long int rdtsc(void)
{
    unsigned long long int x;
    __asm__ volatile (".byte 0x0f, 0x31" : "=A" (x));
    return x;
}


int main(){
    //call the function for allocating arrays of increasing size in bytes
    makeArray((1 << 3));
    makeArray((1 << 4));
    makeArray((1 << 5));
    makeArray((1 << 6));
    makeArray((1 << 7));
    makeArray((1 << 8));
    // makeArray((1 << 9));
    // makeArray((1 << 10));
    // makeArray((1 << 11));
    // makeArray((1 << 12));
    // makeArray((1 << 13));
    // makeArray((1 << 14));
    makeArray((1 << 15));
    // makeArray((1 << 16));
    // makeArray((1 << 17));
    // makeArray((1 << 18));
    // makeArray((1 << 19));
    // makeArray((1 << 20));
    // makeArray((1 << 21));
    // makeArray((1 << 22));
    makeArray((1 << 23));
    // makeArray((1 << 24));
}

void makeArray(long double size){
    int arrSize = size;
    char * arr = malloc(arrSize * sizeof(char));
    int i;
    int stride = sizeof(char);        //step size

    char ** head = (char **) arr;   //start of linked list in contiguous memory
    char ** p = head;         //interator for linked list
    for (i = 0; i < arrSize; i += stride) {      
        (*p) = &arr[i+stride];      //iterate through linked list, having each one point stride bytes forward
        p += (stride/sizeof(p));          //increment iterator stride bytes forward
        // printf("value: %p\n", &arr[i+stride]);
    }
    *p = (char *) head;       //set tailf to point to head
    // printf("arrSize %Lf\n", size);
    // printf("char size: %d\n", stride );
    accessArray(arr, size, head);
    free(arr);
}

void accessArray(char *cacheArray, long double size, char** head){
    const long double NUM_ACCESSES = 1000000;    //number of accesses to linked list
 
    // FILE *fp =  fopen("accessData.txt", "a");   //open file for writing data
    
    // struct timespec startAccess, endAccess;     //struct for timer
    // long double accessTime = 0;

    int i = 0;
    char ** p = head;     //create iterator

    // long long int start = 0;
    // long long int end = 0;

    // clock_gettime(CLOCK_REALTIME, &startAccess);
    
    long long blah = 0;
    clock_t start = clock();
    for(i = 0; i < NUM_ACCESSES; i++){
        // start = rdtsc();
        THOU       //macro subsitute 100 accesses to mitigate loop overhead
        // end = rdtsc();
        // blah += (end - start)/1000;
    }
    clock_t end = clock();
    
    // long long accessTime = (end-start);
    printf("long long %d in time %d cycles\n", (int)size, (int)end-(int)start);
    // printf("average cycles: %Lf\n", (long double)accessTime/(NUM_ACCESSES*1000));
    // long float access = (float)accessTime/(NUM_ACCESSES);
    // clock_gettime(CLOCK_REALTIME, &endAccess); //end clock
    // accessTime = (((endAccess.tv_sec - startAccess.tv_sec) * SECONDS_PER_NS) + (endAccess.tv_nsec - startAccess.tv_nsec)) / (1000*NUM_ACCESSES);
    // printf("array size %d in time %Lf\n", (int)size, access );
    // end = rdtsc();
    // readTime = (end - start);
    // printf("%lf\n", readTime);
    // printf("read time for array of size %d: %d, %d\n", (int)size, end, start );
    // fprintf(fp, "%Lf\t%ld mb\n", readTime, size);  //print results to file
    // fclose(fp);  //close file
}
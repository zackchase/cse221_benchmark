#include<sys/time.h>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>

static __inline__ unsigned long long rdtsc(void)
{
    unsigned long long int x;
    __asm__ volatile (".byte 0x0f, 0x31" : "=A" (x));
    return x;
}


int main(){

    unsigned long long coldstart = 0;
    unsigned long long start = 0;
    unsigned long long end = 0;
    int i = 0;

	coldstart = rdtsc();
	start = rdtsc();
	// zero_inc_param_overhead();
	// one_inc_param_overhead(1);
	// two_inc_param_overhead(1,2);
	// three_inc_param_overhead(1,2,3);
	// four_inc_param_overhead(1,2,3,4);
	// five_inc_param_overhead(1,2,3,4,5);
	// six_inc_param_overhead(1,2,3,4,5,6);
	seven_inc_param_overhead(1,2,3,4,5,6,7);
	end = rdtsc();
	printf("%llu", end-start);

}

int zero_inc_param_overhead() {
	return;
}
int one_inc_param_overhead(a) {
	return;
}
int two_inc_param_overhead(a,b) {
	return;
}
int three_inc_param_overhead(a,b,c) {
	return;
}
int four_inc_param_overhead(a,b,c,d) {
	return;
}
int five_inc_param_overhead(a,b,c,d,e) {
	return;
}
int six_inc_param_overhead(a,b,c,d,e,f) {
	return;
}
int seven_inc_param_overhead(a,b,c,d,e,f,g) {
	return;
}

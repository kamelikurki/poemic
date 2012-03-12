#include <poemic_defs.h>


float oscillator(float *output, float frequency, float amplitude, float *table, float *index,int length, int vectorsize, int sr) {
        float inc = frequency*length/sr;
	int i;
	for(i = 0;i<vectorsize;i++) {
	  float frac = *index-(int)(*index);
	  float a,b;
	  a = table[(int)*index];
	  b = table[(int)*index+1];
	  output[i] = amplitude*(a+frac*(b-a));
	  *index += inc;
	  while(*index>=length) *index -=length;
	  while(*index<0) *index += length;
	}
	return *output;
}

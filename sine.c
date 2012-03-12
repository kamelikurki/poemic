#include <math.h>
#include <stdlib.h>
#include <poemic_defs.h>


float* sine_table (int length, float phase) {
        float pi = 4*atan(1.);
	int n;
	float *table  = (float*) malloc(sizeof(float)*(length+2));
	phase *= pi*2;
	for(n=0;n<length+2;n++) table[n] = (float) cos(phase+n*2*pi/length);
	return table;
}

float envelope(float duration, float controlR, int *count) {
  int durationsamples = (int) (duration*controlR);
  if((*count)++ < durationsamples/2) return *count*2/durationsamples;
  else return (1-*count/durationsamples)*2;
}

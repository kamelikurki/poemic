#ifndef _POEMIC_DEFS
#define _POEMIC_DEFS


#include <portaudio.h>


float* sine_table(int length, float phase);

float oscillator(float *output, float frequency, float amplitude, float *table, float *index,int length, int vectorsize, int sr);

//void player(float frequency, float duration, float amplitude);

PaStream* openStream();

void writeStream(PaStream *handle, float frequency, float duration, float amplitude);

void closeStream(PaStream *handle);

float envelope(float duration, float controlR, int *count);

#endif

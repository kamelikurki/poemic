#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <poemic_defs.h>


PaStream* openStream() {
  PaError err;
  PaDeviceIndex devout,ndev;
  const PaDeviceInfo *info;
  PaStreamParameters param;
  PaStream *handle;
  int i;
  err = Pa_Initialize();
  ndev = Pa_GetDeviceCount();
  printf("List of available output devices:\n");
  for(i=0; i<ndev;i++) {
    info = Pa_GetDeviceInfo((PaDeviceIndex) i);
    if(info->maxOutputChannels > 0) printf("output device %d: %s\n", i, info->name);
  }
  printf("Choose the number of the output device you want to use:");
  scanf("%d", &devout); 
  memset(&param, 0, sizeof(PaStreamParameters));
  param.device = (PaDeviceIndex) devout;
  param.channelCount = 1;
  param.sampleFormat = paFloat32;
  Pa_OpenStream(&handle, NULL, &param,44100,256, paNoFlag, NULL, NULL);
  Pa_StartStream(handle);
  return handle;
}

void writeStream(PaStream *handle, float frequency, float duration, float amplitude) {
  int i,j,dur, count = 0;
  dur = duration*44100/256;
  float index, index2, control, cr, *buf, *wave;
  cr = 44100/256;
  index = 0.f;
  buf = (float*) malloc(256*sizeof(float));
  wave = sine_table(2048, 0);
  for(j = 0;j < dur;j++){
    oscillator(buf, frequency+oscillator(&control,5.f,5.f, wave, &index2,2048, 1,cr),envelope(duration,cr,&count)*amplitude,wave,&index,2048,256,44100);
    Pa_WriteStream(handle, buf, 256);
  }
  free(buf);
  free(wave);
}


void closeStream(PaStream *handle) {
  Pa_StopStream(handle);
  Pa_CloseStream(handle);
  Pa_Terminate();
}

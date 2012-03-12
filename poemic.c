#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <portaudio.h>
#include <poemic_defs.h>

/**
Poemic is a software that transforms text to melodies. The input file can be a poem, a piece of news, lyrics of a song or anything you want to use as source material.
 **/

int main(int argc, char* argv[]) {
  /*Ask user for parameters*/
  int i,j, index, notenumber, key, lastbit, notes, d, e;
  float tempo, upper, lower;
  FILE *inputFile;
  notes = 0;
  index = 0;
  inputFile = fopen(argv[1], "r");
  if (inputFile==NULL) {
    printf("Error opening input filen\n");
    exit(-1);
  } else {
    do {
      e = fgetc (inputFile);
      notes ++;
    } while (e != EOF);
  }
  if (fseek(inputFile, 0L, SEEK_SET) != 0) {
    printf("Error when moving the pointer back to the start of the file!\n");
    exit(-1);
  }
  int numbers[notes];
  do {
      d = fgetc (inputFile);
      if(d<97 ) numbers[index] = (int)d-77;
      else numbers[index] = (int)d-32-77;
      if(numbers[index]>0) numbers[index]--;
      index++;
  } while(d != EOF);

  printf("Give tempo(bpm) for the piece: ");
  scanf("%f", &tempo); /*length of a whole note is (60/bpm)*(4/notelength) notelength = 1,2,4,8...(1 = whole, 2=half etc.)*/
  
  printf("Give time signature(for example 4/4 = 4 4): ");
  scanf("%f %f", &upper, &lower);
  
  int mask = 0x800;
  int keymask = 0xAD5;/*1010 1101 0101*/
  
  printf("Give the key you want the music to be in(0=C, 1= Db, 2 = D, 3= Eb, 4=E, 5=F, 6=Gb, 7=G, 8=Ab, 9=A 10=B, 11=Cb):");
  scanf("%d", &key);
  notenumber = 60 + key;
  for(i=0;i<key;i++) {
	lastbit = mask&keymask;
	keymask >>= 1;
        if(lastbit) keymask |= 0x800;
  }
  /*Generate the notes*/
  PaStream *kahva = openStream();
  for(i=0;i<notes; i++) {
    int instrument, note, notelength,j, interval;
    float amplitude, duration, frequency;
    double exponent, base;
    /*Decide which instrument to use*/
    instrument = 3;
    /*Decide the amplitude of note*/
    amplitude = (rand()%51)+50;
    amplitude /= 100;
    /*Decide the duration of a note in seconds*/
    notelength=0x001;
    notelength <<= (rand() % 4+1);
    duration = (60/tempo)*(upper/notelength*(lower/4));
    if(numbers[i] < -12 || numbers[i] > 12) {
      continue;
    }else {
      interval = numbers[i];
      int direction  = rand()%2;
      if (interval<0) {
	for(j=0;j<abs(interval);j++) {
	  mask >>= 1;
	  if(mask == 0) mask = 0x800;
	} 
	if (!mask&keymask){
	  interval++;
	  mask >>= 1;
	  if(mask == 0) mask = 0x800;
	}
      } else {
	for(j=0;j<abs(interval);j++) {
	  mask <<= 1;
	  if(mask == 0) mask = 0x001;
	}
	if (!mask&keymask){
	  interval--;
	  mask <<= 1;
	  if(mask == 0) mask = 0x001;
	}
      }
    
      if(direction) notenumber+=interval;
      else notenumber-=interval;
      note = ((int)abs(notenumber))%12;
      frequency = 261.63;
      for(j=0;j<note;j++) frequency *= 1.059463;
      char c = '+';
      if(i==0) c ='0';
      writeStream(kahva, frequency, duration, amplitude);
      
    }
  }
  closeStream(kahva);
  return 0;
}

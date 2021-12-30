#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <lib/piano.h>
#include <sndfile.h>

#define	SAMPLE_RATE 48000
#define SAMPLE_COUNT (SAMPLE_RATE * 20)	
#define MAX_AMPLITUDE 0x7F000000
#define CHANNELS 2
#define FREQUENCY 440
#define VELOCITY 64

int main(void)
{
	SNDFILE	*file ;
	SF_INFO	sfinfo ;
	int *buffer = (int*)malloc(CHANNELS * SAMPLE_COUNT * sizeof(int));
	float *mono_buffer = (float*)malloc(SAMPLE_COUNT * sizeof(float));
	memset(&sfinfo, 0, sizeof(sfinfo));
	sfinfo.samplerate	= SAMPLE_RATE ;
	sfinfo.frames		= SAMPLE_COUNT ;
	sfinfo.channels		= CHANNELS;
	sfinfo.format		= (SF_FORMAT_WAV | SF_FORMAT_PCM_24);
	string s;
	initialize_string(&s, FREQUENCY, SAMPLE_RATE);
	excite_string(&s, VELOCITY);
	get_string_samples(mono_buffer, &s, SAMPLE_COUNT);
	file = sf_open ("test.wav", SFM_WRITE, &sfinfo);
	for (int i = 0 ; i < SAMPLE_COUNT ; i++)
	{	
		buffer [2 * i] = (int) MAX_AMPLITUDE * mono_buffer[i];
		buffer [2 * i + 1] = (int) MAX_AMPLITUDE * mono_buffer[i];
		
	}
	sf_write_int (file, buffer, sfinfo.channels * SAMPLE_COUNT);
	sf_close(file);
	free(buffer);
	return 0;
}

#include "piano_string.h"


void initialize_string(string* s, float frequency, int sample_rate)
{
	s->frequency = frequency;
	s->sample_rate = sample_rate;
	s->state = NOTE_OFF;	
	s->w = new_waveguide((float)sample_rate / (float)frequency);
}

void get_string_samples(float* buffer, string* s, int n_samples)
{
	float output, hpeak;
	for(int i = 0; i < n_samples; i++)
	{
		output = waveguide_process(s->w);
		buffer[i] += output;
	}
}

void excite_string(string* s, int velocity)
{
	s->state = NOTE_ON;
	float v = (float)velocity / 128.0;
	excite_waveguide(s->w, v);
}

void stop_string(string* s)
{
	s->state = NOTE_OFF;
}

void sustain_string(string* s){
	s->state = SUSTAIN;
}
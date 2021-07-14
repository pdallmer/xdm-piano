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
	float output;
	for(int i = 0; i < n_samples; i++)
	{
		buffer[i] += waveguide_process(s->w);
	}
}

void excite_string(string* s, int velocity)
{
	s->state = EXCITATION;
	if(velocity > 0){
		s->w->damping_filter->b0 = 0.5;
		s->w->damping_filter->b1 = 0.5;
	}
	float v = (float)velocity / 128.0;
	excite_waveguide(s->w, v);
}

void stop_string(string* s)
{
	s->w->damping_filter->b0 = 0.4;
	s->w->damping_filter->b1 = 0.4;
	s->state = NOTE_OFF;
}

void sustain_string(string* s){
	s->state = SUSTAIN;
}
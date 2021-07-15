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
	float input, output, hpeak;
	hpeak = 0.0;
	for(int i = 0; i < n_samples; i++)
	{
		if(i < s->w->exciter->N)
		{
			input = hann_process(s->w->exciter);
			s->w->upper->buffer[s->w->upper_input] += input;
			s->w->lower->buffer[s->w->lower_input] += input;
		}
		else{
			s->w->exciter->N = 0;
			s->w->exciter->n = 0;
		}
		output = waveguide_process(s->w);
		hpeak += fabs(output);
		buffer[i] += output;
	}
	if (hpeak < 0.0001) s->state = NOTE_OFF;
}

void excite_string(string* s, int velocity)
{
	s->state = NOTE_ON;
	s->w->damping_filter->b0 = 0.5;
	s->w->damping_filter->b1 = 0.5;
	float v = (float)velocity / 128.0;
	excite_waveguide(s->w, v);
}

void stop_string(string* s)
{
	s->state = DECAY;
	s->w->damping_filter->b0 = 0.4;
	s->w->damping_filter->b1 = 0.4;
}

void sustain_string(string* s){
	s->state = SUSTAIN;
}
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
	hpeak = 0.0;
	for(int i = 0; i < n_samples; i++)
	{
		excite_waveguide(s->w, one_pole_process(s->w->input_filter, s->state == EXCITATION));
		s->state = NOTE_ON;
		output = waveguide_process(s->w);
		hpeak += fabs(output);
		buffer[i] += output;
	}
	if (hpeak < MUTE && s->w->damping_filter->b0 < 0.5) s->state = NOTE_OFF;
}

void excite_string(string* s, int velocity)
{
	s->state = EXCITATION;
	s->w->damping_filter->b0 = 0.5;
	s->w->damping_filter->b1 = 0.5;
	float v = (float)velocity / 128.0;
	s->w->input_filter->b0 = v;
	s->w->input_filter->a1 = 1 - (0.5 * v) * (0.5 * v);
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
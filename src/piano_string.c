#include "piano_string.h"


void initialize_string(string* s, float frequency, int sample_rate)
{
	s->frequency = frequency;
	s->sample_rate = sample_rate;
	s->state = NOTE_OFF;	
	s->d = new_delay_line((float)sample_rate / (float)frequency);
	s->damping_filter = new_one_zero(0.5, 0.5);
}

void get_string_samples(float* buffer, string* s, int n_samples)
{
	float output;
	for(int i = 0; i < n_samples; i++)
	{
		//output
		output = delay_line_peek(s->d);
		buffer[i] += output;
		//damping
		delay_line_process(s->d, one_zero_process(s->damping_filter, output));
	}
}

void excite_string(string* s, int velocity)
{

	s->state = NOTE_ON;
	float v = (float)velocity / 128.0;
	one_pole* f = new_one_pole(0, 0);
	for(int i = 0; i < s->d->length; i++)
	{
		f->a1 = -(i / s->d->length);
		f->b0 = 1 + f->a1;
		delay_line_process(s->d, one_pole_process(f, random_float(v)));
	}	
}
void stop_string(string* s)
{
	s->state = NOTE_OFF;
}

void sustain_string(string* s){
	s->state = SUSTAIN;
}
#include "piano_string.h"

void initialize_string(string* s, float frequency, int sample_rate)
{
	s->frequency = frequency;
	s->delay_line_length = ceil((float)sample_rate / (float)frequency);
	s->delay_line = (float*)malloc(s->delay_line_length * sizeof(float));
	s->state = NOTE_OFF;	
	s->biquad = (float*)malloc(2 * sizeof(float));
}

void get_string_samples(float* buffer, string* s, int n_samples)
{
	float g, b1, b2, a1, a2, r;
	r = 0.9;
	a2 = r * r;
	g = a2;
	a1 = -2 * r * cosf(2 * M_PI * s->frequency);
	b1 = a1 / a2;
	b2 = 1 / a2;
	for(int i = 0; i < n_samples; i++)
	{
		//output
		buffer[i] += s->delay_line[s->delay_line_out];
		//dispersion
		s->delay_line[s->delay_line_out] = g * s->delay_line[s->delay_line_out] 
											+ b1 * g * s->delay_line[(s->delay_line_out + 1) % s->delay_line_length] 
											+ b2 * g * s->delay_line[(s->delay_line_out + 2) % s->delay_line_length] 
											- a1 * s->biquad[(s->biquad_out + 1) % 2] 
											- a2 * s->biquad[s->biquad_out];
		s->biquad[s->biquad_out] = s->delay_line[s->delay_line_out];
		s->biquad_out = (s->biquad_out + 1) % 2;
		//damping
		s->delay_line[s->delay_line_out] = 0.5 * s->delay_line[s->delay_line_out] + 0.5 * s->delay_line[(s->delay_line_out + 1) % s->delay_line_length];
		//increase counter
		s->delay_line_out = (s->delay_line_out + 1) % s->delay_line_length;
	}
}

void excite_string(string* s, int velocity)
{
	s->state = NOTE_ON;
	float v = (float)velocity / 128.0;
	s->delay_line_out = 0;
	s->biquad_out = 0;
	for(int i = 0; i < s->delay_line_length; i++)
	{
		s->delay_line[i] =  random_float(v);
	}	
}
void stop_string(string* s)
{
	s->state = NOTE_OFF;
}

void sustain_string(string* s){
	s->state = SUSTAIN;
}
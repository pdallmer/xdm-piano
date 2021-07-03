#include "piano_string.h"

void initialize_string(string* s, float frequency, int sample_rate)
{
	s->frequency = frequency;	
	s->delay_line_length = ceil((float)sample_rate / (float)frequency);
	s->delay_line = (float*)malloc(s->delay_line_length * sizeof(float));
	s->state = NOTE_OFF;	
	s->two_pole = (float*)malloc(2 * sizeof(float));
}

void get_string_samples(float* buffer, string* s, int n_samples)
{
	int next_index;
	for(int i = 0; i < n_samples; i++)
	{
		//output
		buffer[i] += s->delay_line[s->delay_line_out];
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
	s->two_pole_out = 0;
	for(int i = 0; i < s->delay_line_length; i++)
	{
		s->delay_line[i] =  0.2 * random_float(v) + 2 * 0.9 * cosf(440) * s->two_pole[(s->two_pole_out + 1) % 2] - 0.89 * s->two_pole[s->two_pole_out];
		s->two_pole[s->two_pole_out] = s->delay_line[i];
		s->two_pole_out = (s->two_pole_out + 1) % 2;
	}	
}
void stop_string(string* s)
{
	s->state = NOTE_OFF;
}

void sustain_string(string* s){
	s->state = SUSTAIN;
}
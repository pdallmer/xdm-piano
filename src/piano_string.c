#include "piano_string.h"

void initialize_string(string* s, float frequency, int sample_rate)
{
	
	s->delay_line_length = floor((float)sample_rate / (float)frequency);
	s->delay_line = (float*)malloc(s->delay_line_length * sizeof(float));
	s->state = NOTE_OFF;	
}

void get_string_samples(float* buffer, string* s, int n_samples)
{
	int next_index;
	for(int i = 0; i < n_samples; i++)
	{
		buffer[i] += s->delay_line[s->upper_hammer] + s->delay_line[s->lower_hammer];
		s->nut = (s->nut + 1) % s->delay_line_length;
		s->bridge = (s->bridge + 1) % s->delay_line_length;
		s->upper_hammer = (s->upper_hammer + 1) % s->delay_line_length;
		s->lower_hammer = (s->lower_hammer + 1) % s->delay_line_length;
		s->delay_line[s->nut] *= -0.995;
		s->delay_line[s->bridge] *= -1;
	}
}

void excite_string(string* s, int velocity)
{
	s->state = NOTE_ON;
	float v = (float)velocity / 256.0;
	for(int i = 0; i < s->delay_line_length; i++)
	{
		s->delay_line[i] = 0;
	}	
	s->nut = 0;
	s->bridge = (s->nut + (s->delay_line_length / 2)) % s->delay_line_length;
	s->upper_hammer = (s->bridge - (s->delay_line_length / 8)) % s->delay_line_length;
	s->lower_hammer = (s->bridge + (s->delay_line_length / 8)) % s->delay_line_length;
	s->delay_line[s->upper_hammer] = v;
	s->delay_line[s->lower_hammer] = v;
}

void stop_string(string* s)
{
	s->state = NOTE_OFF;
}

void sustain_string(string* s){
	s->state = SUSTAIN;
}
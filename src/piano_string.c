#include "piano_string.h"

void initialize_string(string* s, float frequency, int sample_rate)
{
	
	s->delay_line_length = floor((float)sample_rate / (float)frequency);
	s->delay_line = (float*)malloc(s->delay_line_length * sizeof(float));
	s->state = NOTE_OFF;
	
}

void get_string_samples(float* buffer, string* s, int n_samples)
{
	for(int i = 0; i < n_samples; i++)
	{
		buffer[i] += s->delay_line[s->delay_line_out];
  		s->delay_line[s->delay_line_out] = (s->delay_line[s->delay_line_out] / 2) + (s->delay_line[(s->delay_line_out + 1) % s->delay_line_length] / 2);
		s->delay_line_out = (s->delay_line_out + 1) % s->delay_line_length;
	}
}

void excite_string(string* s, int velocity)
{
	s->state = NOTE_ON;
	for(int i = 0; i < s->delay_line_length; i++)
	{
		s->delay_line[i] = random_float((float)velocity / 127.0);
	}
	s->delay_line_out = 0;
}

void stop_string(string* s)
{
	s->state = NOTE_OFF;
}

void sustain_string(string* s){
	s->state = SUSTAIN;
}
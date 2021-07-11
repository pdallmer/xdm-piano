#include "piano_string.h"


void initialize_string(string* s, float frequency, int sample_rate)
{
	s->frequency = frequency;
	s->delay_line_length = floor((float)sample_rate / (float)frequency) - 1;
	s->m = ((float)sample_rate / (float)frequency) - s->delay_line_length;
	s->a1 = -1 * ((s->m - 1 + 1) / (s->m - 1 + 1 + 1));
	s->delay_line = (float*)malloc(s->delay_line_length * sizeof(float));
	s->state = NOTE_OFF;	
}

void get_string_samples(float* buffer, string* s, int n_samples)
{
	float y;
	for(int i = 0; i < n_samples; i++)
	{
		//output
		buffer[i] += s->delay_line[s->delay_line_out]; 
		//damping
		s->delay_line[s->delay_line_out] = 0.5 * s->delay_line[s->delay_line_out] + 0.5 * s->delay_line[(s->delay_line_out + 1) % s->delay_line_length];
		//tuning
		y = s->a1 * s->delay_line[s->delay_line_out] + s->x1 - s->a1 * s->y1;
		s->x1 = s->delay_line[s->delay_line_out];
		s->delay_line[s->delay_line_out] = y;
		s->y1 = y;
		//increase counter
		s->delay_line_out = (s->delay_line_out + 1) % s->delay_line_length;

	}
}

void excite_string(string* s, int velocity)
{

	s->state = NOTE_ON;
	float v = (float)velocity / 128.0;
	s->delay_line_out = 0;
	float b0, a1, feedback;
	for(int i = 0; i < s->delay_line_length; i++)
	{
		s->delay_line[i] =  random_float(v);
		//filter excitation input
		a1 = (float)-i / s->delay_line_length;
		b0 = 1.0 + a1;
		feedback = i == 0 ? 0 : s->delay_line[i - 1];
		s->delay_line[i] = b0 * s->delay_line[i] - a1 * feedback;
	}	
	s->x1 = 0;
}
void stop_string(string* s)
{
	s->state = NOTE_OFF;
}

void sustain_string(string* s){
	s->state = SUSTAIN;
}
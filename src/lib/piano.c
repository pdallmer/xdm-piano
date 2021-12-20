#include <lib/piano.h>

void initialize_string(string* s, float frequency, int sample_rate)
{
	s->w = new_karplus_strong(sample_rate / frequency);
	s->state = NOTE_OFF;
}

void get_string_samples(float* buffer, string* s, int n_samples)
{
	for(int i = 0; i < n_samples; i++)
	{
		buffer[i] += process_karplus_strong(s->w);
	}
}

void excite_string(string* s, int velocity)
{
	excite_karplus_strong(s->w, (float)velocity/127.0);
	s->state = NOTE_ON;
}

void stop_string(string* s)
{
	s->state = NOTE_OFF;
}

void sustain_string(string* s){
	s->state = SUSTAIN;
}

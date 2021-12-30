#include <lib/piano.h>

void initialize_string(string* s, float frequency, int sample_rate)
{
	s->w = new_waveguide(sample_rate / frequency, 1.0/3.0);
	s->state = NOTE_OFF;
}

void get_string_samples(float* buffer, string* s, int n_samples)
{
	for(int i = 0; i < n_samples; i++)
	{
		buffer[i] += process_waveguide(s->w);
	}
}

void excite_string(string* s, int velocity)
{
	excite_waveguide(s->w, (float)velocity / 127.0);
	s->state = NOTE_ON;
}

void stop_string(string* s)
{
	s->state = NOTE_OFF;
}

void sustain_string(string* s){
	s->state = SUSTAIN;
}

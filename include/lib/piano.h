#ifndef _PIANO_H
#define _PIANO_H

#include <lib/waveguide.h>

enum string_state
{
	NOTE_OFF,
	NOTE_ON,
	SUSTAIN
};

typedef struct string 
{
	waveguide *w;
	enum string_state state;
}string;

void initialize_string(string* s, float frequency, int sample_rate);

void get_string_samples(float* buffer, string* s, int n_samples);

void excite_string(string* s, int velocity);

void stop_string(string* s);

void sustain_string(string* s);

#endif

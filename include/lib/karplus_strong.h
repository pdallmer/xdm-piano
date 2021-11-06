#ifndef _KARPLUS_STRONG_H
#define _KARPLUS_STRONG_H

enum string_state
{
	NOTE_OFF,
	NOTE_ON,
	SUSTAIN
};

typedef struct string string;

struct string 
{
	int delay_line_length; 
	int delay_line_out;
	float* delay_line;
	enum string_state state;
};

void initialize_string(string* s, float frequency, int sample_rate);

void get_string_samples(float* buffer, string* s, int n_samples);

void excite_string(string* s, int velocity);

void stop_string(string* s);

void sustain_string(string* s);

#endif

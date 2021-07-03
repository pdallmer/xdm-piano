#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "utils.h"

enum string_state
{
	NOTE_OFF,
	NOTE_ON,
	SUSTAIN
};

typedef struct string string;

struct string 
{
	float frequency;
	int delay_line_length; 
	int delay_line_out;
	int two_pole_out;
	float* two_pole;
	float* delay_line;
	enum string_state state;
};

void initialize_string(string* s, float frequency, int sample_rate);

void get_string_samples(float* buffer, string* s, int n_samples);

void excite_string(string* s, int velocity);

void stop_string(string* s);

void sustain_string(string* s);
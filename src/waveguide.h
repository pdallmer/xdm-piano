#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "filter.h"

typedef struct waveguide waveguide;

struct waveguide
{
	delay_line *upper;
	delay_line *lower;
	one_zero *damping_filter;
	int upper_input;
	int lower_input;
	int upper_output;
	int lower_output;
};

waveguide *new_waveguide(float length);

float waveguide_process(waveguide *w);

void excite_waveguide(waveguide *w, float v);
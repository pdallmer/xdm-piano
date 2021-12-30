#include <lib/dsp.h>
#define LOW_PASS_FILTER_FACTOR 0.5

typedef struct waveguide{
	delay *upper_right;
	delay *upper_left;
	delay *lower_right;
	delay *lower_left;
	one_zero *low_pass_filter;
	float upper_input;
	float lower_input;
}waveguide;

waveguide *new_waveguide(float length, float hammer_position);

float process_waveguide(waveguide *w);

void excite_waveguide(waveguide *w, float velocity);

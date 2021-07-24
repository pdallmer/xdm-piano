#include "waveguide.h"


waveguide *new_waveguide(float length)
{
	waveguide *new_waveguide = (waveguide*)malloc(sizeof(waveguide));
	new_waveguide->upper = new_delay_line(length / 2.0);
	new_waveguide->lower = new_delay_line(length / 2.0);
	new_waveguide->damping_filter = new_one_zero(0.5, 0.5);
	//input and output offset not parameterized yet
	int offset = floor(length / 6);
	new_waveguide->upper_input = offset;
	new_waveguide->lower_input = new_waveguide->lower->buffer_length - offset;
	new_waveguide->upper_output = new_waveguide->upper->buffer_length - offset;
	new_waveguide->lower_output = offset;
	return new_waveguide;
}


float waveguide_process(waveguide *w)
{
	float y = w->upper->buffer[w->upper_output] + w->lower->buffer[w->lower_output];
	float uin = -1 * delay_line_process(w->lower, -delay_line_peek(w->upper));
	delay_line_process(w->upper, one_zero_process(w->damping_filter, uin));
	w->upper_output = (w->upper_output + 1) % w->upper->buffer_length;
	w->lower_output = (w->lower_output + 1) % w->lower->buffer_length;
	w->upper_input = (w->upper_input + 1) % w->upper->buffer_length;
	w->lower_input = (w->lower_input + 1) % w->lower->buffer_length;
	return y;
}

void excite_waveguide(waveguide *w, float v)
{
	w->upper->buffer[w->upper_input] += v;
	w->lower->buffer[w->lower_input] += v;
}
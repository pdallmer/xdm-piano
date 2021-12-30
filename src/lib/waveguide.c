#include <lib/waveguide.h>
#include <stdlib.h>

waveguide *new_waveguide(float length, float hammer_position)
{
	waveguide *w = (waveguide*)malloc(sizeof(waveguide));
	unsigned int left_length = (length / 2) * hammer_position;
	unsigned int right_length = (length / 2) - left_length;
	w->upper_left = new_delay(left_length);
	w->upper_right = new_delay(right_length);
	w->lower_left = new_delay(left_length);
	w->lower_right = new_delay(right_length);
	w->low_pass_filter = new_one_zero(LOW_PASS_FILTER_FACTOR, LOW_PASS_FILTER_FACTOR);
	connect_dsp_elements((dsp_element*)w->upper_left, (dsp_element*)w->upper_right);
	connect_dsp_elements((dsp_element*)w->upper_right, (dsp_element*)w->low_pass_filter);
	connect_dsp_elements((dsp_element*)w->low_pass_filter, (dsp_element*)w->lower_right);
	connect_dsp_elements((dsp_element*)w->lower_right, (dsp_element*)w->lower_left);
	connect_dsp_elements((dsp_element*)w->lower_left, (dsp_element*)w->upper_left);	
	return w;
}

float process_waveguide(waveguide *w)
{
	float output = *w->upper_right->output;
	process_one_zero(w->low_pass_filter);
	*w->lower_right->input *= -1;
	process_delay(w->lower_right);
	
	*w->lower_left->input += w->lower_input;
	w->lower_input = 0;
	
	process_delay(w->lower_left);
	*w->upper_left->input *= -1;
	process_delay(w->upper_left);
	
	*w->upper_right->input += w->upper_input;
	w->upper_input = 0;
	
	process_delay(w->upper_right);
	return output;
}

void excite_waveguide(waveguide *w, float velocity)
{
	w->upper_input = velocity;
	w->lower_input = velocity;
}

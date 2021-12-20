#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <lib/karplus_strong.h>
#include <lib/utils.h>

karplus_strong *new_karplus_strong(unsigned int length){
	karplus_strong *k = (karplus_strong*)malloc(sizeof(karplus_strong));
	k->delay = new_delay(length);
	k->low_pass_filter = new_one_zero(LOW_PASS_FILTER_FACTOR, LOW_PASS_FILTER_FACTOR);
	connect_dsp_elements((dsp_element*)k->delay, (dsp_element*)k->low_pass_filter);
	connect_dsp_elements((dsp_element*)k->low_pass_filter, (dsp_element*)k->delay);
	return k;
}

float process_karplus_strong(karplus_strong *k){
	float output = *k->delay->output;
	process_delay(k->delay);
	process_one_zero(k->low_pass_filter);
	return output;
}

void excite_karplus_strong(karplus_strong *k, float velocity){
	for(unsigned int i = 0; i < k->delay->length; i++){
		k->delay->buffer[i] = random_float(velocity);
	}
}

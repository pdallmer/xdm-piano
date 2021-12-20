#ifndef _KARPLUS_STRONG_H
#define _KARPLUS_STRONG_H

#define LOW_PASS_FILTER_FACTOR 0.5

#include <lib/dsp.h>

typedef struct karplus_strong{
	delay *delay;
	one_zero *low_pass_filter;
}karplus_strong;

karplus_strong *new_karplus_strong(unsigned int length);

float process_karplus_strong(karplus_strong *k);

void excite_karplus_strong(karplus_strong *k, float velocity);


#endif

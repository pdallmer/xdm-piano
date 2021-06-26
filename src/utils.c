#include "utils.h"

float mix_samples(float a, float b)
{
	return a + b - a * b;
}

float random_float(float abs_max)
{
	float random = (float)rand()/(float)(RAND_MAX/(abs_max * 2));
	return random - abs_max;
}
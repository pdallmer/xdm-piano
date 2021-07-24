#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "filter.h"

typedef struct waveguide waveguide;

struct waveguide
{
	float *r; //right going waves
	float *l; //left going waves
	int rl;
	int ll;
	thiran *tuning_filter;
	float bridge_impedance;
	float wave_impedance;
	int right_input;
	int left_input;
	int right_bridge;
	int left_bridge;
	int right_nut;
	int left_nut;
};

waveguide *new_waveguide(float length);

float waveguide_process(waveguide *w);

void excite_waveguide(waveguide *w, float v);
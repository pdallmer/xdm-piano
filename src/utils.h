#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct delay_line delay_line;
typedef struct thiran thiran;
typedef struct one_zero one_zero;
typedef struct one_pole one_pole;
typedef struct dispersion_filter dispersion_filter;
typedef struct smoothing_filter smoothing_filter;
typedef struct waveguide waveguide;

//first order
struct thiran
{
	float x1;
	float y1;
	float m;
	float a1;
};

struct delay_line
{
	int out;
	float length;
	int buffer_length;
	thiran* tuning_filter;
	float* buffer;
};

struct one_zero
{
	float x1;
	float b0;
	float b1;
};

struct one_pole
{
	float y1;
	float b0;
	float a1;
};

struct dispersion_filter
{
	thiran **f;
	float total_delay;
};

struct smoothing_filter
{
	float *X;
	float y1;
	float b0;
	float a1;
	int max_order;
	int order;
	int out;
};


//not universal, terminated string only
struct waveguide
{
	delay_line *upper;
	delay_line *lower;
	one_zero *damping_filter;
	smoothing_filter *input_smoothing_filter;
	int upper_input;
	int lower_input;
	int upper_output;
	int lower_output;
};


float random_float(float abs_max);

thiran *new_thiran(float m);

delay_line *new_delay_line(float length);

one_zero *new_one_zero(float b0, float b1);

one_pole *new_one_pole(float a1, float b0);

dispersion_filter *new_dispersion_filter(int key, int m, float b);

smoothing_filter *new_smoothing_filter(int max_order);

waveguide *new_waveguide(float length);

float thiran_peek(thiran *t, float x0);

float thiran_process(thiran *t, float x0);

float delay_line_peek(delay_line *d);

float delay_line_process(delay_line *d, float x0);

float one_zero_process(one_zero *f, float x0);

float one_pole_process(one_pole *f, float x0);

float smoothing_filter_process(smoothing_filter *f, float x0);

float waveguide_process(waveguide *w);

void excite_waveguide(waveguide *w, float v);
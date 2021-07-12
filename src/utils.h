#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct delay_line delay_line;
typedef struct thiran thiran;
typedef struct one_zero one_zero;
typedef struct one_pole one_pole;
typedef struct biquad biquad;

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
	float* buffer;
	int out;
	float length;
	int buffer_length;
	thiran* tuning_filter;
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

struct biquad
{
	float g;
	float b1;
	float b2;
	float a1;
	float a2;
	float x1;
	float x2;
	float y1;
	float y2;
};

float random_float(float abs_max);

thiran* new_thiran(float m);

delay_line* new_delay_line(float length);

one_zero *new_one_zero(float b0, float b1);

one_pole *new_one_pole(float a1, float b0);

biquad *new_biquad(float g, float b1, float b2, float a1, float a2);

biquad *new_low_pass_biquad(int fs, float fc, float q, biquad *f);

float thiran_peek(thiran *t, float x0);

float thiran_process(thiran* t, float x0);

float delay_line_peek(delay_line* d);

float delay_line_process(delay_line* d, float x0);

float one_zero_process(one_zero* f, float x0);

float one_pole_process(one_pole* f, float x0);

float biquad_process(biquad *f, float x0);
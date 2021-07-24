#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "utils.h"

typedef struct thiran thiran;
typedef struct one_zero one_zero;
typedef struct one_pole one_pole;
typedef struct delay_line delay_line;

struct delay_line
{
	int out;
	float length;
	int buffer_length;
	thiran* tuning_filter;
	float* buffer;
};

//first order
struct thiran
{
	float x1;
	float y1;
	float m;
	float a1;
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


delay_line *new_delay_line(float length);

float delay_line_peek(delay_line *d);

float delay_line_process(delay_line *d, float x0);

thiran *new_thiran(float m);

one_zero *new_one_zero(float b0, float b1);

one_pole *new_one_pole(float a1, float b0);

float thiran_peek(thiran *t, float x0);

float thiran_process(thiran *t, float x0);

float one_zero_process(one_zero *f, float x0);

float one_pole_process(one_pole *f, float x0);
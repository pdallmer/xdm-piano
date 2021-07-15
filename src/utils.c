#include "utils.h"

float random_float(float abs_max)
{
	float random = (float)rand()/(float)(RAND_MAX/(abs_max * 2));
	return random - abs_max;
}

thiran* new_thiran(float m)
{
	thiran* new_thiran = (thiran*)malloc(sizeof(thiran));
	new_thiran->x1 = 0.0;
	new_thiran->y1 = 0.0;
	new_thiran->m = m;
	new_thiran->a1 = -1 * ((new_thiran->m - 1) / (new_thiran->m - 1 + 1)) * ((new_thiran->m - 1 + 1) / (new_thiran->m - 1 + 1 + 1));
	return new_thiran;
}

delay_line* new_delay_line(float length)
{
	delay_line* new_delay_line = (delay_line*)malloc(sizeof(delay_line));
	new_delay_line->length = length;
	new_delay_line->buffer_length = floor(length - 1);
	new_delay_line->tuning_filter = new_thiran(length - new_delay_line->buffer_length);
	new_delay_line->out = 0;
	new_delay_line->buffer = (float*)malloc(new_delay_line->buffer_length * sizeof(float));
	return new_delay_line;
}

one_zero *new_one_zero(float b0, float b1)
{
	one_zero *new_one_zero = (one_zero*)malloc(sizeof(one_zero));
	new_one_zero->b0 = b0;
	new_one_zero->b1 = b1;
	new_one_zero->x1 = 0;
	return new_one_zero;
}

one_pole *new_one_pole(float a1, float b0)
{
	one_pole *new_one_pole = (one_pole*)malloc(sizeof(one_pole));
	new_one_pole->a1 = a1;
	new_one_pole->b0 = b0;
	new_one_pole->y1 = 0;
	return new_one_pole;
}

hann *new_hann(int N, int max_N)
{
	hann *new_hann = (hann*)malloc(sizeof(hann));
	new_hann->N = N;
	new_hann->max_N = max_N;
	new_hann->n = 0;
	return new_hann;
}

waveguide *new_waveguide(float length)
{
	waveguide *new_waveguide = (waveguide*)malloc(sizeof(waveguide));
	new_waveguide->upper = new_delay_line(length / 2.0);
	new_waveguide->lower = new_delay_line(length / 2.0);
	new_waveguide->damping_filter = new_one_zero(0.5, 0.5);
	new_waveguide->exciter = new_hann(0, 128);
	//input and output offset not parameterized yet
	int offset = floor(length / 6);
	new_waveguide->upper_input = offset;
	new_waveguide->lower_input = new_waveguide->lower->buffer_length - offset;
	new_waveguide->upper_output = new_waveguide->upper->buffer_length - offset;
	new_waveguide->lower_output = offset;
	return new_waveguide;
}

float thiran_peek(thiran *t, float x0)
{
	return t->a1 * x0 + t->x1 - t->a1 * t->y1;
}

float thiran_process(thiran* t, float x0)
{
	float y = t->a1 * x0 + t->x1 - t->a1 * t->y1;
	t->x1 = x0;
	t->y1 = y;
	return y;
}

float delay_line_peek(delay_line* d)
{
	return thiran_peek(d->tuning_filter, d->buffer[d->out]);	
}

float delay_line_process(delay_line* d, float x0)
{
	float y = thiran_process(d->tuning_filter, d->buffer[d->out]);
	d->buffer[d->out] = x0;
	d->out = (d->out + 1) % d->buffer_length;
	return y;
}

float one_zero_process(one_zero* f, float x0)
{
	float y = f->b0 * x0 + f->b1 * f->x1;
	f->x1 = x0;
	return y;
}

float one_pole_process(one_pole* f, float x0)
{
	float y = f->b0 * x0 - f->a1 * f->y1;
	f->y1 = y;
	return y;
}

float hann_process(hann *h)
{
	float y = (((-(float)h->N -1)/ h->max_N) + 1) * sinf((2 * M_PI * h->n) / h->N);
	y *= y;
	h->n++;
	return y;
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
	w->exciter->N = (w->exciter->max_N * (1 - v)) + 1;
}
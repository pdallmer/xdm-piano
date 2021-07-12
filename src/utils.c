#include "utils.h"

float random_float(float abs_max)
{
	float random = (float)rand()/(float)(RAND_MAX/(abs_max * 2));
	return random - abs_max;
}

thiran* new_thiran(float m)
{
	thiran* new_thiran = (thiran*)malloc(sizeof(thiran*));
	new_thiran->x1 = 0.0;
	new_thiran->y1 = 0.0;
	new_thiran->m = m;
	new_thiran->a1 = -1 * ((new_thiran->m - 1 + 1) / (new_thiran->m - 1 + 1 + 1));
	return new_thiran;
}

delay_line* new_delay_line(float length)
{
	delay_line* new_delay_line = (delay_line*)malloc(sizeof(delay_line*));
	new_delay_line->length = length;
	new_delay_line->buffer_length = floor(length - 1);
	new_delay_line->tuning_filter = new_thiran(length - new_delay_line->buffer_length);
	new_delay_line->buffer = (float*)malloc(new_delay_line->buffer_length * sizeof(float));
	new_delay_line->out = 0;
	return new_delay_line;
}

one_zero *new_one_zero(float b0, float b1)
{
	one_zero *new_one_zero = (one_zero*)malloc(sizeof(one_zero*));
	new_one_zero->b0 = b0;
	new_one_zero->b1 = b1;
	new_one_zero->x1 = 0;
	return new_one_zero;
}

one_pole *new_one_pole(float a1, float b0)
{
	one_pole *new_one_pole = (one_pole*)malloc(sizeof(one_pole*));
	new_one_pole->a1 = a1;
	new_one_pole->b0 = b0;
	new_one_pole->y1 = 0;
	return new_one_pole;
}

biquad *new_biquad(float g, float b1, float b2, float a1, float a2)
{
	biquad *new_biquad = (biquad*)malloc(sizeof(biquad));
	new_biquad->g = g;
	new_biquad->b1 = b1;
	new_biquad->b2 = b2;
	new_biquad->a1 = a1;
	new_biquad->a2 = a2;
	return new_biquad;
}

biquad *new_low_pass_biquad(int fs, float fc, float q, biquad *f)
{
	if(f == NULL)
	{
		f = new_biquad(0,0,0,0,0);
	}
    float k = tanf(M_PI * fc / fs);
    float norm = 1 / (1 + k / q + k * k);
    f->g = k * k * norm;
    f->a1 = 2 * f->g;
    f->a2 = f->g;
    f->b1 = 2 * (k * k - 1) * norm;
    f->b2 = (1 - k / q + k * k) * norm;
    return f;
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

float biquad_process(biquad *f, float x0)
{
	float y = f->g * x0 + f->b1 * f->g * f->x1 + f->b2 * f->g * f->x2 - f->a1 * f->y1 - f->a2 * f->y2;
	f->y2 = f->y1;
	f->y1 = y;
	f->x2 = f->x1;
	f->x1 = x0;
	return y;
}
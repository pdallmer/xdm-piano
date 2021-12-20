#include <lib/dsp.h>
#include <stdlib.h>

void connect_dsp_elements(dsp_element *out, dsp_element *in){
	in->input = out->output;
}

delay *new_delay(unsigned int length){
 	delay *d = (delay*)malloc(sizeof(delay));
 	d->buffer = (float*)malloc(length * sizeof(float));
 	d->index = 0;
 	d->length = length;
 	d->output = (float*)malloc(sizeof(float));
	return d;
}
 
one_zero *new_one_zero(float b0, float b1){
 	one_zero *f = (one_zero*)malloc(sizeof(one_zero));
 	f->x0 = 0;
 	f->x1 = 0;
 	f->b0 = b0;
 	f->b1 = b1;
 	f->output = (float*)malloc(sizeof(float));
 	return f;
}
 
void process_delay(delay *d){
	*d->output = d->buffer[d->index];
	d->buffer[d->index] = *d->input;
 	d->index = (d->index + 1) % d->length;
}
 
void process_one_zero(one_zero *f){
 	*f->output = f->b0 * f->x0 + f->b1 * f->x1;
 	f->x1 = f->x0;
 	f->x0 = *f->input;
}

#ifndef _DSP_H
#define _DSP_H

typedef struct dsp_element{
	float *input;
	float *output;
}dsp_element;

typedef struct delay{
	float *input;
	float *output;
	float *buffer;
	unsigned int index;
	unsigned int length;
}delay;

typedef struct one_zero{
	float *input;
	float *output;
	float x0; 
	float x1;
	float b0; 
	float b1; 
}one_zero;

void connect_dsp_elements(dsp_element *out, dsp_element *in);

delay *new_delay(unsigned int length);

one_zero *new_one_zero(float b0, float b1);

void process_delay(delay *d);

void process_one_zero(one_zero *f);

#endif

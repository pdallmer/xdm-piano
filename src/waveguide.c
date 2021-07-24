#include "waveguide.h"


waveguide *new_waveguide(float length)
{
	waveguide *new_waveguide = (waveguide*)malloc(sizeof(waveguide));
	new_waveguide->rl = length / 2;
	new_waveguide->ll = floor(length - new_waveguide->rl);
	new_waveguide->ll = length - (new_waveguide->rl + new_waveguide->ll) < 1 ? new_waveguide->ll - 1 : new_waveguide->ll;
	new_waveguide->tuning_filter = new_thiran(length - (new_waveguide->rl + new_waveguide->ll));
	new_waveguide->r = (float*)malloc(new_waveguide->rl * sizeof(float));
	new_waveguide->l = (float*)malloc(new_waveguide->ll * sizeof(float));
	new_waveguide->bridge_impedance = 1.0;
	new_waveguide->wave_impedance = 1e-3;
	int offset = floor(length / 6);
	new_waveguide->right_input = new_waveguide->rl - 1 - offset;
	new_waveguide->left_input = new_waveguide->ll - 1 - offset;
	new_waveguide->right_bridge = new_waveguide->rl - 1;
	new_waveguide->left_bridge = new_waveguide->ll -1;
	new_waveguide->right_nut = 0;
	new_waveguide->left_nut = 0;	
	return new_waveguide;
}


float waveguide_process(waveguide *w)
{
	float p = (w->bridge_impedance - w->wave_impedance) / (w->bridge_impedance + w->wave_impedance);
	float y = (1.0 - p) * w->r[w->right_bridge];
	float rin = w->l[w->left_nut];
	w->l[w->left_nut] = -p * w->r[w->right_bridge];
	w->r[w->right_nut] = thiran_process(w->tuning_filter, -rin);
	w->left_bridge = (w->left_bridge + 1) % w->ll;
	w->left_nut = (w->left_nut + 1) % w->ll;
	w->right_bridge = ((w->right_bridge + w->rl) - 1) % w->rl;
	w->right_nut = ((w->right_nut + w->rl) - 1) % w->rl;
	return y * 100;
}

void excite_waveguide(waveguide *w, float v)
{
	w->r[w->right_input] += v;
	w->l[w->left_input] += v;
}
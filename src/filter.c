#include "filter.h"


thiran* new_thiran(float m)
{
	thiran* new_thiran = (thiran*)malloc(sizeof(thiran));
	new_thiran->x1 = 0.0;
	new_thiran->y1 = 0.0;
	new_thiran->m = m;
	new_thiran->a1 = -1 * ((new_thiran->m - 1) / (new_thiran->m - 1 + 1)) * ((new_thiran->m - 1 + 1) / (new_thiran->m - 1 + 1 + 1));
	return new_thiran;
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

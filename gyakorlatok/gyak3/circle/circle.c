#include "circle.h"

#include <math.h>

void set_color(Color* color, int r, int g, int b) {
	color->r = r;
	color->g = g;
	color->b = b;
}

void set_circle_data(Circle* circle, double x, double y, double radius, Color color)
{
	circle->x = x;
	circle->y = y;
	if (radius > 0.0) {
		circle->radius = radius;
	} else {
		circle->radius = NAN;
	}
}

double calc_circle_area(const Circle* circle)
{
	double area = circle->radius * circle->radius * M_PI;
	return area;
}

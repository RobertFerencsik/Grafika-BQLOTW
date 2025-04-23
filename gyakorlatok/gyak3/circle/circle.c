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

void draw_line(Screen* screen, Point* a, Point* b, int color) {
  double x, y, dx, dy, step;
  dx = (b->x - a->x);
  dy = (b->y - a->y);
  step = (abs(dx) > abs(dy)) ? abs(dx) : abs(dy);
  dx /= step;
  dy /= step;
  x = a->x;
  y = a->y;
  for (int t = 0; t <= step; ++t) {
    screen->data[(int)x][(int)y];
    x += dx;
    y += dy;
  }
}

void draw_circle(Screen* screen, Circle* circle, int color) {
  double x_0, y_0, x, y;
  double phi, delta;
  phi = 0;
  delta = 0.01;
  x_0 = circle->radius * cos(phi) + circle->x;
  y_0 = circle->radius * sin(phi) + circle->y;
  while (phi < 2 * M_PI) {
    Point p_0;
    Point p;
    phi += delta;
    x = circle->radius * cos(phi) + circle->x;
    y = circle->radius * sin(phi) + circle->y;
    p_0->x = x_0;
    p_0->y = y_0;
    p->x = x;
    p->y = y;
    draw_line(screen, &p_0, &p, color);
    x_0 = x;
    y_0 = y;
  }
}
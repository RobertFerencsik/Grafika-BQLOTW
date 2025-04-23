#ifndef CIRCLE_H
#define CIRCLE_H

/**
 * Data of a circle object in Descartes coordinate system
 */
 
 typedef struct Screen {
  int w;
  int h;
  int data[WIDTH][HEIGHT];
} Screen;
 
 typedef struct Color {
	 int r,g,b;
 } Color;
 
typedef struct Circle
{
	double x;
	double y;
	double radius;
	Color color
} Circle;

/**
 * Set the data of the circle color and screen
 */
void set_color(Color* color, int r, int g, int b); 
void set_circle_data(Circle* circle, double x, double y, double radius, Color color);
void set_screen(Screen* screen, int w, int h);

/**
 * Calculate the area of the circle.
 */
double calc_circle_area(const Circle* circle);

/**
 * Draw the circle.
 */
void draw_circle(Screen* screen, Circle* circle, int color)

#endif // CIRCLE_H

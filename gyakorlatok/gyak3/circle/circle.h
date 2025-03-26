#ifndef CIRCLE_H
#define CIRCLE_H

/**
 * Data of a circle object in Descartes coordinate system
 */
 
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
 * Set the data of the circle
 */
void set_color(int r, int g, int b); 
void set_circle_data(Circle* circle, double x, double y, double radius, Color color);


/**
 * Calculate the area of the circle.
 */
double calc_circle_area(const Circle* circle);

#endif // CIRCLE_H

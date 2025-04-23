#include "ball.h"

#include <GL/gl.h>

#include <math.h>

void init_ball(Ball* ball, float x, float y)
{
    ball->x = x;
    ball->y = y;
    ball->radius = 50;
    ball->speed_x = 120;
    ball->speed_y = 150;
	ball->rotation = 1;
	ball->speed_rotation = 100;
}

void update_ball(Ball* ball, double time)
{
    ball->x += ball->speed_x * time;
    ball->y += ball->speed_y * time;
	ball->rotation += ball->speed_rotation * time;
}

void set_position(Ball* ball, float x, float y)
{
	ball->x = x;
	ball->y = y;
}

void change_ball_size(Ball* ball, float size) {
	if (ball->radius > 20 && ball->radius < 80)
		ball->radius += size;
}

void render_ball(Ball* ball)
{
    double angle;
    double x;
    double y;

    glPushMatrix();
    glTranslatef(ball->x, ball->y, 0.0);
	glRotatef(ball->rotation, 0.0f, 0.0f, 1.0f);
	
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0, 0.9, 0.8);
    glVertex2f(0, 0);
    angle = 0;
    while (angle < 2.0 * M_PI + 1) {
        x = cos(angle) * ball->radius;
        y = sin(angle) * ball->radius;
        glVertex2f(x, y);
        angle += 0.8;
    }
    glEnd();
    glPopMatrix();
}

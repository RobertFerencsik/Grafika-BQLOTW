#include "camera.h"
#include <GL/gl.h>
#include <math.h>

#define BOUNDARY_LIMIT 100.0 
#define TREE_X 4.0f
#define TREE_Y -25.0f
#define TREE_RADIUS 2.0f  // Adjust depending on how big the tree is


void init_camera(Camera* camera)
{
    camera->position.x = 0.0;
    camera->position.y = 0.0;
    camera->position.z = 1.0;

    camera->rotation.x = 0.0;
    camera->rotation.y = 0.0;
    camera->rotation.z = 0.0;

    camera->speed.x = 0.0;
    camera->speed.y = 0.0;
    camera->speed.z = 0.0;
	
	camera->acceleration = 1;
	camera->max_acceleration = 3;
	camera->angular_acceleration = 0;
    camera->max_angular_acceleration = 0;
	
	camera->gear = 0;
	camera->gear_ratio = 0.0f;
}

void update_camera(Camera* camera, double time)
{
    double angle;
    double side_angle;
	
	double prev_x = camera->position.x;
    double prev_y = camera->position.y;

    angle = degree_to_radian(camera->rotation.z);
    side_angle = degree_to_radian(camera->rotation.z + 90.0);

    camera->position.x += cos(angle) * camera->speed.y * time;
    camera->position.y += sin(angle) * camera->speed.y * time;
    camera->position.x += cos(side_angle) * camera->speed.x * time;
    camera->position.y += sin(side_angle) * camera->speed.x * time;
	
	    // Collision check with tree
    double dx = camera->position.x - TREE_X;
    double dy = camera->position.y - TREE_Y;
    double dist_sq = dx * dx + dy * dy;
    double radius_sq = TREE_RADIUS * TREE_RADIUS;

    if (dist_sq < radius_sq) {
        // Revert to previous position
        camera->position.x = prev_x;
        camera->position.y = prev_y;
    }
	    // Clamp camera within square boundary
    if (camera->position.x < -BOUNDARY_LIMIT) camera->position.x = -BOUNDARY_LIMIT;
    if (camera->position.x >  BOUNDARY_LIMIT) camera->position.x =  BOUNDARY_LIMIT;
    if (camera->position.y < -BOUNDARY_LIMIT) camera->position.y = -BOUNDARY_LIMIT;
    if (camera->position.y >  BOUNDARY_LIMIT) camera->position.y =  BOUNDARY_LIMIT;
	


}

void update_gear_ratio(Camera* camera) {
    switch (camera->gear) {
        case -1: camera->gear_ratio = -0.5f; break; // Reverse
        case 0:  camera->gear_ratio = 0.0f; break;  // Neutral
        case 1:  camera->max_angular_acceleration = 0.4; camera->gear_ratio = 0.5f; break;
        case 2:  camera->max_angular_acceleration = 0.5; camera->gear_ratio = 0.75f; break;
        case 3:  camera->max_angular_acceleration = 0.6; camera->gear_ratio = 1.0f; break;
        case 4:  camera->max_angular_acceleration = 0.7; camera->gear_ratio = 1.25f; break;
        case 5:  camera->max_angular_acceleration = 0.9; camera->gear_ratio = 1.5f; break;
        default: camera->gear_ratio = 1.0f; break;
    }
}

void rotate_camera(Camera* camera, double horizontal)
{
	camera->rotation.z += horizontal;
	if (camera->rotation.z < 0) {
        camera->rotation.z += 360.0;
    }
    if (camera->rotation.z > 360.0) {
        camera->rotation.z -= 360.0;
    }
}

void set_camera_speed(Camera* camera, double speed) {
    camera->speed.y = speed * camera->gear_ratio;
}


void set_view(const Camera* camera)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef(-(camera->rotation.x + 90), 1.0, 0, 0);
    glRotatef(-(camera->rotation.z -90), 0, 0, 1.0);
    glTranslatef(-camera->position.x, -camera->position.y, -camera->position.z);
}

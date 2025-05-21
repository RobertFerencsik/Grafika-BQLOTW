#ifndef CAMERA_H
#define CAMERA_H

#include "utils.h"

#include <stdbool.h>

/**
 * Camera, as a moving point with direction
 */
typedef struct Camera
{
    vec3 position;
    vec3 rotation;
    vec3 speed;
	
	double acceleration;
	double max_acceleration;
	double angular_acceleration;
    double max_angular_acceleration;
    int gear;              // Current gear (e.g., -1 for reverse, 0 for neutral, 1-5 for forward gears)
    float gear_ratio;      // Speed multiplier based on gear

    bool is_preview_visible;
} Camera;

/**
 * Initialize the camera to the start position.
 */
void init_camera(Camera* camera);

/**
 * Writes the camera position onto the console.
 */
void write_position(Camera* camera);

/**
 * Update the position of the camera.
 */
void update_camera(Camera* camera, double time);

/**
 * Update gear ratio.
 */
void update_gear_ratio(Camera* camera);


/**
 * Set the horizontal and vertical rotation of the view angle.
 */
void rotate_camera(Camera* camera, double horizontal);

/**
 * Set the speed of forward and backward motion.
 */
void set_camera_speed(Camera* camera, double speed);

/**
 * Apply the camera settings to the view transformation.
 */
void set_view(const Camera* camera);

void show_texture_preview();

#endif /* CAMERA_H */

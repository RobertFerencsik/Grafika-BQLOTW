#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "texture.h"

#include <obj/model.h>

typedef struct Scene
{
	Model tree;
    Material material;
	GLuint sky_front, sky_back, sky_left, sky_right, sky_top;
    GLuint texture_id_tree;
	GLuint texture_id_ground;
} Scene;

/**
 * Initialize the scene by loading models.
 */
void init_scene(Scene* scene);

/**
 * Set the lighting of the scene.
 */
void set_lighting();

/**
 * Set the current material.
 */
void set_material(const Material* material);

/**
 * Update the scene.
 */
void update_scene(Scene* scene);

/**
 * Render the scene objects.
 */
void render_scene(const Scene* scene, const Camera* camera);

/**
 * Draw the origin of the world coordinate system.
 */
void draw_origin();

/**
 * Draw a string (at a fixed location).
 */
void draw_string(const Scene* scene, const char* s);

/**
 * Draw a x,y  plane.
 */
void draw_ground();

/**
 * Draw the sky.
 */
void draw_skybox(const Scene* scene,const Camera* camera);

#endif /* SCENE_H */

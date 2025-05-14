#include "scene.h"
#include "camera.h"

#include <obj/load.h>
#include <obj/draw.h>

void init_scene(Scene* scene)
{
    load_model(&(scene->tree), "assets/models/tree.obj");
    
	scene->texture_id_tree = load_texture("assets/textures/tree.jpg");
    scene->texture_id_ground = load_texture("assets/textures/race.webp");
	
	scene->sky_front = load_texture("assets/textures/sky_front.png");
	scene->sky_back = load_texture("assets/textures/sky_back.png");
	scene->sky_left = load_texture("assets/textures/sky_left.png");
	scene->sky_right = load_texture("assets/textures/sky_right.png");
	scene->sky_top = load_texture("assets/textures/sky_top.png");


	scene->material.ambient.red = 0.2;
	scene->material.ambient.green = 0.2;
	scene->material.ambient.blue = 0.2;

	scene->material.diffuse.red = 0.8;
	scene->material.diffuse.green = 0.8;
	scene->material.diffuse.blue = 0.8;

	scene->material.specular.red = 1.0;
	scene->material.specular.green = 1.0;
	scene->material.specular.blue = 1.0;

	scene->material.shininess = 50.0;

}


void set_lighting()
{
	
    float ambient_light[] = { 0.3f, 0.3f, 0.3f, 1.0f };  // Global light
    float diffuse_light[] = { 1.0f, 1.0f, 1.0f, 1.0f };  // Main white light
    float specular_light[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // Shiny specular
    float position[] = { 100.0f, 100.0f, 100.0f, 1.0f };       // Light above and to the side
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void update_lighting (float x) {
	
	
	float ambient_light[] = { 0.3f, 0.3f, 0.3f, 1.0f };  // Global light
    float diffuse_light[] = { 1.0f, 1.0f, 1.0f, 1.0f };  // Main white light
    float specular_light[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // Shiny specular
    float position[] = { 100.0f, 100.0f, 100.0f, 1.0f };       // Light above and to the side
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void set_material(const Material* material)
{
    float ambient_material_color[] = {
        material->ambient.red,
        material->ambient.green,
        material->ambient.blue
    };

    float diffuse_material_color[] = {
        material->diffuse.red,
        material->diffuse.green,
        material->diffuse.blue
    };

    float specular_material_color[] = {
        material->specular.red,
        material->specular.green,
        material->specular.blue
    };

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &(material->shininess));
}

void update_scene(Scene* scene)
{

}

void render_scene(const Scene* scene, const Camera* camera)
{
	glDisable(GL_LIGHTING);           // Ne világítsuk meg a skyboxot
    draw_skybox(scene, camera);
    glEnable(GL_LIGHTING);            // Utána vissza lehet kapcsolni
    set_material(&(scene->material));
    set_lighting();
    
    // Draw the ground (bind its texture separately)
    glBindTexture(GL_TEXTURE_2D, scene->texture_id_ground);  // Bind the ground texture
    draw_ground(scene);  // Draw the ground with its own texture

    // Draw tree (bind its texture separately)
    glPushMatrix();                      
	glBindTexture(GL_TEXTURE_2D, scene->texture_id_tree);
    glRotatef(90, 1.0f, 0.0f, 0.0f);
    glTranslatef(4.0f, -1.0f, 25.0f);
    draw_model(&(scene->tree));
    glPopMatrix();
	
	glPushMatrix();                      
	glBindTexture(GL_TEXTURE_2D, scene->texture_id_tree);
    glRotatef(90, 1.0f, 0.0f, 0.0f);
    glTranslatef(4.0f, -1.0f, 25.0f);
    draw_model(&(scene->tree));
    glPopMatrix();
}

void draw_ground(const Scene* scene) {
    float box_side = 100;

    glColor3f(1.0f, 1.0f, 1.0f);  // No color modification

    glBegin(GL_QUADS);
		glNormal3f(0.0f, 0.0f, 1.0f);
        // Bottom-left
        glTexCoord2f(0.0f, 0.0f);  
        glVertex3f(-box_side, -box_side, -1.0f);

        // Bottom-right
        glTexCoord2f(1.0f, 0.0f);  
        glVertex3f(box_side, -box_side, -1.0f);

        // Top-right
        glTexCoord2f(1.0f, 1.0f);  
        glVertex3f(box_side, box_side, -1.0f);

        // Top-left
        glTexCoord2f(0.0f, 1.0f);  
        glVertex3f(-box_side, box_side, -1.0f);
    glEnd();
}

void draw_skybox(const Scene* scene, const Camera* camera)
{
    float size = 100.0f;

    glDepthMask(GL_FALSE);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(camera->position.x, camera->position.y, camera->position.z);

    // RIGHT
    glBindTexture(GL_TEXTURE_2D, scene->sky_right);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 1); glVertex3f(size, size, -size);    
        glTexCoord2f(1, 1); glVertex3f(-size, size, -size);   
        glTexCoord2f(1, 0); glVertex3f(-size, size, size);    
        glTexCoord2f(0, 0); glVertex3f(size, size, size);     
    glEnd();

    // BACK
    glBindTexture(GL_TEXTURE_2D, scene->sky_back);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 1); glVertex3f(-size, -size, size);    
        glTexCoord2f(1, 1); glVertex3f(-size, -size, -size);   
        glTexCoord2f(1, 0); glVertex3f(-size, size, -size);    
        glTexCoord2f(0, 0); glVertex3f(-size, size, size);     
    glEnd();
	
    // FRONT
    glBindTexture(GL_TEXTURE_2D, scene->sky_front);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 1); glVertex3f(size, -size, -size);    
        glTexCoord2f(1, 1); glVertex3f(size, -size, size);     
        glTexCoord2f(1, 0); glVertex3f(size, size, size);      
        glTexCoord2f(0, 0); glVertex3f(size, size, -size);     
    glEnd();

    // RIGHT
    glBindTexture(GL_TEXTURE_2D, scene->sky_right);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 1); glVertex3f(-size, -size, size);    
        glTexCoord2f(1, 1); glVertex3f(size, -size, size);     
        glTexCoord2f(1, 0); glVertex3f(size, -size, -size);    
        glTexCoord2f(0, 0); glVertex3f(-size, -size, -size);   
    glEnd();

    glPopMatrix();
    glDepthMask(GL_TRUE);
}
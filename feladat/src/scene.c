#include "scene.h"
#include "camera.h"

#include <math.h>
#include <obj/load.h>
#include <obj/draw.h>

void init_scene(Scene* scene)
{
    load_model(&(scene->tree), "assets/models/tree.obj");
	load_model(&(scene->car), "assets/models/car.obj");
    
	scene->texture_id_tree = load_texture("assets/textures/tree.jpg");
	scene->texture_id_paint = load_texture("assets/textures/paint.webp");
    scene->texture_id_ground = load_texture("assets/textures/race.webp");
	
	scene->texture_sky = load_texture("assets/textures/sky.jpg");

	scene->fog_enabled = false;
	scene->time_of_day = 1.0f;

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

/*
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
*/

void update_lighting(float time_of_day) {
    float radius = 100.0f;
    float sun_x = radius * cosf(time_of_day);
    float sun_y = radius * sinf(time_of_day);
    float sun_z = 100.0;

    float position[] = { sun_x, sun_y, sun_z, 1.0f };

    float intensity = fmaxf(0.6f, sinf(time_of_day));

    float ambient_light[]  = { 0.3f * intensity, 0.3f * intensity, 0.3f * intensity, 1.0f };
    float diffuse_light[]  = { 1.0f * intensity, 1.0f * intensity, 0.9f * intensity, 1.0f };
    float specular_light[] = { 1.0f * intensity, 1.0f * intensity, 1.0f * intensity, 1.0f };

    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
}

void set_fog(bool enabled)
{
    if (enabled) {
        glEnable(GL_FOG);
        glFogi(GL_FOG_MODE, GL_LINEAR);
        GLfloat fogColor[] = { 0.5f, 0.6f, 0.7f, 1.0f };
        glFogfv(GL_FOG_COLOR, fogColor);
        glFogf(GL_FOG_DENSITY, 0.06f);
        glFogf(GL_FOG_START, 3.0f);
        glFogf(GL_FOG_END, 100.0f);
        glHint(GL_FOG_HINT, GL_DONT_CARE);
    } else {
        glDisable(GL_FOG);
    }
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
	set_fog(scene->fog_enabled);


	scene->time_of_day += 0.005f;
    if (scene->time_of_day > 2 * M_PI) {
        scene->time_of_day -= 2 * M_PI;
    }

    update_lighting(scene->time_of_day);

}

void render_scene(const Scene* scene, const Camera* camera)
{
	glDisable(GL_LIGHTING); 
    draw_skybox(scene, camera);
	glEnable(GL_LIGHTING); 
    set_material(&(scene->material));
	//set_lighting();
    
    glBindTexture(GL_TEXTURE_2D, scene->texture_id_ground);
    draw_ground(scene);

    glPushMatrix();                      
	glBindTexture(GL_TEXTURE_2D, scene->texture_id_tree);
    glRotatef(90, 1.0f, 0.0f, 0.0f);
    glTranslatef(4.0f, -1.0f, 25.0f);
    draw_model(&(scene->tree));
    glPopMatrix();
	
	
	// Draw the car in front of the camera
	glPushMatrix();

	float offset_distance = 2.0f;
	float angle_rad = degree_to_radian(camera->rotation.z);

	float car_x = camera->position.x + cos(angle_rad) * offset_distance;
	float car_y = camera->position.y + sin(angle_rad) * offset_distance;

	glTranslatef(car_x, car_y, -1.0f);  // Align with camera
	glRotatef(camera->rotation.z, 0.0f, 0.0f, 1.0f);  // Face same direction

	glBindTexture(GL_TEXTURE_2D, scene->texture_id_paint);
	draw_model(&(scene->car));

	glPopMatrix();
	
	/*
	glPushMatrix();                      
	glBindTexture(GL_TEXTURE_2D, scene->texture_id_paint);
    glRotatef(90, 1.0f, 0.0f, 0.0f);
    glTranslatef(10.0f, -1.0f, 25.0f);
    draw_model(&(scene->car));
    glPopMatrix();
	*/
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
    glBindTexture(GL_TEXTURE_2D, scene->texture_sky);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 1); glVertex3f(size, size, -size);    
        glTexCoord2f(1, 1); glVertex3f(-size, size, -size);   
        glTexCoord2f(1, 0); glVertex3f(-size, size, size);    
        glTexCoord2f(0, 0); glVertex3f(size, size, size);     
    glEnd();

    // BACK

    glBegin(GL_QUADS);
        glTexCoord2f(0, 1); glVertex3f(-size, -size, size);    
        glTexCoord2f(1, 1); glVertex3f(-size, -size, -size);   
        glTexCoord2f(1, 0); glVertex3f(-size, size, -size);    
        glTexCoord2f(0, 0); glVertex3f(-size, size, size);     
    glEnd();
	
    // FRONT

    glBegin(GL_QUADS);
        glTexCoord2f(0, 1); glVertex3f(size, -size, -size);    
        glTexCoord2f(1, 1); glVertex3f(size, -size, size);     
        glTexCoord2f(1, 0); glVertex3f(size, size, size);      
        glTexCoord2f(0, 0); glVertex3f(size, size, -size);     
    glEnd();

    // RIGHT

    glBegin(GL_QUADS);
        glTexCoord2f(0, 1); glVertex3f(-size, -size, size);    
        glTexCoord2f(1, 1); glVertex3f(size, -size, size);     
        glTexCoord2f(1, 0); glVertex3f(size, -size, -size);    
        glTexCoord2f(0, 0); glVertex3f(-size, -size, -size);   
    glEnd();

    glPopMatrix();
    glDepthMask(GL_TRUE);
}
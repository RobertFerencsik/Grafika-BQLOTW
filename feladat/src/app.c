#include "app.h"
#include "scene.h"
#include "camera.h"
#include <stdio.h>
#include <SDL2/SDL_image.h>
#include <string.h>

void init_app(App* app, int width, int height)
{
    int error_code;
    int inited_loaders;

    app->is_running = false;

    error_code = SDL_Init(SDL_INIT_EVERYTHING);
    if (error_code != 0) {
        printf("[ERROR] SDL initialization error: %s\n", SDL_GetError());
        return;
    }

    app->window = SDL_CreateWindow(
        "Cube!",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        width, height,
        SDL_WINDOW_OPENGL);
    if (app->window == NULL) {
        printf("[ERROR] Unable to create the application window!\n");
        return;
    }
	
	app->renderer = SDL_CreateRenderer(app->window, -1, SDL_RENDERER_ACCELERATED);

    inited_loaders = IMG_Init(IMG_INIT_PNG);
    if (inited_loaders == 0) {
        printf("[ERROR] IMG initialization error: %s\n", IMG_GetError());
        return;
    }

    app->gl_context = SDL_GL_CreateContext(app->window);
    if (app->gl_context == NULL) {
        printf("[ERROR] Unable to create the OpenGL context!\n");
        return;
    }

    init_opengl();
	SDL_SetRelativeMouseMode(SDL_TRUE); // This hides the cursor and allows infinite movement
    reshape(width, height);
    init_camera(&(app->camera));
    init_scene(&(app->scene));

    app->is_running = true;
}

void init_opengl()
{
    glShadeModel(GL_SMOOTH);

    glEnable(GL_NORMALIZE);
    glEnable(GL_AUTO_NORMAL);

    glClearColor(0.1, 0.1, 0.1, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_DEPTH_TEST);


    glClearDepth(1.0);

    glEnable(GL_TEXTURE_2D);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void reshape(GLsizei width, GLsizei height)
{
    int x, y, w, h;
    double ratio;

    ratio = (double)width / height;
    if (ratio > VIEWPORT_RATIO) {
        w = (int)((double)height * VIEWPORT_RATIO);
        h = height;
        x = (width - w) / 2;
        y = 0;
    }
    else {
        w = width;
        h = (int)((double)width / VIEWPORT_RATIO);
        x = 0;
        y = (height - h) / 2;
    }

    glViewport(x, y, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(
        -.08, .08,
        -.06, .06,
        .1, 1000.0
    );
}



typedef struct {
    const char* title;
    const char* message;
} TutorialStep;

void show_instructions(SDL_Window* window) {
    TutorialStep steps[] = {
        {
            "Welcome to the Game!",
            "In this instruction you can see how to control your vehicle.\n\nPress 'Next' to continue."
        },
        {
            "Movement",
            "Use up, left, right to move the camera:\nW - Forward and Backward\nA - Left\nD - Right"
        },
        {
            "Shifting Gears",
            "Use number keys to shift gears:\n1-5: Forward Gears\nN: Neutral\nR: Reverse"
        },
		{
            "Toggle fog",
            "Use the key I to toggle fog on/off"
        },
        {
            "You're Ready!",
            "Press 'Start Game' to begin your adventure!"
        }
    };

    const int total_steps = sizeof(steps) / sizeof(steps[0]);
    int current_step = 0;

    while (1) {
        const SDL_MessageBoxButtonData buttons[] = {
            { /* .flags, .buttonid, .text */ 0, 0, "Back" },
            { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, (current_step == total_steps - 1) ? "Start Game" : "Next" },
            { SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 2, "Exit" }
        };

        const SDL_MessageBoxData messageboxdata = {
            SDL_MESSAGEBOX_INFORMATION,
            window,
            steps[current_step].title,
            steps[current_step].message,
            SDL_arraysize(buttons),
            buttons,
            NULL // Color scheme
        };

        int buttonid;
        if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0) {
            SDL_Log("error displaying message box");
            break;
        }

        if (buttonid == 0 && current_step > 0) {
            current_step--; // Back
        } else if (buttonid == 1) {
            if (current_step < total_steps - 1)
                current_step++; // Next
            else
                break; // Start Game
        } else if (buttonid == 2) {
            // Exit
            exit(0);
        }
    }
}



void handle_app_events(App* app)
{
    SDL_Event event;
    static bool key_w_down = false;
    static bool key_a_down = false;
    static bool key_d_down = false;
    static bool handbrake_engaged = false;

    // Poll and update key states
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
		switch (event.key.keysym.sym) {
        case SDLK_f:
			if (app->scene.fog_enabled)
				app->scene.fog_enabled = false;
			else
				app->scene.fog_enabled = true;
            break;
    }
        case SDL_KEYDOWN:
            switch (event.key.keysym.scancode) {
            case SDL_SCANCODE_ESCAPE:
                app->is_running = false;
                break;
				case SDL_SCANCODE_F:
					if (app->scene.fog_enabled){
						app->scene.fog_enabled = false;
					} else {
						app->scene.fog_enabled = true;
					}
				break;
			case SDL_SCANCODE_1: app->camera.gear = 1; update_gear_ratio(&(app->camera)); break;
			case SDL_SCANCODE_2: app->camera.gear = 2; update_gear_ratio(&(app->camera)); break;
			case SDL_SCANCODE_3: app->camera.gear = 3; update_gear_ratio(&(app->camera)); break;
			case SDL_SCANCODE_4: app->camera.gear = 4; update_gear_ratio(&(app->camera)); break;
			case SDL_SCANCODE_5: app->camera.gear = 5; update_gear_ratio(&(app->camera)); break;
			case SDL_SCANCODE_N: app->camera.gear = 0; update_gear_ratio(&(app->camera)); break;
			case SDL_SCANCODE_R: app->camera.gear = -1; update_gear_ratio(&(app->camera)); break;
			case SDL_SCANCODE_P:
				write_position(&(app->camera));
				break;
            case SDL_SCANCODE_UP:
                key_w_down = true;
                break;
            case SDL_SCANCODE_LEFT:
                key_a_down = true;
                break;
            case SDL_SCANCODE_RIGHT:
                key_d_down = true;
                break;
            case SDL_SCANCODE_I:
                show_instructions(app->window);
                break;
            default:
                break;
            }
            break;

        case SDL_KEYUP:
            switch (event.key.keysym.scancode) {
            case SDL_SCANCODE_UP:
                key_w_down = false;
                break;
            case SDL_SCANCODE_LEFT:
                key_a_down = false;
                break;
            case SDL_SCANCODE_RIGHT:
                key_d_down = false;
                break;
            case SDL_SCANCODE_SPACE:
                handbrake_engaged = false;
                break;
            default:
                break;
            }
            break;

        case SDL_QUIT:
            app->is_running = false;
            break;

        default:
            break;
        }
    }

    // Apply combined input logic outside event loop
    if (!handbrake_engaged) {
        if (key_w_down) {
            set_camera_speed(&(app->camera), 10.0);
		} else {
            set_camera_speed(&(app->camera), 0.0);
        }
    }
	
    if (key_a_down && key_w_down) {
		if(app->camera.angular_acceleration < app->camera.max_angular_acceleration) {
			app->camera.angular_acceleration +=0.03;
		}
        rotate_camera(&(app->camera), app->camera.angular_acceleration);
    } else if (key_d_down && key_w_down) {
		if(app->camera.angular_acceleration > -(app->camera.max_angular_acceleration)) {
			app->camera.angular_acceleration -=0.03;
		}
        rotate_camera(&(app->camera), app->camera.angular_acceleration);
    } else {
		app->camera.angular_acceleration = 0; 
	}
}



void update_app(App* app)
{
    double current_time;
    double elapsed_time;

    current_time = (double)SDL_GetTicks() / 1000;
    elapsed_time = current_time - app->uptime;
    app->uptime = current_time;

    update_camera(&(app->camera), elapsed_time);
    update_scene(&(app->scene));
}

void render_app(App* app)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    set_view(&(app->camera));
    render_scene(&(app->scene),&(app->camera));
    glPopMatrix();
    SDL_GL_SwapWindow(app->window);
}

void destroy_app(App* app)
{
    if (app->gl_context != NULL) {
        SDL_GL_DeleteContext(app->gl_context);
    }

    if (app->window != NULL) {
        SDL_DestroyWindow(app->window);
    }

    SDL_Quit();
}

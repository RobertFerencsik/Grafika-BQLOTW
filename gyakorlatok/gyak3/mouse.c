 #include <stdio.h>
 #include <SDL2/SDL.h>
 
 #define MAX_LINE_COUNT 4

// Struct to represent a color
typedef struct Color {
    int r;
    int g;
    int b;
} Color;

// Struct to represent a line
typedef struct Line {
    int x1, y1, x2, y2;
    Color color;
} Line;
 
int main(int argc, char *argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }
    
    // Create a window
    SDL_Window *window = SDL_CreateWindow("SDL Line Drawing", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
    if (!window) {
        fprintf(stderr, "Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    
    // Create a renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        fprintf(stderr, "Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    
    Line lines[MAX_LINE_COUNT];
    int line_count = 0;
    int is_first_click = 1;
    int x1, y1;
    
    // Main event loop
    int quit = 0;
    SDL_Event event;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    quit = 1; // Exit loop when window is closed
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT) { // Left mouse click
                        if (is_first_click) {
                            x1 = event.button.x;
                            y1 = event.button.y;
                            is_first_click = 0;
                        } else {
                            if (line_count < MAX_LINE_COUNT) {
                                lines[line_count].x1 = x1;
                                lines[line_count].y1 = y1;
                                lines[line_count].x2 = event.button.x;
                                lines[line_count].y2 = event.button.y;
                                lines[line_count].color = (Color){255, 255, 255}; // Default white color
                                line_count++;
                            }
                            is_first_click = 1;
                        }
                    }
                    break;
            }
        }
        
        // Render
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
        SDL_RenderClear(renderer);
        
        for (int i = 0; i < line_count; i++) {
            SDL_SetRenderDrawColor(renderer, lines[i].color.r, lines[i].color.g, lines[i].color.b, 255);
            SDL_RenderDrawLine(renderer, lines[i].x1, lines[i].y1, lines[i].x2, lines[i].y2);
        }
        
        SDL_RenderPresent(renderer);
    }
    
    // Clean up resources
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
	return 0;
 }

/*
 * To compile this program using GCC, use the following command:
 * gcc main.c -o sdl_mouse.exe -lmingw32 -lSDL2main -lSDL2
 *
 * Then, run the compiled executable:
 * ./sdl_mouse
 */
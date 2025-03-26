#include <stdio.h>
#include <SDL2/SDL.h>

#define MAX_SHAPES 100
#define PALETTE_SIZE 5
#define PALETTE_HEIGHT 50

// Struct to represent a color
typedef struct Color {
    int r;
    int g;
    int b;
} Color;

// Struct to represent a rectangle
typedef struct Rectangle {
    int x, y, w, h;
    Color color;
} Rectangle;

int main(int argc, char *argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }
    
    // Create a window
    SDL_Window *window = SDL_CreateWindow("SDL Color Palette", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
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
	
    
    // Define color palette
    Color palette[PALETTE_SIZE] = {
        {255, 0, 0},   // Red
        {0, 255, 0},   // Green
        {0, 0, 255},   // Blue
        {255, 255, 0}, // Yellow
        {255, 255, 255} // White
    };
    
    Color selected_color = palette[0]; // Default color
    Rectangle rectangles[MAX_SHAPES];
    int rect_count = 0;
    
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
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        int mx = event.button.x;
                        int my = event.button.y;
                        
                        // Check if the click is inside the palette area
                        if (my < PALETTE_HEIGHT) {
                            int index = mx / (640 / PALETTE_SIZE);
                            if (index < PALETTE_SIZE) {
                                selected_color = palette[index];
                            }
                        } else if (rect_count < MAX_SHAPES) {
							if (event.button.button == SDL_BUTTON_LEFT) {
                            rectangles[rect_count].x = mx - 25;
                            rectangles[rect_count].y = my - 25;
                            rectangles[rect_count].w = 50;
                            rectangles[rect_count].h = 50;
                            rectangles[rect_count].color = selected_color;
                            rect_count++;
                        }
                    }
                    break;
            }
        }
        
        // Render
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
        SDL_RenderClear(renderer);
        
        // Draw palette
        for (int i = 0; i < PALETTE_SIZE; i++) {
            SDL_SetRenderDrawColor(renderer, palette[i].r, palette[i].g, palette[i].b, 255);
            SDL_Rect rect = {i * (640 / PALETTE_SIZE), 0, 640 / PALETTE_SIZE, PALETTE_HEIGHT};
            SDL_RenderFillRect(renderer, &rect);
        }
        
        // Draw rectangles
        for (int i = 0; i < rect_count; i++) {
            SDL_SetRenderDrawColor(renderer, rectangles[i].color.r, rectangles[i].color.g, rectangles[i].color.b, 255);
            SDL_Rect rect = {rectangles[i].x, rectangles[i].y, rectangles[i].w, rectangles[i].h};
            SDL_RenderFillRect(renderer, &rect);
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
 * To compile this program using GCC on Windows, use the following command:
 * gcc -o sdl_color_palette sdl_color_palette.c -lmingw32 -lSDL2main -lSDL2
 *
 * Then, run the compiled executable:
 * ./sdl_color_palette
 */

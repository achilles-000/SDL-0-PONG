#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>


    struct direction {
    bool right;
    bool left;
    bool up;
    bool down;
    int vertical;

    };

int main(int argc, char *argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    // Variables:
    struct direction dir0 = { false, false, false, false, 300 };
    struct direction dir1 = { false, false, false, false, 300 };


    // Create a window
    SDL_Window *window = SDL_CreateWindow("Movable Window",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          640, 480,
                                          SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (window == NULL) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Create renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Main loop
    SDL_bool running = SDL_TRUE;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT: {
                    running = SDL_FALSE;
                    break;
                }
                case SDL_MOUSEBUTTONDOWN: {
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        // Save the initial window position
                        int initialX, initialY;
                        SDL_GetWindowPosition(window, &initialX, &initialY);

                        // Move the window with the mouse
                        int windowX, windowY;
                        while (SDL_PollEvent(&event)) {
                            if (event.type == SDL_MOUSEMOTION) {
                                windowX = initialX + event.motion.x - event.button.x;
                                windowY = initialY + event.motion.y - event.button.y;
                                SDL_SetWindowPosition(window, windowX, windowY);
                            } else if (event.type == SDL_MOUSEBUTTONUP &&
                                       event.button.button == SDL_BUTTON_LEFT) {
                                break;
                            }
                        }
                    }
                    break;
                }
                case SDL_KEYDOWN: {
                    if (event.key.keysym.sym == SDLK_w) {
                        dir0.up = true;
                    }
                    if (event.key.keysym.sym == SDLK_s) {
                        dir0.down = true;
                    }
                    if (event.key.keysym.sym == SDLK_UP) {
                        dir1.up = true;
                    }
                    if (event.key.keysym.sym == SDLK_DOWN) {
                        dir1.down = true;
                    }
                    break;

                }
                case SDL_KEYUP: {
                    if (event.key.keysym.sym == SDLK_w) {
                        dir0.up = false;
                    }
                    if (event.key.keysym.sym == SDLK_s) {
                        dir0.down = false;
                    }
                    if (event.key.keysym.sym == SDLK_UP) {
                        dir1.up = false;
                    }
                    if (event.key.keysym.sym == SDLK_DOWN) {
                        dir1.down = false;
                    }
                    break;

                }
                default:
                    break;
            }
        }

        if (dir0.up == true && dir0.vertical > 0) dir0.vertical -= 1;
        if (dir0.down == true && dir0.vertical < 380) dir0.vertical += 1;
        if (dir1.up == true && dir1.vertical > 0) dir1.vertical -= 1;
        if (dir1.down == true && dir1.vertical < 380) dir1.vertical += 1;
        

        

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Set the draw color to red and draw a filled rectangle
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        SDL_Rect rect0 = {5, dir0.vertical, 25, 100};
        SDL_Rect rect1 = {610, dir1.vertical, 25, 100};
        SDL_RenderFillRect(renderer, &rect0);
        SDL_RenderFillRect(renderer, &rect1);
        
        // Update the screen
        SDL_RenderPresent(renderer);


    }

    // Clean up
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
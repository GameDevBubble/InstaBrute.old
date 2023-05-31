#include <iostream>
#include "main.h"
#include "SDL2/SDL.h"

int main(int argc, char* argv[]) {
    Log::Log(Log::LogLevel::INFO, "initiated InstaBrute", "InstaBrute", true, true);
    // Init sdl
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        Log::Log(Log::LogLevel::ERROR, "failed to init sdl", "InstaBrute", true, true);
        return 1;
    }

    // Create the Main window
    SDL_Window* window = SDL_CreateWindow("InstaBrute", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
    if (!window) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Window could not be created! SDL_Error: %s\n", SDL_GetError());
        Log::Log(Log::LogLevel::ERROR, "failed to create window" + std::string(SDL_GetError()), "InstaBrute", true, true);
        return 1;
    } else {
        Log::Log(Log::LogLevel::INFO, "created SDL2 window", "InstaBrute", true, true);
    }

    // Create the Main renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        Log::Log(Log::LogLevel::ERROR, "failed to create renderer" + std::string(SDL_GetError()), "InstaBrute", true, true);
        return 1;
    } else {
        Log::Log(Log::LogLevel::INFO, "created SDL2 renderer", "InstaBrute", true, true);
    }
    // Main Loop
    bool quit = false;
    SDL_Event event;
    while (!quit) {
        // Handle events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }

        // Clear the screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Render the screen
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
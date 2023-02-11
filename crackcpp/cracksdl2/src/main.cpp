#include <Windows.h>
#include <SDL.h>

typedef struct {
    SDL_Renderer* renderer;
    SDL_Window* window;
} App;

INT WINAPI wWinMain(
    _In_ HINSTANCE instance,
    _In_opt_ HINSTANCE prevInstance,
    _In_ LPWSTR    cmdLine,
    _In_ int       cmdShow) {

    bool is_active = true;
    SDL_Event event;
    SDL_Window* window;
    SDL_Surface* screen;
    SDL_Renderer* renderer;

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        return -1;
    }

    window = SDL_CreateWindow(
        "cracksdl2",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        800, 600,
        //SDL_WINDOW_FULLSCREEN |
        SDL_WINDOW_OPENGL
    );
    screen = SDL_GetWindowSurface(window);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    while (is_active) {
        // ÊÂ¼þ
        while (0 != SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                is_active = false;
                break;
            }
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    is_active = false;
                    break;
                }
            }
        }

        // Ö¡
        SDL_UpdateWindowSurface(window);
    }

    if (nullptr != renderer) SDL_DestroyRenderer(renderer);
    if (nullptr != screen) SDL_FreeSurface(screen);
    if (nullptr != window) SDL_DestroyWindow(window);
    return 0;
}
#include <Windows.h>
#include <SDL.h>
#include <SDL_image.h>

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

    auto ir = IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

    SDL_Texture* bg = IMG_LoadTexture(renderer, "res/bg.jpg");
    // auto* bgs = IMG_Load("res/bg.png");
    const char* error = IMG_GetError();
    int w, h;
    SDL_QueryTexture(bg, NULL, NULL, &w, &h);
    SDL_Rect bgRect;
    bgRect.x = 0;
    bgRect.y = 0;
    bgRect.w = 800;
    bgRect.h = 600;

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
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, bg, NULL, &bgRect);
        SDL_RenderPresent(renderer);
        // SDL_UpdateWindowSurface(window);
    }

    if (nullptr != renderer) SDL_DestroyRenderer(renderer);
    if (nullptr != screen) SDL_FreeSurface(screen);
    if (nullptr != window) SDL_DestroyWindow(window);
    return 0;
}
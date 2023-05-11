#include <iostream>
#include <SDL2/SDL.h>

#include "RenderManager.h"

int main(int argv, char *args[])
{
    if (SDL_Init(SDL_INIT_VIDEO) > 0)
        std::cout << "GG MAN YOURE FKED" << std::endl;
    else
    {
        RenderManager renderManager = RenderManager();
        renderManager.createMainWindow("HOLY SMOKES");
        SDL_Event event;

        bool isGameRuning = true;

        while (isGameRuning)
        {
            while (SDL_PollEvent(&event))
            {
                if(event.type == SDL_QUIT) {
                    renderManager.quit();
                    isGameRuning = false;
                    break;
                }
            }
            renderManager.render(renderManager.loadTexture("resource/texture_sample.jpg"));
        }
    }
    return 0;
}
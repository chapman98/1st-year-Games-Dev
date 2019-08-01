#ifndef SFWINDOW_H
#define SFWINDOW_H

#include <SDL.h>
#include "SFCommon.h"

#define FIRST_SUPPORTED -1

class SFWindow {
public:
    SFWindow(Uint32 w, Uint32 h, SDL_Color drawColor);
    ~SFWindow();
    void ClearScreen();
    void ShowScreen();
    
    int GetWidth();
    int GetHeight();
    SDL_Window* getWindow();
    SDL_Renderer* getRenderer();
private:
    SDL_Window*   window;
    SDL_Renderer* renderer;
};

#endif

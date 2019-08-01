#include <SDL.h>
#include <memory>

using namespace std;

#include "SFCommon.h"
#include "SFApp.h"

#define SECOND_MILLIS 1000
#define FRAME_RATE 60

enum UserEvents { UPDATE_EVENT };

Uint32 PushUpdateEvent(Uint32 interval, void *param) {
    SDL_Event event;
    event.type = SDL_USEREVENT;
    event.user.code = UPDATE_EVENT;
    event.user.data1 = 0;
    event.user.data2 = 0;
    SDL_PushEvent(&event);
    return interval;
}

shared_ptr<SFWindow> InitGraphics() {

    // Initialise SDL - when using C/C++ it's common to have to
    // initialise libraries by calling a function within them.
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) < 0) {
        throw SFException("Failed to initialise SDL");
    }

    Uint32 width = 640;
    Uint32 height = 480;
    
    // color gray
    SDL_Color drawColor = { 128, 128, 128, SDL_ALPHA_OPAQUE };

    return make_shared<SFWindow>(width, height, drawColor);
}

int main(int arc, char ** argv) {




    try {
        // Initialise graphics context
        shared_ptr<SFWindow> window = InitGraphics();
        
        // Initialise world
        shared_ptr<SFApp> game = make_shared<SFApp>(window);

        int delay = SECOND_MILLIS / FRAME_RATE;
        
        // Set up the timer to call "PushUpdateEvent" every delay milliseconds
        SDL_AddTimer(delay, PushUpdateEvent, NULL);

        game->StartMainLoop();
        
    } catch (SFException& e) {
        cout << "Exception occurred!" << endl;
        cout << e.what() << endl;
        cout << "Exception details: " << SDL_GetError() << endl;
    }

    return 0;

}

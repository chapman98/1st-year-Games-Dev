#ifndef SFBOUNDINGBOX_H
#define SFBOUNDINGBOX_H

#include <memory>
#include <SDL.h>

#include "SFMath.h"

using namespace std;

class SFBoundingBox {
public:
    SFBoundingBox(const Point2, const int, const int);
    virtual ~SFBoundingBox();
    void SetPosition(Point2 &);
    void Translate(Vector2 &);
    int GetX();
    int GetY();
    int GetWidth();
    int GetHeight();
    SDL_Rect GetBox();

    bool CollidesWith(const shared_ptr<SFBoundingBox>);

private:
    SDL_Rect box;
};

#endif

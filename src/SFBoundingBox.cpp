#include "SFBoundingBox.h"

SFBoundingBox::SFBoundingBox(const Point2 position, const int width, const int height) {
    box = { (int) position.getX(), (int) position.getY(), width, height };
}

SFBoundingBox::~SFBoundingBox() {
}

void SFBoundingBox::SetPosition(Point2 & p) {
    box.x = (int) p.getX();
    box.y = (int) p.getY();
}

void SFBoundingBox::Translate(Vector2 & v) {
    box.x += v.getX();
    box.y += v.getY();
}

int SFBoundingBox::GetX() {
    return box.x;
}

int SFBoundingBox::GetY() {
    return box.y;
}

int SFBoundingBox::GetWidth() {
    return box.w;
}

int SFBoundingBox::GetHeight() {
    return box.h;
}

SDL_Rect SFBoundingBox::GetBox() {
    return box;
}

bool SFBoundingBox::CollidesWith(const shared_ptr<SFBoundingBox> b) {
    return SDL_HasIntersection(&box, &b->box) == SDL_TRUE;
}

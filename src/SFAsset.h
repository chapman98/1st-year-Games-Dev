#ifndef SFASSET_H
#define SFASSET_H

#include <string>
#include <memory>
#include <iostream>

#include <SDL.h>
#include <SDL_image.h>

using namespace std;

#include "SFCommon.h"
#include "SFEvent.h"
#include "SFWindow.h"
#include "SFBoundingBox.h"

/**
 * We could create SFPlayer, SFProjectile and SFAsset which are subclasses
 * of SFAsset.  However, I've made an implementation decision to use this
 * enum to mark the type of the SFAsset.  If we add more asset types then
 * the subclassing strategy becomes a better option.
 */
enum SFASSETTYPE { SFASSET_DEAD, SFASSET_PLAYER, SFASSET_PROJECTILE, SFASSET_ALIEN, SFASSET_COIN };

class SFAsset {
public:
    SFAsset(const SFASSETTYPE, const std::shared_ptr<SFWindow>);
    SFAsset(const SFAsset&);
    virtual ~SFAsset();

    virtual void      SetPosition(Point2 &);
    virtual Point2    GetPosition();
    virtual Point2    GetCenter();
    virtual void      OnRender();
    virtual void      GoEast();
    virtual void      GoWest();
    virtual void      GoNorth();
    virtual void      GoSouth();
    virtual void      SetNotAlive();
    virtual bool      IsAlive();
    virtual void      HandleCollision();

    virtual bool                      CollidesWith(shared_ptr<SFAsset>);
    virtual shared_ptr<SFBoundingBox> GetBoundingBox();
    
private:
    SDL_Texture               * sprite;
    shared_ptr<SFBoundingBox>   bbox;
    SFASSETTYPE                 type;
    std::shared_ptr<SFWindow>   sf_window;
};

#endif

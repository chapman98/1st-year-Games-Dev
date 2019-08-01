#include "SFApp.h"
#include "Score.h"

static Score s; //create the scoreboard
static int counter = 0;
static bool coin_check = false; // used to stop the coin from giving the player more points

SFApp::SFApp(std::shared_ptr<SFWindow> window) : is_running(true), window(window) {
    int canvas_w = window->GetWidth();
    int canvas_h = window->GetHeight();

    player = make_shared<SFAsset>(SFASSET_PLAYER, window);
    auto player_pos = Point2(canvas_w / 2 - player->GetBoundingBox()->GetWidth() / 2, canvas_h - player->GetBoundingBox()->GetHeight());
    player->SetPosition(player_pos);

    const int number_of_aliens = 10;
    for (int i = 0; i < number_of_aliens; i++) {
        // place an alien at width/number_of_aliens * i
        auto alien = make_shared<SFAsset>(SFASSET_ALIEN, window);
        auto pos = Point2((canvas_w / number_of_aliens) * i + alien->GetBoundingBox()->GetWidth() / 2, 000.0f);
        alien->SetPosition(pos);
        aliens.push_back(alien);
    }

    auto coin = make_shared<SFAsset>(SFASSET_COIN, window);
    auto pos = Point2((canvas_w / 4), 0);
    coin->SetPosition(pos);
    coins.push_back(coin);
}

SFApp::~SFApp() {}

/**
 * Handle all events that come from SDL.
 * These are timer or keyboard events.
 */
void SFApp::OnEvent(SFEvent& event) {
    SFEVENT the_event = event.GetCode();
    switch (the_event) {
    case SFEVENT_QUIT:
        is_running = false;
        break;
    case SFEVENT_UPDATE:
        OnUpdate();
        OnRender();
        break;
    case SFEVENT_PLAYER_LEFT:
	if ((player->GetPosition().getX())  > 0)
	{
        player->GoWest();
	}
        break;
    case SFEVENT_PLAYER_RIGHT:
	if ((player->GetPosition().getX()) <= 575)
	{
        player->GoEast();
	}
        break;
    case SFEVENT_FIRE:
        FireProjectile();
        break;
    }
}

void SFApp::StartMainLoop() {
    SDL_Event event;
    while (SDL_WaitEvent(&event) && is_running) {
        
        // wrap an SDL_Event with our SFEvent
        SFEvent sfevent((const SDL_Event)event);
        
        // handle our SFEvent
        OnEvent(sfevent);
    }
}

void SFApp::OnUpdate() {
	
s.display(window->getWindow());//updates score and displays it on window


    // 1. Move / update game objects
    for (auto p : projectiles) {
        p->GoNorth(); 

    }

    // coins
    for (auto c : coins) {
        c->GoSouth();
	if (player->CollidesWith(c) && coin_check == false)
	{
        coin_check = true;  //stops coin from giving the player more points
	s.increment_Coin(); //add 10 points to player when they go over the coin
	}
    }

    // enemies
    for (auto a : aliens) {
	a->GoSouth(); //Aliens will go towards the players slowly
	if(player->CollidesWith(a))
		   {
		    s.decrement();	//decrement score when the player hits an alien
		    a->HandleCollision();
	            }

    }

    // 2. Detect collisions
    for (auto p : projectiles) {
        for (auto a : aliens) {
		
            if (p->CollidesWith(a)) { 
		s.increment();// add 1 to the score
                p->HandleCollision();
                a->HandleCollision();
            }
        }
    }

    // 3. Remove dead aliens (the long way)
    list<shared_ptr<SFAsset>> tmp;
    for (auto a : aliens) {
        if (a->IsAlive()) {
            tmp.push_back(a);
        }
    }
    aliens.clear();
    aliens = list<shared_ptr<SFAsset>>(tmp);


for (auto a : aliens) {
 if (a->GetPosition().getY() > 520){ //remove aliens which leave the window
  a->HandleCollision();
 }
}


  if(aliens.size()==0){ //check if there is any aliens left
     for (int i = 0; i < 10; i++) {
       	auto alien = make_shared<SFAsset>(SFASSET_ALIEN, window);
    	auto pos = Point2((window->GetWidth()/ 10) * i + alien->GetBoundingBox()->GetWidth() / 2, 000.0f);
        alien->SetPosition(pos); //spawns aliens
        aliens.push_back(alien);
    		}
	}

}

void SFApp::OnRender() {
    // 1. Clear visible content
    window->ClearScreen();

    // 2. Draw game objects off-screen
    player->OnRender();

    for (auto p : projectiles) {
        if (p->IsAlive()) { 
            p->OnRender(); 
        }
    }

    for (auto a : aliens) {
        if (a->IsAlive()) { 
            a->OnRender(); 
        }
    }


    for (auto c : coins) {
        c->OnRender();
    }

    // 3. Switch the off-screen buffer to be on-screen
    window->ShowScreen();
}

void SFApp::FireProjectile() {
    auto bullet = make_shared<SFAsset>(SFASSET_PROJECTILE, window);
    auto v = player->GetCenter();
    auto pos = Point2(v.getX() - bullet->GetBoundingBox()->GetWidth() / 2, v.getY());
    bullet->SetPosition(pos);
    projectiles.push_back(bullet);
}

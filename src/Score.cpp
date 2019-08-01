#include "Score.h"


using namespace std;

  Score::Score() //starts score
  {
    cout << Score::score << endl;
  }

  void Score::increment()
  { 
  Score::score++; //increments score
  }

void Score::decrement()
  { 
  Score::score--; //decrements score when you hit an alien
  }


 void Score::increment_Coin()
  { 
  Score::score = Score::score + 10; //adds 10 to the score when player picks coin up 
  }


  void Score::display(SDL_Window* window)
{
//displays the score the the window title

    std::string display_score = ("Starship Fontana Score = " + std::to_string(score));
    SDL_SetWindowTitle(window, display_score.c_str());


}



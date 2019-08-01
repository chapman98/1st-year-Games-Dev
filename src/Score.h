#include <iostream>
#include <SDL.h>


class Score

{
	public:
		Score();
		void increment();
		void decrement();
		void display(SDL_Window* window);
		void increment_Coin();

	private:
		int score = 0;
		  
		
};

#include "Game.h"

int main() {
	Game game("Test", 1000, 1000);
	
	//main loop
	while (game.GetWindowShouldClose())//while window is not closed
	{
		//update Events
		game.Update();

		//render
		game.Render();
	}
	return 0;
}
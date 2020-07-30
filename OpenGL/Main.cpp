#include "Game.h"

int main() {
	Game game("Test");
	
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
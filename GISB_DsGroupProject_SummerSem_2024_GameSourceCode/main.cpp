#include <iostream>
using namespace std;

#include "Game.h"

int main() {
	cout << "\tGet ready to play!" << endl;
	cout << "*.*.*.* WHEEL  OF  FORTUNE *.*.*.*" << endl;
	cout << "___________________________________________________________________\n" << endl;
	
	Game game;
    // Game logic
    game.startGame();
    
	return 0;
}

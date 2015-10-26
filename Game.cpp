#include <iostream>
#include <string>
#include "Piece.cpp"
#include "Player.cpp"

int main()
{
	Player B("Alfred");
	std::cout << B.getName() << std::endl;

	B.printState();
	B.check();
	B.printState();
	B.checkMate();
	B.printState();
	B.gameEnd();
	B.printState();
	B.inGame();
	B.printState();
	B.checkMate();
	B.printState();
	B.inGame();
	B.gameNull();
	B.gameEnd();
	B.printState();	

	return 0;
}

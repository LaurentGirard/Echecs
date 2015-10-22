#include <iostream>
#include <string>
#include "Piece.cpp"
#include "Player.cpp"

int main()
{
	// Piece kingB = new King();
	King kingW("white");
	King kingB("black");
	kingW.printPiece();
	kingB.printPiece();

	Player B("Alfred");
	std::cout << B.getName() << std::endl;	
	return 0;
}

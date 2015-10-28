#include <iostream>
#include <string>
#include "Piece.cpp"
#include "Player.cpp"

int main()
{
	// Piece* _board[8][8]; // A revoir
	Player playerA("Alfred","White");
	Player playerB("Alphonse","Black");

	playerB.getPieces()[8]->printPiece();

	return 0;
}

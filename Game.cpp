#include <iostream>
#include "Piece.cpp"

int main()
{
	// Piece kingB = new King();
	King kingW("white");
	King kingB("black");
	kingW.printPiece();
	kingB.printPiece();
	return 0;
}

/**
* @file Piece.cpp
* @author P. Sullivan, G.Laurent
* @since 25/12/2015
* @brief implémentation des méthodes de la classe Factory
*
**/

#include "Factory.hpp"

//------------------------------------------------------------------------------------------------------
//----------------------------- CLASS Factory ----------------------------------------------------------
//------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------
Factory::Factory() {}

//------------------------------------------------------------------------------------------------------
Factory::~Factory(){}

//------------------------------------------------------------------------------------------------------
std::vector<Piece*> Factory::buildPieces(bool color){
	int i = 0;

	std::vector<Piece*> listPieces;

	FactorySpawn* spawn = new FactorySpawn();
	FactoryRook* rook = new FactoryRook(); 
	FactoryKnight* knight = new FactoryKnight(); 
	FactoryBishop* Bishop = new FactoryBishop(); 
	FactoryQueen* Queen = new FactoryQueen();
	FactoryKing* King = new FactoryKing(); 

	std::vector<Piece*> spawns = spawn->buildPieces(color);
	std::vector<Piece*> rooks = rook->buildPieces(color);
	std::vector<Piece*> knights = knight->buildPieces(color);
	std::vector<Piece*> bishops = Bishop->buildPieces(color);
	std::vector<Piece*> queens = Queen->buildPieces(color);
	std::vector<Piece*> kings = King->buildPieces(color);

	while (i < spawns.size())
	{
		listPieces.push_back(spawns[i]);
		++i;
	}

	listPieces.push_back(rooks[0]);
	listPieces.push_back(knights[0]);
	listPieces.push_back(bishops[0]);
	listPieces.push_back(queens[0]);
	listPieces.push_back(kings[0]);
	listPieces.push_back(bishops[1]);
	listPieces.push_back(knights[1]);
	listPieces.push_back(rooks[1]);

	return listPieces;
}

//------------------------------------------------------------------------------------------------------
//----------------------------- CLASS FactorySpawn -----------------------------------------------------
//------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------
FactorySpawn::FactorySpawn() {}

//------------------------------------------------------------------------------------------------------
FactorySpawn::~FactorySpawn(){}

//------------------------------------------------------------------------------------------------------
std::vector<Piece*> FactorySpawn::buildPieces(bool color){
	std::vector<Piece*> listPieces;
	int y;

	if(!color)
		y = 1;
	else
		y = 6;

	for(int i = 0; i < 8; ++i)
		listPieces.push_back(new Spawn(i,y,color));

	return listPieces;
}

//------------------------------------------------------------------------------------------------------
//----------------------------- CLASS FactoryRook ------------------------------------------------------
//------------------------------------------------------------------------------------------------------
FactoryRook::FactoryRook() {}

//------------------------------------------------------------------------------------------------------
FactoryRook::~FactoryRook(){}

//------------------------------------------------------------------------------------------------------
std::vector<Piece*> FactoryRook::buildPieces(bool color){
	std::vector<Piece*> listPieces;
	int y;

	if(!color)
		y = 0;
	else
		y = 7;

	listPieces.push_back(new Rook(0,y));
	listPieces.push_back(new Rook(7,y));

	return listPieces;
}

//------------------------------------------------------------------------------------------------------
//----------------------------- CLASS FactoryKnight ----------------------------------------------------
//------------------------------------------------------------------------------------------------------
FactoryKnight::FactoryKnight() {}

//------------------------------------------------------------------------------------------------------

FactoryKnight::~FactoryKnight(){}

//------------------------------------------------------------------------------------------------------
std::vector<Piece*> FactoryKnight::buildPieces(bool color){
	std::vector<Piece*> listPieces;
	int y;

	if(!color)
		y = 0;
	else
		y = 7;

	listPieces.push_back(new Knight(1,y));
	listPieces.push_back(new Knight(6,y));

	return listPieces;
}

//------------------------------------------------------------------------------------------------------
//----------------------------- CLASS FactoryBishop ----------------------------------------------------
//------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------
FactoryBishop::FactoryBishop() {}

//------------------------------------------------------------------------------------------------------
FactoryBishop::~FactoryBishop(){}

//------------------------------------------------------------------------------------------------------

std::vector<Piece*> FactoryBishop::buildPieces(bool color){
	std::vector<Piece*> listPieces;
	int y;

	if(!color)
		y = 0;
	else
		y = 7;

	listPieces.push_back(new Bishop(2,y));
	listPieces.push_back(new Bishop(5,y));
	return listPieces;
}

//------------------------------------------------------------------------------------------------------
//----------------------------- CLASS FactoryQueen -----------------------------------------------------
//------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------
FactoryQueen::FactoryQueen() {}

//------------------------------------------------------------------------------------------------------
FactoryQueen::~FactoryQueen(){}

//------------------------------------------------------------------------------------------------------
std::vector<Piece*> FactoryQueen::buildPieces(bool color){
	std::vector<Piece*> listPieces;
	int y;

	if(!color)
		y = 0;
	else
		y = 7;

	listPieces.push_back(new Queen(3,y));
	return listPieces;
}

//------------------------------------------------------------------------------------------------------
//----------------------------- CLASS FactoryKing ------------------------------------------------------
//------------------------------------------------------------------------------------------------------
FactoryKing::FactoryKing() {}
//------------------------------------------------------------------------------------------------------

FactoryKing::~FactoryKing(){}

//------------------------------------------------------------------------------------------------------
std::vector<Piece*> FactoryKing::buildPieces(bool color){
	std::vector<Piece*> listPieces;
	int y;	

	if(!color)
		y = 0;
	else
		y = 7;

	listPieces.push_back(new King(4,y));
	return listPieces;
}

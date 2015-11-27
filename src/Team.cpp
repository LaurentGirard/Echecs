/**
* @file Team.cpp
* @author P. Sullivan, G.Laurent
* @since 25/12/2015
* @brief implémentation des méthodes de la classe Team
*
**/

#include "Team.hpp"

//------------------------------------------------------------------------------------------------------

Team::Team(){}

//------------------------------------------------------------------------------------------------------

Team::~Team(){}

//------------------------------------------------------------------------------------------------------

std::vector<Piece*> Team::buildTeamNormal(bool color)
{
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
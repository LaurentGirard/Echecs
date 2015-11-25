/**
* @file ObjectPool.cpp
* @author P. Sullivan, G.Laurent
* @since 25/12/2015
* @brief implémentation des méthodes de la classe ObjectPool
*
**/

#include "ObjectPool.hpp"

//------------------------------------------------------------------------------------------------------
ObjectPool::ObjectPool()
{
	unsigned int i;

	// Les 16 pièces d'un joueur sont créées mais pas opérationnelles
	for(i = 0 ; i < 17 ; ++i)
		_pool[i] = new Piece();
}

//------------------------------------------------------------------------------------------------------
ObjectPool::~ObjectPool() {}

//------------------------------------------------------------------------------------------------------
Piece* ObjectPool::pickPiece(unsigned int indPiece)
{

	Piece* p = NULL;

	// Si l'indice est valide, l'emplacement de la pièce est mis à NULL et l'ancien contenu est retourné
	if(indPiece < 17)
	{
		p = _pool[indPiece];
		_pool[indPiece] = NULL;
	}

	return p;
}

//------------------------------------------------------------------------------------------------------
void ObjectPool::putPiece(Piece* piece, unsigned int indPiece)
{
	// L'emplacement à l'indice indPiece contient maintenant piece
	_pool[indPiece] = piece;
}

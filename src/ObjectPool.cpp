/**
* @file ObjectPool.cpp
* @author P. Sullivan, G.Laurent
* @since 25/12/2015
* @brief implémentation des méthodes de la classe ObjectPool
*
**/

#include "ObjectPool.hpp"

//------------------------------------------------------------------------------------------------------
ObjectPool::ObjectPool() {}

//------------------------------------------------------------------------------------------------------
ObjectPool::~ObjectPool() {}

//------------------------------------------------------------------------------------------------------
Piece* ObjectPool::pickPiece(unsigned int indPiece)
{
	Piece* p = NULL;

	// Si l'indice est valide, l'emplacement de la pièce est mis à NULL et l'ancien contenu est retourné
	if(indPiece < 16)
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

//------------------------------------------------------------------------------------------------------
Piece** ObjectPool::getPool()
{
	return _pool;
}

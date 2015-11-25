/**
 * @file ObjectPool.hpp
 * @author P. Sullivan, G.Laurent
 * @since 25/12/2015
 * @brief Définition de la classe ObjectPool permettant à un joueur de prendre ou remettre ses pièces depuis une pool
 *
**/

#ifndef __OBJECTPOOL_HPP__
#define __OBJECTPOOL_HPP__

#include "Piece.hpp"

class ObjectPool{

	private:

		Piece* _pool[16];			// L'odre des pièces est le même que celui dans l'attribut _pieces de la classe Player

	public:

		/**
       	* @brief Constructeur, crée un objet ObjectPool
       	*/
			ObjectPool();

		/**
		* @brief Destructeur
		*/
			~ObjectPool();

		/**
		* @brief permet de prendre un objet dans la pool
		* @param unsigned int, indice de la pool permettant d'enlever la Piece* à cet indice
		* @return Piece*, pointeur de la pièce sortante
		*/
			Piece* pickPiece(unsigned int indPiece);

		/**
		* @brief permet de remettre un objet dans la pool
		* @param Piece*, pointeur de la pièce à remettre dans la pool (en fin de partie)
		* @param unsigned int, indice de la pool permettant de remettre la Piece* à cet indice
		*/
			void putPiece(Piece* piece, unsigned int indPiece);

};

#endif // __OBJECTPOOL_HPP__
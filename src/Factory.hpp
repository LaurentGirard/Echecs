/**
 * @file Chess.hpp
 * @author P. Sullivan, G.Laurent
 * @since 25/12/2015
 * @brief Définition de la factoty
 *
**/

#ifndef __FACTORY_HPP__
#define __FACTORY_HPP__

#include "Piece.hpp"


/**
* @class factory 
* 
* @brief Classe abstaite de Piece
*
*/

class Factory
{
    public:
    	Factory();
    	~Factory();
		virtual std::vector<Piece*> fabriquePieces(bool color);//false == White
};

/**
* @class fabriquespawns
* 
* @brief Classe fabriquespawns héritant de Factory
*
*/

class FactorySpawn : public Factory
{

      public:
      FactorySpawn();
      ~FactorySpawn();
      std::vector<Piece*> fabriquePieces(bool color);
};

/**
* @class fabriquespawns
* 
* @brief Classe fabriquespawns héritant de Factory
*
*/

class FactoryRook : public Factory
{

      public:
      FactoryRook();
      ~FactoryRook();
      std::vector<Piece*> fabriquePieces(bool color);
};

/**
* @class fabriquespawns
* 
* @brief Classe fabriquespawns héritant de Factory
*
*/

class FactoryKnight : public Factory
{

      public:
      FactoryKnight();
      ~FactoryKnight();
      std::vector<Piece*> fabriquePieces(bool color);
};

/**
* @class fabriquespawns
* 
* @brief Classe fabriquespawns héritant de Factory
*
*/

class FactoryBishop : public Factory
{

      public:
      FactoryBishop();
      ~FactoryBishop();
      std::vector<Piece*> fabriquePieces(bool color);
};

/**
* @class fabriquespawns
* 
* @brief Classe fabriquespawns héritant de Factory
*
*/

class FactoryQueen : public Factory
{

      public:
      FactoryQueen();
      ~FactoryQueen();
      std::vector<Piece*> fabriquePieces(bool color);
};

/**
* @class fabriquespawns
* 
* @brief Classe fabriquespawns héritant de Factory
*
*/

class FactoryKing : public Factory
{

      public:
      FactoryKing();
      ~FactoryKing();
      std::vector<Piece*> fabriquePieces(bool color);
};


#endif // __FACTORY_HPP__

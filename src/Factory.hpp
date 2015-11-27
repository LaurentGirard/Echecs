/**
 * @file Factory.hpp
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
* @brief Classe abstaite Factory
*
*/

class Factory
{
    public:

    Factory();
    virtual ~Factory();

		virtual std::vector<Piece*> buildPieces(bool color); //false == White
};

/**
* @class FactorySpawn
* 
* @brief Classe FactorySpawn héritant de Factory
*
*/

class FactorySpawn : public Factory
{

      public:
      FactorySpawn();
      ~FactorySpawn();
      std::vector<Piece*> buildPieces(bool color);
};

/**
* @class FactoryRook
* 
* @brief Classe FactoryRook héritant de Factory
*
*/

class FactoryRook : public Factory
{

      public:
      FactoryRook();
      ~FactoryRook();
      std::vector<Piece*> buildPieces(bool color);
};

/**
* @class FactoryKnight
* 
* @brief Classe FactoryKnight héritant de Factory
*
*/

class FactoryKnight : public Factory
{

      public:
      FactoryKnight();
      ~FactoryKnight();
      std::vector<Piece*> buildPieces(bool color);
};

/**
* @class FactoryBishop
* 
* @brief Classe FactoryBishop héritant de Factory
*
*/

class FactoryBishop : public Factory
{

      public:
      FactoryBishop();
      ~FactoryBishop();
      std::vector<Piece*> buildPieces(bool color);
};

/**
* @class FactoryQueen
* 
* @brief Classe FactoryQueen héritant de Factory
*
*/

class FactoryQueen : public Factory
{

      public:
      FactoryQueen();
      ~FactoryQueen();
      std::vector<Piece*> buildPieces(bool color);
};

/**
* @class FactoryKing
* 
* @brief Classe FactoryKing héritant de Factory
*
*/

class FactoryKing : public Factory
{

      public:
      FactoryKing();
      ~FactoryKing();
      std::vector<Piece*> buildPieces(bool color);
};


#endif // __FACTORY_HPP__

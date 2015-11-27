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
    /**
    * @brief Constructeur de Factory
     */
    Factory();

    /**
    * @brief Destructeur de Factory
     */
    virtual ~Factory();

    /**
    * @brief Permet de retourner une liste de Pièce*
    * @param bool color, false signifie que l'équipe est white
    * @return une liste de Piece*
    */
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
      /**
      * @brief Constructeur de FactorySpawn
      */
      FactorySpawn();

      /**
      * @brief Destructeur de FactorySpawn
       */
      ~FactorySpawn();

      /**
      * @brief Permet de retourner une liste de Pièce* bien initialisée pour les spawns normals
      * @param bool color, false signifie que l'équipe est white
      * @return une liste de Piece*
      */
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

      /**
      * @brief Constructeur de FactoryRook
      */
      FactoryRook();

      /**
      * @brief Destructeur de FactoryRook
       */
      ~FactoryRook();

      /**
      * @brief Permet de retourner une liste de Pièce* bien initialisée pour les Rooks normals
      * @param bool color, false signifie que l'équipe est white
      * @return une liste de Piece*
      */
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

      /**
      * @brief Constructeur de FactoryKnight
      */
      FactoryKnight();


      /**
      * @brief Destructeur de FactoryKnight
       */
      ~FactoryKnight();

      /**
      * @brief Permet de retourner une liste de Pièce* bien initialisée pour les Knights normals
      * @param bool color, false signifie que l'équipe est white
      * @return une liste de Piece*
      */
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

      /**
      * @brief Constructeur de FactoryBishop
      */
      FactoryBishop();

      /**
      * @brief Destructeur de FactoryBishop
       */
      ~FactoryBishop();

      /**
      * @brief Permet de retourner une liste de Pièce* bien initialisée pour les Bishops normals
      * @param bool color, false signifie que l'équipe est white
      * @return une liste de Piece*
      */
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

      /**
      * @brief Constructeur de FactoryQueen
      */
      FactoryQueen();

      /**
      * @brief Destructeur de FactoryQueen
       */
      ~FactoryQueen();

      /**
      * @brief Permet de retourner une liste de Pièce* bien initialisée pour la reine normale
      * @param bool color, false signifie que l'équipe est white
      * @return une liste de Piece*
      */
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

      /**
      * @brief Constructeur de FactoryKing
      */
      FactoryKing();

      /**
      * @brief Destructeur de FactoryKing
       */
      ~FactoryKing();

      /**
      * @brief Permet de retourner une liste de Pièce* bien initialisée pour le roi normal
      * @param bool color, false signifie que l'équipe est white
      * @return une liste de Piece*
      */
      std::vector<Piece*> buildPieces(bool color);
};


#endif // __FACTORY_HPP__

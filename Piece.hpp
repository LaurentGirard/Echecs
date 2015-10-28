/**
 * @file Piece.hpp
 * @author P. Sullivan, G.Laurent
 * @since 25/12/2015
 * @brief Définition d'une classe de Piece
 *
**/

#ifndef __Piece_HPP__
#define __Piece_HPP__

#include <string>
#include "Cell.cpp"
/**
* @class Piece 
* 
* @brief Classe abstaite de Piece
*
*/

class Piece
{
	protected:

		Cell* square;				// attribut : case sur laquelle est la pièce
		bool alive;					// attribut : état de la pièce ( 0 = pièce détruite ; 1 = pièce en vie )

	public:

      /**
       * @brief Constructeur, crée une pièce
       */
		Piece(unsigned int x, unsigned int y);

      /**
       * @brief Destructeur de Piece
       */
		~Piece();

	/**
       * @brief de Getter l'attribut _square
       * @return attribut _square
       */
		Cell* getSquare();

      /**
       * @brief Setter de l'attribut _square
       * @param newCell est la nouvelle case sur laquelle est la pièce
       */
		void setSquare(Cell* newCell);

	/**
       * @brief Getter de l'attribut _alive
       * @return attribut _alive
       */
		bool asAlive();

      /**
       * @brief Setter de l'attribut _alive
       * @param newAlive
       */
		void setAlive(bool newAlive);

	/**
		* @brief procédure permettant d'afficher les coordonnées de la case sur laquelle se trouve la pièce
		*/

		void printPiece();
		
	/**
       * @brief procédure virtuelle permettant le déplacement de la pièce vers la case dest
       * @param Cell dest
       */
		virtual void move(Cell* dest) = 0;

	/**
       * @brief procédure virtuelle permettant de savoir si la destination est possible ou non
       * @param Cell dest
       */
		virtual bool destination(Cell* dest) = 0;
};

/**
* @class Spawn
* 
* @brief Classe Spawn héritant de Piece
*
*/

class Spawn : public Piece
{
      public:

      /**
       * @brief Constructeur, crée un objet Spawn de coordonnées x,y
       * @param unsigned int x
       * @param unsigned int y
       */
            Spawn(unsigned int x, unsigned int y);

      /**
       * @brief Destructeur d'un objet cavalier
       */
            ~Spawn();

      /**
       * @brief procédure virtuelle permettant le déplacement du Pion vers la case dest
       * @param Cell dest
       */
            virtual void move(Cell* dest);

      /**
       * @brief procédure virtuelle permettant de savoir si la destination est possible ou non
       * @param Cell dest
       */
            virtual bool destination(Cell* dest);
};

/**
* @class Rook 
* 
* @brief Classe Rook héritant de Piece
*
*/

class Rook : public Piece
{
      private:

            bool _moved;                        // attribut : permet de savoir si la tour a bougé ou non pendant la partie

      public:

      /**
       * @brief Constructeur, crée un objet Rook de coordonnées x,y
       * @param unsigned int x
       * @param unsigned int y
       */
            Rook(unsigned int x, unsigned int y);

      /**
       * @brief Destructeur d'un objet Rook
       */
            ~Rook();

      /**
       * @brief Getter de l'attribut _moved
       * @return attribut _moved
       */
            bool asMoved();

      /**
       * @brief Setter de l'attribut _moved
       * @param bool newMoved
       */
            void setMoved(bool newMoved);

      /**
       * @brief procédure virtuelle permettant le déplacement de la Tour vers la case dest
       * @param Cell dest
       */
            virtual void move(Cell* dest);

      /**
       * @brief procédure virtuelle permettant de savoir si la destination est possible ou non
       * @param Cell dest
       */
            virtual bool destination(Cell* dest);
};

/**
* @class Knight
* 
* @brief Classe Knight héritant de Piece
*
*/

class Knight : public Piece
{
	public:

    	/**
       * @brief Constructeur, crée un objet Knight de coordonnées x,y
       * @param unsigned int x
       * @param unsigned int y
       */
		Knight(unsigned int x, unsigned int y);

	/**
       * @brief Destructeur d'un objet cavalier
       */
		~Knight();

	/**
       * @brief procédure virtuelle permettant le déplacement du Cavalier vers la case dest
       * @param Cell dest
       */
		virtual void move(Cell* dest);

	/**
       * @brief procédure virtuelle permettant de savoir si la destination est possible ou non
       * @param Cell dest
       */
		virtual bool destination(Cell* dest);
};

/**
* @class Bishop 
* 
* @brief Classe Bishop héritant de Piece
*
*/

class Bishop : public Piece
{
      public:

      /**
       * @brief Constructeur, crée un objet Bishop de coordonnées x,y
       * @param unsigned int x
       * @param unsigned int y
       */
            Bishop(unsigned int x, unsigned int y);

      /**
       * @brief Destructeur d'un objet cavalier
       */
            ~Bishop();

      /**
       * @brief procédure virtuelle permettant le déplacement du Fou vers la case dest
       * @param Cell dest
       */
            virtual void move(Cell* dest);

      /**
       * @brief procédure virtuelle permettant de savoir si la destination est possible ou non
       * @param Cell dest
       */
            virtual bool destination(Cell* dest);
};

/**
* @class Queen 
* 
* @brief Classe Queen héritant de Piece
*
*/

class Queen : public Piece
{
      public:

      /**
       * @brief Constructeur, crée un objet Queen de coordonnées x,y
       * @param unsigned int x
       * @param unsigned int y
       */
            Queen(unsigned int x, unsigned int y);

      /**
       * @brief Destructeur d'un objet cavalier
       */
            ~Queen();

      /**
       * @brief procédure virtuelle permettant le déplacement de la Reine vers la case dest
       * @param Cell dest
       */
            virtual void move(Cell* dest);

      /**
       * @brief procédure virtuelle permettant de savoir si la destination est possible ou non
       * @param Cell dest
       */
            virtual bool destination(Cell* dest);
};

/**
* @class King 
* 
* @brief Classe King héritant de Piece
*
*/

class King : public Piece
{
      private:

            bool _moved;                        // attribut : permet de savoir si le roi a bougé ou non pendant la partie

      public:

      /**
       * @brief Constructeur, crée un objet King d'une couleur mise en paramètre
       * @param string color
       */
            King(unsigned int x, unsigned int y);

      /**
       * @brief Destructeur d'un objet King
       */
            ~King();

      /**
       * @brief Getter de l'attribut _moved
       * @return attribut _moved
       */
            bool asMoved();

      /**
       * @brief Setter de l'attribut _moved
       * @param bool newMoved
       */
            void setMoved(bool newMoved);

      /**
       * @brief procédure virtuelle permettant le déplacement du Roi vers la case dest
       * @param Cell dest
       */
            virtual void move(Cell* dest);

      /**
       * @brief procédure virtuelle permettant de savoir si la destination est possible ou non
       * @param Cell dest
       */
            virtual bool destination(Cell* dest);
};

#endif // __Piece_HPP__
/**
 * @file Piece.hpp
 * @author P. Sullivan, G.Laurent
 * @since 25/12/2015
 * @brief Définition d'une classe de Piece
 *
**/

#ifndef __Piece_HPP__
#define __Piece_HPP__

#include "Cell.cpp"
#include <vector>

/**
* @class Piece 
* 
* @brief Classe abstaite de Piece
*
*/

class Piece
{
	protected:

		Cell* square;                                         // attribut : case sur laquelle est la pièce
		bool alive;					                  // attribut : état de la pièce ( 0 = pièce détruite ; 1 = pièce en vie )
            std::vector< std::vector< Cell> > movements;          // attribut : liste de liste de cases représentant les déplacements possibles de la pièce
            std::string label;                                    // attribut : libellé de la pièce (S = Spawn, R = Rook, C = Knight etc.)
	
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
       * @brief de Getter l'attribut square
       * @return attribut square
       */
		Cell* getSquare();

      /**
       * @brief Setter de l'attribut square
       * @param newCell est la nouvelle case sur laquelle est la pièce
       */
		void setSquare(Cell* newCell);

	/**
       * @brief Getter de l'attribut alive
       * @return attribut alive
       */
		bool asAlive();

      /**
       * @brief Setter de l'attribut alive
       * @param newAlive
       */
		void setAlive(bool newAlive);

      /**
       * @brief de Getter l'attribut label
       * @return attribut label
       */
            std::string getLabel();

	/**
	* @brief procédure permettant d'afficher les coordonnées de la case sur laquelle se trouve la pièce
	*/
		void printPiece();
		
	/**
       * @brief fonction virtuelle retournant la liste des cases possibles pour un déplacement de la pièce
       * @return vector<Cell> 
       */
		virtual void movement();

		std::vector< std::vector< Cell> > getmovements();

		virtual std::vector< Cell> getcaneat();
};

/**
* @class Spawn
* 
* @brief Classe Spawn héritant de Piece
*
*/

class Spawn : public Piece
{
	private:

		bool _direction;
		std::vector<Cell> _caneat;

      public:

      /**
       * @brief Constructeur, crée un objet Spawn de coordonnées x,y
       * @param unsigned int x
       * @param unsigned int y
       * @param bool haut(true)/bas(false)
       */
            Spawn(unsigned int x, unsigned int y, bool direction);

      /**
       * @brief Destructeur d'un objet cavalier
       */
            ~Spawn();

      /**
       * @brief procédure virtuelle permettant de mettre à jour l'attribut movements en fonction des déplacements possibles du Pion
       */
            virtual void movement();
	 /**
       * @brief Getter de l'attribut _direction
       * @return attribut _caneat;
       */
		std::vector< Cell> getcaneat();

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
       * @brief procédure virtuelle permettant de mettre à jour l'attribut movements en fonction des déplacements possibles de la Tour
       */
            virtual void movement();
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
       * @brief procédure virtuelle permettant de mettre à jour l'attribut movements en fonction des déplacements possibles du Cavalier
       */
            virtual void movement();
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
       * @brief procédure virtuelle permettant de mettre à jour l'attribut movements en fonction des déplacements possibles du Fou
       */
            virtual void movement();
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
       * @brief procédure virtuelle permettant de mettre à jour l'attribut movements en fonction des déplacements possibles de la Dame
       */
            virtual void movement();
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
       * @brief procédure virtuelle permettant de mettre à jour l'attribut movements en fonction des déplacements possibles du Roi 
       */
            virtual void movement();
};

#endif // __Piece_HPP__

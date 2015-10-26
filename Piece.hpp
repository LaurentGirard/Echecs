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

		Cell square;				// attribut : case sur laquelle est la pièce
		std::string color;				// attribut : couleur de la pièce
		bool alive;					// attribut : état de la pièce ( 0 = pièce détruite ; 1 = pièce en vie )

	public:

      /**
       * @brief Constructeur, crée une pièce
       */
		Piece(std::string color);

      /**
       * @brief Destructeur de Piece
       */
		~Piece();

	/**
       * @brief de Getter l'attribut _square
       * @return attribut _square
       */
		Cell getSquare();

      /**
       * @brief Setter de l'attribut _square
       * @param newCell est la nouvelle case sur laquelle est la pièce
       */
		void setSquare(Cell newCell);

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
		virtual void move(Cell const dest) = 0;

	/**
       * @brief procédure virtuelle permettant de savoir si la destination est possible ou non
       * @param Cell dest
       */
		virtual bool destination(cell const dest) =0;

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

		bool _moved;				// attribut : permet de savoir si le roi à bouger ou non pendant la partie

	public:

    	/**
       * @brief Constructeur, crée un objet King d'une couleur mise en paramètre
       * @param string color
       */
		King(std::string color);

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
		virtual void move(Cell const dest);

	/**
       * @brief procédure virtuelle permettant de savoir si la destination est possible ou non
       * @param Cell dest
       */
		virtual bool destination(cell const dest);

};

/**
* @class Cavalier 
* 
* @brief Classe King héritant de Piece
*
*/
class Cavalier : public Piece
{
	public:

    	/**
       * @brief Constructeur, crée un objet cavalier d'une couleur mise en paramètre et de la position 1 ou 2
       * @param string color, int num
       */
		Cavalier(std::string color, int num);

	/**
       * @brief Destructeur d'un objet cavalier
       */
		~Cavalier();

	/**
       * @brief procédure virtuelle permettant le déplacement du Roi vers la case dest
       * @param Cell dest
       */
		virtual void move(Cell const dest);

	/**
       * @brief procédure virtuelle permettant de savoir si la destination est possible ou non
       * @param Cell dest
       */
		virtual bool destination(cell const dest);

};

#endif // __Piece_HPP__

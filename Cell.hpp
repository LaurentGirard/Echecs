/**
 * @file Cell.hpp
 * @author P. Sullivan, G.Laurent
 * @since 25/12/2015
 * @brief Définition d'une classe de Cell
 *
**/

#ifndef __Cell_HPP__
#define __Cell_HPP__

/**
* @class Cell 
* 
* @brief Classe permettant de représenter une case du jeu d'echec 
*
*/
class Cell
{
	private:

		unsigned int _x;				// attribut : Coordonnée X d'une case
		unsigned int _y;				// attribut : Coordonnée Y d'une case

	public:

        /**
       * @brief Constructeur par défaut, crée un objet Cell
       */
			Cell();

		/**
       * @brief Constructeur, crée un objet Cell initialisant les coordonnées
       * @param unsigned int x
       * @param unsigned int y
       */
			Cell(unsigned int x, unsigned int y);

		/**
       * @brief Destructeur d'un objet Cell
       */
			~Cell();

		/**
       * @brief Getter de l'attribut _x
       * @return attribut _x
       */
			unsigned int getX();

      /**
       * @brief Setter de l'attribut _x
       * @param unsigned int newX
       */
			void setX(unsigned int newX);

		/**
       * @brief Getter de l'attribut _y
       * @return attribut _y
       */
			unsigned int getY();

		/**
       * @brief Setter de l'attribut _y
       * @param unsigned int newY
       */	
			void setY(unsigned int newY);
};

#endif // __Cell_HPP__

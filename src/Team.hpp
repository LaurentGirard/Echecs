/**
 * @file Team.hpp
 * @author P. Sullivan, G.Laurent
 * @since 25/12/2015
 * @brief Définition d'une classe Team
 *
**/

#ifndef __Team_HPP__
#define __Team_HPP__

#include "Factory.hpp"

/**
* @class Cell 
* 
* @brief Classe permettant de représenter une Team
*
*/

class Team
{
	public:

       /**
       * @brief Constructeur de Factory
       */
       Team();

       /**
       * @brief Destructeur de Factory
       */
       ~Team();

       /**
       * @brief Permet de retourner une liste de 16 Pièce* qui compose une équipe Normal
       * @param bool color, false signifie que l'équipe est white
       * @return une liste de Piece*
       */
       std::vector<Piece*> buildTeamNormal(bool color);

};

#endif // __Team_HPP__

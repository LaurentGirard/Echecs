/**
 * @file Player.hpp
 * @author P. Sullivan, G.Laurent
 * @since 25/12/2015
 * @brief Définition de la classe Player
 *
**/

#ifndef __Player_HPP__
#define __Player_HPP__

class Player
{
	private:

		std::string _name;				// Attribut : nom du joueur
		State *_state;					// Attribut : état courant du joueur dans la partie
		State *_gameState;				// Attribut : état en jeu
		// State _checkState;				// Attribut : état d'échec
		// State _mateState;				// Attribut : état d'échec et mat
		// State _nullState;				// Attribut : état de jeu nul
		// State _endState;				// Attribut : état de fin de jeu

	public:

	/**
   	* @brief Destructeur de Player
   	* @param name, nom du joueur
  	 */
		Player(std::string name);

	/**
   	* @brief Destructeur de Player
  	 */
		~Player();

	/**
	* @brief Getter de l'attribut _name
	* @return attribut _name
	*/
		std::string getName();

	/**
	* @brief Setter de l'attribut _name
	* @param newName, nouveau nom
	*/
		void setName(std::string newName);
};

#endif // __Player_HPP__
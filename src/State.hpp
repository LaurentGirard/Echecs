/**
 * @file State.hpp
 * @author P. Sullivan, G.Laurent
 * @since 25/12/2015
 * @brief Définition de la classe abstraite State et de ses classes filles (GameState, CheckState, MateState, NullState et EndState)
 *
**/

#ifndef __State_HPP__
#define __State_HPP__

class Player;		// Permet d'utiliser les méthodes de Player -> dépendance circulaire

class State
{
	protected:

		Player * player;				// Attribut : Player sur lequel l'état courant sera modifié à l'aide des transitions

	public:

	/**
   * @brief Constructeur, crée un Etat avec un Joueur en paramètre
   * @param p
   */
		State(Player *p);

	/**
   * @brief Destructeur de l'objet State
   */
		~State();

	/**
   * @brief procédure virtuelle permettant de la transition de l'état CheckState à l'état GameState
   */
		virtual void inGame() = 0;

	/**
   * @brief procédure virtuelle permettant de la transition de l'état GameState à l'état CheckState
   */
		virtual void check() = 0;

	/**
   * @brief procédure virtuelle permettant de la transition de l'état GameState à l'état MateState
   */
		virtual void checkMate() = 0;

	/**
   * @brief procédure virtuelle permettant de la transition de l'état GameState à l'état NullState
   */
		virtual void gameNull() = 0;

	/**
   * @brief procédure virtuelle permettant de la transition de l'état MateState ou l'état NullState à l'état EndState
   */
		virtual void gameEnd() = 0;

	/**
   * @brief procédure virtuelle permettant d'afficher l'état courant
   */
		virtual void print() = 0;

	/**
   * @brief procédure virtuelle permettant de savoir s'il se trouve en position d'echec
   */
		virtual bool ischeck() = 0;
	/**
   * @brief procédure virtuelle permettant de savoir s'il se trouve en position d'echec et mate
   */
		virtual bool isCheckMate() = 0;
	/**
   * @brief procédure virtuelle permettant de savoir s'il se trouve en position null
   */
		virtual bool isnulle() = 0;
};

class GameState : public State
{
	public:

	/**
   * @brief Constructeur, crée un EtatJeu à l'aide du constructeur de State avec un Joueur en paramètre
   * @param p
   */
		GameState(Player* p);

	/**
   * @brief Destructeur de l'objet GameState
   */
		~GameState();

	/**
   * @brief Définition de la procédure virtuelle, pas d'effet dans cet Etat là
   */
		void inGame();

	/**
   * @brief Définition de la procédure virtuelle, transition vers l'état CheckState
   */
		void check();

	/**
   * @brief Définition de la procédure virtuelle, transition vers l'état MateState
   */
		void checkMate();

	/**
   * @brief Définition de la procédure virtuelle, transition vers l'état NullState
   */
		void gameNull();

	/**
   * @brief Définition de la procédure virtuelle, pas d'effet dans cet Etat là
   */
		void gameEnd();

	/**
   * @brief Définition de la procédure virtuelle, affiche l'état GameState
   */
		void print();
	/**
	* @brief procédure virtuelle permettant de savoir s'il se trouve en position d'echec
	*/
		bool ischeck();
	/**
	* @brief procédure virtuelle permettant de savoir s'il se trouve en position d'echec et mate
	*/
		bool isCheckMate();

	/**
	* @brief procédure virtuelle permettant de savoir s'il se trouve en position nulle
	*/
		bool isnulle();
};

class CheckState : public State
{
	public:

	/**
   * @brief Constructeur, crée un EtatEchec à l'aide du constructeur de State avec un Joueur en paramètre
   * @param p
   */
		CheckState(Player* p);

	/**
   * @brief Destructeur de l'objet CheckState
   */
		~CheckState();

	/**
   * @brief Définition de la procédure virtuelle, transition vers l'état GameState
   */
		void inGame();

	/**
   * @brief Définition de la procédure virtuelle, pas d'effet dans cet Etat là
   */
		void check();

	/**
   * @brief Définition de la procédure virtuelle, pas d'effet dans cet Etat là
   */
		void checkMate();

	/**
   * @brief Définition de la procédure virtuelle, pas d'effet dans cet Etat là
   */
		void gameNull();

	/**
   * @brief Définition de la procédure virtuelle, pas d'effet dans cet Etat là
   */
		void gameEnd();

	/**
   * @brief Définition de la procédure virtuelle, affiche l'état CheckState
   */
		void print();
	/**
	* @brief procédure virtuelle permettant de savoir s'il se trouve en position d'echec
	*/
		bool ischeck();
	/**
	* @brief procédure virtuelle permettant de savoir s'il se trouve en position d'echec et mat
	*/
		bool isCheckMate();
	/**
	* @brief procédure virtuelle permettant de savoir s'il se trouve en position nulle
	*/
		bool isnulle();
};

class MateState : public State
{
	public:

	/**
   * @brief Constructeur, crée un EtatMate à l'aide du constructeur de State avec un Joueur en paramètre
   * @param p
       */
		MateState(Player* p);

	/**
   * @brief Destructeur de l'objet MateState
   */
		~MateState();

	/**
   * @brief Définition de la procédure virtuelle, pas d'effet dans cet Etat là
   */
		void inGame();

	/**
   * @brief Définition de la procédure virtuelle, pas d'effet dans cet Etat là
   */
		void check();

	/**
   * @brief Définition de la procédure virtuelle, pas d'effet dans cet Etat là
   */
		void checkMate();

	/**
   * @brief Définition de la procédure virtuelle, pas d'effet dans cet Etat là
   */
		void gameNull();

	/**
   * @brief Définition de la procédure virtuelle, transition vers l'état EndGame
   */
		void gameEnd();

	/**
   * @brief Définition de la procédure virtuelle, affiche l'état MateState
   */
		void print();
	/**
	* @brief procédure virtuelle permettant de savoir s'il se trouve en position d'echec
	*/
		bool isCheckMate();
	/**
	* @brief procédure virtuelle permettant de savoir s'il se trouve en position d'echec et mate
	*/
		bool ischeck();
	/**
	* @brief procédure virtuelle permettant de savoir s'il se trouve en position nulle
	*/
		bool isnulle();
};

class NullState : public State
{
	public:

	/**
   * @brief Constructeur, crée un EtatNull à l'aide du constructeur de State avec un Joueur en paramètre
   * @param p
   */
		NullState(Player* p);

	/**
   * @brief Destructeur de l'objet NullState
   */
		~NullState();

	/**
   * @brief Définition de la procédure virtuelle, pas d'effet dans cet Etat là
   */
		void inGame();

	/**
   * @brief Définition de la procédure virtuelle, pas d'effet dans cet Etat là
   */
		void check();

	/**
   * @brief Définition de la procédure virtuelle, pas d'effet dans cet Etat là
   */
		void checkMate();

	/**
   * @brief Définition de la procédure virtuelle, pas d'effet dans cet Etat là
   */
		void gameNull();

	/**
   * @brief Définition de la procédure virtuelle, transition vers l'état EndGame
   */
		void gameEnd();

	/**
   * @brief Définition de la procédure virtuelle, affiche l'état NullState
   */
		void print();
	/**
	* @brief procédure virtuelle permettant de savoir s'il se trouve en position d'echec
	*/
		bool ischeck();
	/**
	* @brief procédure virtuelle permettant de savoir s'il se trouve en position d'echec et mate
	*/
		bool isCheckMate();
	/**
	* @brief procédure virtuelle permettant de savoir s'il se trouve en position nulle
	*/
		bool isnulle();
};

class EndState : public State
{
	public:

	/**
   * @brief Constructeur, crée un EtatFin à l'aide du constructeur de State avec un Joueur en paramètre
   * @param p
   */
		EndState(Player* p);

	/**
   * @brief Destructeur de l'objet EndState
   */
		~EndState();

	/**
   * @brief Définition de la procédure virtuelle, pas d'effet dans cet Etat là
   */
		void inGame();

	/**
   * @brief Définition de la procédure virtuelle, pas d'effet dans cet Etat là
   */
		void check();

	/**
   * @brief Définition de la procédure virtuelle, pas d'effet dans cet Etat là
   */
		void checkMate();

	/**
   * @brief Définition de la procédure virtuelle, pas d'effet dans cet Etat là
   */
		void gameNull();

	/**
   * @brief Définition de la procédure virtuelle, pas d'effet dans cet Etat là
   */
		void gameEnd();

	/**
   * @brief Définition de la procédure virtuelle, affiche l'état EndState
   */
		void print();
	/**
	* @brief procédure virtuelle permettant de savoir s'il se trouve en position d'echec
	*/
		bool ischeck();
	/**
	* @brief procédure virtuelle permettant de savoir s'il se trouve en position d'echec et mate
	*/
		bool isCheckMate();

	/**
	* @brief procédure virtuelle permettant de savoir s'il se trouve en position nulle
	*/
		bool isnulle();


};


#endif // __State_HPP__

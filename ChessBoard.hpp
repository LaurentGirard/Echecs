/**
 * @file ChessBoard.hpp
 * @author P. Sullivan, G.Laurent
 * @since 25/12/2015
 * @brief Définition de la classe ChessBoard
 *
**/

#ifndef __CHESSBOARD_HPP__
#define __CHESSBOARD_HPP__

 class ChessBoard
 {
 	private:

 		Piece chessboard[8][8];
 		Player playerA;
 		Player playerB;

 	public:

      	/**
       * @brief Constructeur, crée un plateau avec deux joueurs, initialisant la position des pièces pour chaque joueur
       */
 		ChessBoard();

 		/**
 		* @brief Destructeur de ChessBoard
 		*/
 		~ChessBoard();
 };

 #endif // __CHESSBOARD_HPP__
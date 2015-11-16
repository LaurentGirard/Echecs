/**
* @file Chess.cpp
* @author P. Sullivan, G.Laurent
* @since 25/12/2015
* @brief implémentation des méthodes de la classe Chess
*
**/

#include "Chess.hpp"

//------------------------------------------------------------------------------------------------------
Chess::Chess(std::string nameP1, std::string nameP2)
{
	p1 = new Player(nameP1,"White");
	p2 = new Player(nameP2,"Black");
	initBoard();
}

//------------------------------------------------------------------------------------------------------
Chess::~Chess() {}

//------------------------------------------------------------------------------------------------------
void Chess::initBoard()
{
	unsigned int i, j;

	for(i = 0; i < 8 ; ++i)
	{
		for(j = 0 ; j < 8 ; ++j)
			_board[i][j] = new Piece(i,j);
	}
	
	for(i = 0 ; i < 8 ; ++i)
	{
		_board[i][1] = p1->getPieces()[i];			// Pions Blancs
		_board[i][0] = p1->getPieces()[i+8];		// Autre pièces Blanches

		_board[i][6] = p2->getPieces()[i];			// Pions Noirs
		_board[i][7] = p2->getPieces()[i+8];		// Autres pièces Noires
	}
}

//------------------------------------------------------------------------------------------------------
Piece* Chess::selectDest(Player* player, Piece* piece, unsigned int x, unsigned int y)
{
	unsigned int i, j, k;
	Piece* selectedD = _board[x][y];

	// Si la case selectionnée correspond à une pièce que le joueur player possède
	for(i = 0 ; i < 16 ; ++i)
	{
		if( _board[x][y]->getSquare() == player->getPieces()[i]->getSquare() )
			return NULL;
	}

	// Si la case sélectionnée correspond à un déplacement théorique possible de la pièce
	for(j = 0 ; j < piece->getMovements().size() ; ++j)
	{
		for(k = 0 ; k < piece->getMovements()[j].size() ; ++k)
		{
			if(*(piece->getMovements()[j][k]) == *(selectedD->getSquare()) )
				return selectedD;
		}
	}

	return NULL;
}

//------------------------------------------------------------------------------------------------------
bool Chess::noCollision(Piece* selectedP, Piece* selectedD)
{
	bool noCollision = true;
	bool found = false;
	unsigned int i = 0;
	unsigned int j = 0;
	unsigned int k = 0;
	unsigned int x, y;

	// Cherche l'indice i dans lequel se trouve les étapes intermédiaires du déplacement à effectuer
	while( !found && (i < selectedP->getMovements().size()) )
	{
		while ( !found && (j < selectedP->getMovements()[i].size()) )
		{
			found = ( (*selectedD->getSquare()) == (*selectedP->getMovements()[i][j]) );
			++j;
		}
		j=0;
		if(!found)
			++i;
	}
	// Tant qu'il n'y a pas de collision et que le parcours du vecteur de mouvement n'arrive pas sur la destination sélectionnée
	do
	{
		x = selectedP->getMovements()[i][k]->getX();		
		y = selectedP->getMovements()[i][k]->getY();

		noCollision = (_board[x][y]->getLabel() == " "); // Si le label de la case (x,y) est " ", alors il n'y a pas de pièce réelle sur la case [i][k]
		++k;
	}while( noCollision && 
		  ( (selectedD->getSquare()->getX() != x) || (selectedD->getSquare()->getY() != y )) );
	
	return noCollision;
}
//------------------------------------------------------------------------------------------------------
void Chess::movePiece(Piece* selectedP, Piece* selectedD)
{
	// Récupération des coordonnées de la destination
	unsigned int xDest = selectedD->getSquare()->getX();
	unsigned int yDest = selectedD->getSquare()->getY();

	// Récupération des coordonnées de la Pièce
	unsigned int xPiece = selectedP->getSquare()->getX();
	unsigned int yPiece = selectedP->getSquare()->getY();

	// Check si la destination est occupée par une pièce adverse (dest est soit une piece "vide" soit une pièce adverse)
	bool isAdvers = (selectedD->getLabel() != " ");

	// Si la destination est occupée par une pièce adverse
	if(isAdvers)
		selectedD->setAlive(false);

	_board[xDest][yDest] = selectedP;							// La pièce est déplacée sur le plateau
	_board[xPiece][yPiece] = new Piece(xPiece,yPiece);			// L'ancienne position de la pièce est maintenant une pièce "vide"
	selectedP->setSquare(selectedD->getSquare());				// Mise à jour des coordonnées de la pièce qui vient d'être déplacée
	selectedP->movement();										// Mise à jour des déplacements possibles de la pièce depuis sa nouvelle position
}

//------------------------------------------------------------------------------------------------------
void Chess::gameRound(Player* playerIG, Player* advers)
{
	Piece* selectedP;
	Piece* selectedD;
	unsigned int x, y, x2, y2;

	printBoard();

	std::cout << "Coordonnées de la pièce que vous voulez selectionner : " << std::endl;
	std::cout << "x: ";
	x = getChoiceInt();
	std::cout << "y: ";
	y = getChoiceInt();

	selectedP = playerIG->selectPiece(x,y);		// Selection de la pièce du joueur

	while(selectedP == NULL)
	{
		std::cout << "Aucune pièce en votre possession ne se situe sur la case : (" << x << "," << y << ")" << std::endl;

		std::cout << "Entrer des nouvelles coordonnées : " << std::endl;
		std::cout << "x: ";
		x = getChoiceInt();
		std::cout << "y: ";
		y = getChoiceInt();

		selectedP = playerIG->selectPiece(x,y);
	}

	std::cout << "Vous avez selectionné la pièce :" << std::endl;
	selectedP->printPiece();

	std::cout << "Coordonnées de la case sur laquelle vous voulez déplacer la pièce : " << std::endl;
	std::cout << "x: ";
	x2 = getChoiceInt();
	std::cout << "y: ";
	y2 = getChoiceInt();

	// Selection valide de la destination sur le plateau ( selectedD sera soit une pièce adverse, soit une pièce "vide" )
	selectedD = selectDest(playerIG, selectedP, x2, y2); 	
	while(selectedD == NULL)
	{
		std::cout << "Entrée de nouvelles coordonnées pour la destination de la pièce : " << std::endl;
		std::cout << "x: ";
		x2 = getChoiceInt();
		std::cout << "y: ";
		y2 = getChoiceInt();

		selectedD = selectDest(playerIG, selectedP, x2, y2);
	}

	// Test s'il y a une collision ou non avec une pièce réelle lors du déplacement de selectedP vers selectedD

	if(noCollision(selectedP, selectedD))
	{
		movePiece(selectedP, selectedD);		// déplacement de la pièce selectionnée vers selectedD
	}
	else
	{
		std::cout << "collision !!" << std::endl;
	}

}

//------------------------------------------------------------------------------------------------------
unsigned int Chess::getChoiceInt()
{
	unsigned int choice = 0;

	do
	{
		std::cin >> choice;
	}while(choice > 7);

	return choice;
}

//------------------------------------------------------------------------------------------------------
void Chess::printBoard()
{
	unsigned int i, j, k;

	for(i = 0; i < 8 ; ++i)
	{
		std::cout << 7-i<<"  |";
		for(j = 0 ; j < 8 ; ++j)
			std::cout << _board[j][7-i]->getLabel() << "|";

		std::cout << std::endl;
	}
	
  	std::cout <<"y/x ";

	for(k = 0; k < 8 ; ++k)
		std::cout << k <<" ";

	std::cout << std::endl;
}

//------------------------------------------------------------------------------------------------------
bool Chess::testechec(Player* playerIG, Player* adver)
{
	Piece* kingIG;
	kingIG = playerIG->getking();
	bool res = testechec(kingIG, adver);
	return res;
}

//------------------------------------------------------------------------------------------------------
bool Chess::testechec(Piece* selectedP, Player* adver)
{
	bool positionEchec = false;
	Piece* selectedD;
	// int j;
	int i = 0;
	while( (positionEchec == false) && (i < 16) )
	{
		selectedD = adver->getPieces()[i];
		if(!(selectedD->getLabel()=="S"))
		{	
			if (!(selectDest(adver,selectedD, selectedP->getSquare()->getX(), selectedP->getSquare()->getY())==NULL))
			{
				if(!(noCollision(selectedD, selectedP)))
				{
					positionEchec = true;
				}
			}
		}else
		{
			if ((selectedD->getMovements()[1][0]->getX()==selectedP->getSquare()->getX())&&(selectedD->getMovements()[1][0]->getY()==selectedP->getSquare()->getY()))
			{
				positionEchec = true;
			}
			if ((selectedD->getMovements()[1][0]->getX()==selectedP->getSquare()->getX())&&(selectedD->getMovements()[1][0]->getY()==selectedP->getSquare()->getY()))
			{
				positionEchec = true;
			}		
		}
		i++;
		std::cout<<"i ::: "<<i<<std::endl;		
	}
	return positionEchec;
}

//------------------------------------------------------------------------------------------------------
bool Chess::testechecmat(Player* playerIG, Player* adver)
{
	int positionEchecmat = 0;
	Piece* king_deplacement_virtuel=new Piece(0,0);
	Piece* kingIG;
	kingIG = playerIG->getking();
	int i,x,y,s;
	s=0;
	for(i=0; i<kingIG->getMovements().size(); ++i)
	{
		std::cout<<"cc "<< i << std::endl;
		x=kingIG->getMovements()[i][0]->getX();
		std::cout<<"cx "<< x << std::endl;
		y=kingIG->getMovements()[i][0]->getY();
		std::cout<<"cy "<< y << std::endl;
		king_deplacement_virtuel->setSquare(new Cell(x,y));
		if(playerIG->selectPiece(x,y)==NULL)
		{	
			s++;
			std::cout<<"test echec 1"<<std::endl;
			if(testechec(king_deplacement_virtuel,adver))
			{
				positionEchecmat++;
			}
			std::cout<<"test echec 2"<<std::endl;
		}
	}
	bool deplacementvirtuel = false;
	Piece* selectedD;
	Piece* piecejoueur;
	Piece* piecevirtuel;
	i=0;
	int t;
	int w,z;
	if(positionEchecmat==kingIG->getMovements().size()-1)//roi ne peut pas bouger
	{
		while((i<16)&&(!déplacementvirtuel))
		{
			selectedD = adver->getPieces()[i];//on prend toute les pieces du joueur adverse 
			if (!(selectDest(adver,selectedD, kingIG->getSquare()->getX(), kingIG->getSquare()->getY())==NULL))// si la piece peut manger le roi
			{
				for(t=0; t<16; ++t)
				{
					piecejoueur= playerIG->getPieces()[i];// on prend toute les pieces du joueur 
					if(!(selectDest(playerIG,piecejoueur, selectedD->getSquare()->getX(), selectedD->getSquare()->getY())==NULL)) // on regarde s'il ne peut pas manger la piece qui le met en echec
					{
						if(!(noCollision(piecejoueur, selectedD))
						{
							deplacementvirtuel=true;
						}
					}else // si il ne peut pas manger la piece qui le met en echec alors on regarde si on a pas une piece qui ne peux pas couper le chemin de cette piece 
					{
						for(w=0; w< selectedD->getMovements().size();++w;)
						{
							for(z; z<selectedD->getMovements()[w].size(); ++z)
							{
								if(!(selectDest(playerIG,piecejoueur, selectedD->getMovements()[w][z]->getX(), selectedD->getMovements()[w][z])->getY())==NULL)) // test pour chaque case du déplacements virtuels de la piece "tueuse" si on peux y aller
								{
									if(!(noCollision(piecejoueur, selectedD))
									{
										deplacementvirtuel=true;
									}
								}
							}
						}				
					}
				}
			}
			++i;
		}
		t=0;// compteur de piece qui peut manger le roi si un déplacement virtuel a été fait;
		while(i<16)
		{
			selectedD = adver->getPieces()[i];
			if(!(selectDest(adver,selectedD,  kingIG->getSquare()->getX(), kingIG->getSquare()->getY())==NULL)) // test pour chaque case du déplacements virtuels de la piece "tueuse" si on peux y aller
			{
				if(!(noCollision(piecejoueur, selectedD))
				{
					t++;
				}
			}
			++i;
		}
	}
	bool res = false;
	if ( (deplacementvirtuel&&i>0)||!deplacementvirtuel)
	{
		res=true;
	}
	/*if (res){
		playerIG->checkMate();
	}*/
	std::cout<<"position echecmat : "<< positionEchecmat<<std::endl;
	std::cout<<"déplacement posible : "<< s<<std::endl;
	return res;
}

//------------------------------------------------------------------------------------------------------
void Chess::startGame()
{
	unsigned int i, j;

	Piece* p = _board[2][7];			// Coordonnées de la pièce sur laquelle tu veux afficher les déplacements possible

	std::cout << p->getLabel() << "(" << p->getSquare()->getX() << "," << p->getSquare()->getY() << ")" << std::endl;
	std::cout<<p->getMovements().size()<<std::endl;
	for(i = 0 ; i < p->getMovements().size() ; ++i)
	{
		for(j = 0 ; j < p->getMovements()[i].size() ; ++j)
		{
			std::cout << "(" << p->getMovements()[i][j]->getX() << "," << p->getMovements()[i][j]->getY() << ")" << std::endl;
		}
		std::cout << std::endl;
	}

	//Test du jeu pour 2 tours de jeu chacun
	int m;
		std::cout<<" joueur 2 a vous de jouer !! "<<std::endl;
		gameRound(p2, p1);
		printBoard();
		for(m = 0 ; m < p->getMovements().size() ; ++m)
		{
			for(j = 0 ; j < p->getMovements()[m].size() ; ++j)
			{
				std::cout << "(" << p->getMovements()[m][j]->getX() << "," << p->getMovements()[m][j]->getY() << ")" << std::endl;
			}
			std::cout << std::endl;
		}
	for(i = 0 ; i < 8 ; ++i)
	{
		std::cout<<" testechecmat p2 p1 : "<<testechecmat(p2,p1)<<std::endl;
		std::cout<<" joueur 1 a vous de jouer !! "<<std::endl;
		gameRound(p1, p2);
		printBoard();
		for(m = 0 ; m < p->getMovements().size() ; ++m)
		{
			for(j = 0 ; j < p->getMovements()[m].size() ; ++j)
			{
				std::cout << "(" << p->getMovements()[m][j]->getX() << "," << p->getMovements()[m][j]->getY() << ")" << std::endl;
			}
			std::cout << std::endl;
		}
		std::cout<<" testechecmat p1 p2 : "<<testechecmat(p1,p2)<<std::endl;
		
	}

	/*std::cout << _board[3][4]->getLabel() << "(" << _board[3][4]->getSquare()->getX() << "," << _board[3][4]->getSquare()->getY() << ")" << std::endl;
	for(i = 0 ; i < _board[3][4]->getMovements().size() ; ++i)
	{
		for(j = 0 ; j < _board[3][4]->getMovements()[i].size() ; ++j)
		{
			std::cout << "(" << _board[3][4]->getMovements()[i][j]->getX() << "," << _board[3][4]->getMovements()[i][j]->getY() << ")" << std::endl;
		}
		std::cout << std::endl;
	}*/
	p1->printState();
	//p2->printPieces();

}

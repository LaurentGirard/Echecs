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
	unsigned int i, j, k,lim=3;
	Piece* selectedD = _board[x][y];
	bool manger = false;
	Player* adver = p1;

	if(piece->isAlive()){
		// Si la case selectionnée correspond à une pièce que le joueur player possède
		for(i = 0 ; i < 16 ; ++i)
		{
			if( _board[x][y]->getSquare() == player->getPieces()[i]->getSquare() )
				return NULL;
		}
		// Si la case selectionnée correspond à une pièce que le joueur adver possède
		
		if(player->getName() == p1->getName())
			adver=p2;
		
		for(i = 0; i < 16 ; ++i)
		{
			if( _board[x][y]->getSquare() == adver->getPieces()[i]->getSquare() )
				manger=true;
		}
		// Si la case sélectionnée correspond à un déplacement théorique possible de la pièce
		if(piece->getLabel()!="S")
		{
			for(j = 0 ; j < piece->getMovements().size() ; ++j)
			{
				for(k = 0 ; k < piece->getMovements()[j].size() ; ++k)
				{
					if(*(piece->getMovements()[j][k]) == *(selectedD->getSquare()) )
						return selectedD;
				}
			}
		}else
		{
			// si la destination n'est pas une piece du joueur adverse
			if(!manger)
			{		
				for(k = 0 ; k < piece->getMovements()[0].size() ; ++k)
				{
					if(*(piece->getMovements()[0][k]) == *(selectedD->getSquare()) )
						return selectedD;
				}
			}else 
			{
				k=1;
				if(piece->getSquare()->getX()==7||piece->getSquare()->getX()==0)
					lim--;
				while(k<piece->getMovements().size()&&k<lim)
				{
					if(*(piece->getMovements()[k][0]) == *(selectedD->getSquare()) )
						return selectedD;
					k++;
				}
			}
	
		}
	}
	return NULL;
}

//------------------------------------------------------------------------------------------------------
bool Chess::noCollision(Piece* selectedP, Piece* selectedD, Piece* pieceeaeviter = NULL, Piece* pieceD = NULL)
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
			j++;
		}
		j = 0;
		if(!found)
			++i;
	}
	// Tant qu'il n'y a pas de collision et que le parcours du vecteur de mouvement n'arrive pas sur la destination sélectionnée
	x = selectedP->getMovements()[i][k]->getX();		
	y = selectedP->getMovements()[i][k]->getY();
	while( noCollision && 
		  ( (selectedD->getSquare()->getX() != x) || (selectedD->getSquare()->getY() != y )) )
	{
			if(pieceeaeviter == NULL)
			{
				noCollision = (_board[x][y]->getLabel() == " "); // Si le label de la case (x,y) est " ", alors il n'y a pas de pièce réelle sur la case [i][k]
			}else
			{
				if( (( pieceeaeviter->getSquare()->getX() != x ) || ( pieceeaeviter->getSquare()->getY() != y ))  )
					noCollision = (_board[x][y]->getLabel() == " "); // Si le label de la case (x,y) est " ", alors il n'y a pas de pièce réelle sur la case [i][k]				
				if( pieceD!= NULL &&pieceD->getSquare()->getX()==x && pieceD->getSquare()->getY()==y )
					noCollision = false;
			}
		++k;
		x = selectedP->getMovements()[i][k]->getX();		
		y = selectedP->getMovements()[i][k]->getY();
	}
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
// permet de retourner une liste de piece que peut manger la piece selecteP
std::vector<Piece*> Chess::listPieces(Piece* selectedP, Player* advers)
{
	std::vector<Piece*> list;
	Piece* piecetueuse = NULL;

	for(int i = 0; i < 16; ++i)
	{
		piecetueuse = advers->getPieces()[i];//on prend toute les pieces du joueur adverse
		if (!(selectDest(advers,piecetueuse, selectedP->getSquare()->getX(), selectedP->getSquare()->getY())==NULL))// si la piecetueuse peut aller théoriquement manger la piece selectedp
		{
			if(noCollision(piecetueuse, selectedP))//si la piecetueuse peut aller manger selectedP 
				list.push_back(piecetueuse);
		}
	}
	return list;
}

//------------------------------------------------------------------------------------------------------
bool Chess::listCanEatKing(std::vector<Piece*> list, Player* advers, Player* playerIG, Piece* selectedP, Piece* selectedD)
{
	bool res = false;
	Piece* king = playerIG->getPieces()[12];
	Piece* piecetueuse = NULL;
	for(int i = 0; i < list.size() ; ++i)
	{
		piecetueuse = list[i];//on prend toute les pieces du joueur adverse

		if (!(selectDest(advers,piecetueuse, king->getSquare()->getX(), king->getSquare()->getY())==NULL))// si la piecetueuse peut aller théoriquement manger la piece selectedp
		{
			if(selectedD->getSquare()==piecetueuse->getSquare())
				return false;
			if(!(selectDest(advers,piecetueuse, selectedD->getSquare()->getX(), selectedD->getSquare()->getY())==NULL))
			{
				if(selectedP==king)
				{
					if(noCollision(piecetueuse, selectedD,selectedP))//si la piecetueuse peut aller manger le roi en sautant la piece selectedP
						res=true;
				}
				else
				{
					if(noCollision(piecetueuse, king, selectedP, selectedD))//si la piecetueuse peut aller manger le roi en sautant la piece selectedP
						res = true;
				}
			}else
			{
				if(!(selectDest(advers,piecetueuse, selectedP->getSquare()->getX(), selectedP->getSquare()->getY())==NULL))
				{
					if(noCollision(piecetueuse, king, selectedP, selectedD))
					{
						res = true;
					}
				}
			}
		}
	}
	/*if(res)
	{
		std::cout<<"Vous ne pouvez pas bouger cette piece sinon votre Roi sera encore en position d'échec";
	}*/
	return res;
}
//------------------------------------------------------------------------------------------------------
bool Chess::onTheWay(Player* playerIG, Piece* pieceD, Player* advers){
	Piece* king = playerIG->getPieces()[12];
	Piece* piecetueuse = NULL;
	bool trouve = false;
	int i = 0;
	int ypieceD = pieceD->getSquare()->getY();
	int xpieceD = pieceD->getSquare()->getX();
	int xpiecetueuse;	
	int ypiecetueuse;
	int w = 0;
	int indice = 0;
	int indicebis = 0;
	while((!trouve) && (i < 16) )
	{
		piecetueuse= advers->getPieces()[i];//on prend toute les pieces du joueur adverse
		if (!(selectDest(advers,piecetueuse, king->getSquare()->getX(), king->getSquare()->getY())==NULL))// si la piece peut manger le roi
			trouve = true;
		if(!trouve)
			++i;
	}
	//recherche l'indice dans movements
	i = 0;
	trouve = false;
	if(!(piecetueuse == NULL))
	{
		/********************************************/
		// recherche l'indice du movement de la piece tueuse
		trouve = false;
		i = 0;
		while(i < piecetueuse->getMovements().size() && !trouve)
		{
			w = 0;
			while(w < piecetueuse->getMovements()[i].size() && !trouve)
			{
				if( (piecetueuse->getMovements()[i][w]->getX() == king->getSquare()->getX()) && 
				   (piecetueuse->getMovements()[i][w]->getY() == king->getSquare()->getY()) )
				{
					indice = i;
					indicebis = w;
					trouve = true;
				}
				if(!trouve)
					++w;
			}
			if(!trouve)
				++i;
		}
		trouve = false;
		i = 0;
		//regarde si la destination est la piece tueuse
		if(piecetueuse->getSquare()==pieceD->getSquare())
			trouve=true;

		//regarde si la destination est bien sur le passage de la piece
		for(w = 0 ; w < indicebis ; ++w)
		{
			xpiecetueuse = piecetueuse->getMovements()[indice][w]->getX();
			ypiecetueuse = piecetueuse->getMovements()[indice][w]->getY();
			if ( (xpieceD == xpiecetueuse) && (ypieceD == ypiecetueuse) )
				trouve = true;						
		}
	}
	return trouve;
}
//------------------------------------------------------------------------------------------------------
void Chess::transfoSpawn(Player* playerIG, Piece* selectedP, Piece* selectedD)
{
	int choose;
	bool recherche = false;
	int coordonnee = 0;

	std::cout << "Vous pouvez transformer votre pion en : " << std::endl;
	std::cout << "- Saissisez 0 pour le transformer en Reine." << std::endl;
	std::cout << "- Saissisez 1 pour le transformer en fou." << std::endl;
	std::cout << "- Saissisez 2 pour le transformer en cavalier." << std::endl;
	std::cout << "- Saissisez 3 pour le transformer en tour." << std::endl;

	choose = getChoiceInt();

	while(choose > 3)
	{
		std::cout << "Veuillez saisir un chiffre entre 0 et 4 !" << std::endl;
		choose = getChoiceInt();
	}
	// recheche de la coordonnée de la piece dans ces mains

	while(!recherche && coordonnee < 16)
	{
		if(playerIG->getPieces()[coordonnee]->getSquare() == selectedP->getSquare())
			recherche = true;
		if(!recherche)
			++coordonnee;
	}
	movePiece(selectedP, selectedD);//déplacement de la pièce quand meme

	switch(choose)
	{
		// Spawn devient Queen
		case 0:
		{
			playerIG->getPieces()[coordonnee] = new Queen(selectedD->getSquare()->getX(),selectedD->getSquare()->getY());
			break;
		}
		// Spawn devient Bishop
		case 1:
		{
			playerIG->getPieces()[coordonnee] = new Bishop(selectedD->getSquare()->getX(),selectedD->getSquare()->getY());
			break;
		}
		// Spawn devient Knight
		case 2:
		{
			playerIG->getPieces()[coordonnee] = new Knight(selectedD->getSquare()->getX(),selectedD->getSquare()->getY());
			break;
		}
		// Spawn devient Rook
		case 3:
		{
			playerIG->getPieces()[coordonnee] = new Rook(selectedD->getSquare()->getX(),selectedD->getSquare()->getY());
			break;
		}
	}
	selectedP->movement();// Mise à jour des déplacements possibles de la pièce depuis sa nouvelle position
	_board[selectedD->getSquare()->getX()][selectedD->getSquare()->getY()] = playerIG->getPieces()[coordonnee];	// La pièce est remplacé sur le plateau
}
//------------------------------------------------------------------------------------------------------
// regarde si le petit roque est possible

bool Chess::tryCastling(Player* playerIG, Piece* selectedP, Piece* selectedD)
{
	bool res = false;
	if( playerIG->getPieces()[15]->isAlive() && 
		playerIG->getPieces()[15]->getMovements()[0][0]->getX() == playerIG->getPieces()[15]->getSquare()->getX() &&
		playerIG->getPieces()[15]->getMovements()[0][0]->getY() == playerIG->getPieces()[15]->getSquare()->getY() )
		res = true;
	if(res)
		std::cout << "Coup du Petit Roque !" << std::endl;

	return res;
}

//------------------------------------------------------------------------------------------------------
// regarde si le grand roque est possible
bool Chess::tryGCastling(Player* playerIG, Piece* selectedP, Piece* selectedD)
{
	bool res = false;
	int x, y;

	if( playerIG->getPieces()[8]->isAlive() && 
		playerIG->getPieces()[8]->getMovements()[0][0]->getX() == playerIG->getPieces()[8]->getSquare()->getX() &&
		playerIG->getPieces()[8]->getMovements()[0][0]->getY() == playerIG->getPieces()[8]->getSquare()->getY() )
	{
		x = playerIG->getPieces()[8]->getSquare()->getX() + 1;
		y = playerIG->getPieces()[8]->getSquare()->getY();
		if( ( _board[x][y]->getLabel()) == " ") 
			res = true;
	}
	if(res)
		std::cout << "Coup du Grand Roque !" << std::endl;

	return res;
}

//------------------------------------------------------------------------------------------------------
//procédure permettant d'effectuer le petit roque, on suppose que tryCastling == true

void Chess::castling(Player* playerIG)
{
	int xroi = playerIG->getKing()->getSquare()->getX();
	int yroi = playerIG->getKing()->getSquare()->getY();
	int xtour = playerIG->getPieces()[15]->getSquare()->getX();
	int ytour = playerIG->getPieces()[15]->getSquare()->getY();
	int x1 = playerIG->getKing()->getSquare()->getX()+2;
	int y1 = playerIG->getKing()->getSquare()->getY();
	int x2 = x1-1;
	int y2 = y1;

	_board[x1][y1] = playerIG->getKing();	// Le roi est déplacée sur le plateau
	playerIG->getKing()->setSquare(new Cell(x1,y1));// Mise à jour des coordonnées du roi qui vient d'être déplacée
	playerIG->getKing()->movement();	
	_board[x2][y2] = playerIG->getPieces()[15];// la tour es déplacée
	playerIG->getPieces()[15]->setSquare(new Cell(x2,y2));// Mise à jour des coordonnées de la tour qui vient d'être déplacée
	_board[xroi][yroi] = new Piece(xroi,yroi);			// L'ancienne position de la pièce est maintenant une pièce "vide"
	_board[xtour][ytour] = new Piece(xtour,ytour);			// L'ancienne position de la pièce est maintenant une pièce "vide"



}
//------------------------------------------------------------------------------------------------------
//procédure permettant d'effectuer le grand roque, on suppose que tryGCastling == true
void Chess::gCastling(Player* playerIG)
{
	int xroi = playerIG->getKing()->getSquare()->getX();
	int yroi = playerIG->getKing()->getSquare()->getY();
	int xtour = playerIG->getPieces()[8]->getSquare()->getX();
	int ytour = playerIG->getPieces()[8]->getSquare()->getY();
	int x1 = playerIG->getKing()->getSquare()->getX()-2;
	int y1 = playerIG->getKing()->getSquare()->getY();
	int x2 = x1 + 1;
	int y2 = playerIG->getKing()->getSquare()->getY();

	_board[x1][y1] = playerIG->getKing();	// Le roi est déplacée sur le plateau

	playerIG->getKing()->setSquare(new Cell(x1,y1));// Mise à jour des coordonnées du roi qui vient d'être déplacée
	playerIG->getKing()->movement();	

	_board[x2][y2] = playerIG->getPieces()[8]; // la tour es déplacée

	playerIG->getPieces()[8]->setSquare(new Cell(x2,y2));// Mise à jour des coordonnées de la tour qui vient d'être déplacée
	playerIG->getPieces()[8]->movement();

	_board[xroi][yroi] = new Piece(xroi,yroi);			// L'ancienne position de la pièce est maintenant une pièce "vide"
	_board[xtour][ytour] = new Piece(xtour,ytour);			// L'ancienne position de la pièce est maintenant une pièce "vide"
}

//------------------------------------------------------------------------------------------------------
bool Chess::gameRound(Player* playerIG, Player* advers)
{
	Piece* selectedP;
	Piece* selectedD;
	unsigned int x, y, x2, y2;
	// Selection de la pièce du joueur
	bool choix = false;
	bool arreter = false;
	std::string arret;
	int value_returned;
	int xroipetit;
	int yroipetit;
	bool test1, test2, test3;
	std::cout << " C'est au tour de : " << playerIG->getName() << std::endl;
	std::cout << "---------------------------------------------------------" << std::endl << std::endl;

	while(!choix && !arreter)
	{
		/*
		std::cout << "Souhaitez-vous arreter la partie ? si oui, tapez oui sinon mettez n'importe quoi !" << std::endl;
		std::cin >> arret;
		if( arret == "oui")
			arreter = true;*/

		if(!arreter)
		{
			printBoard();

			std::cout << std::endl << "---------------------------------------------------------" << std::endl;
			std::cout << " Coordonnées de la pièce que vous voulez selectionner : " << std::endl;
			std::cout << "x: ";
			x = getChoiceInt();
			std::cout << "y: ";
			y = getChoiceInt();

			selectedP = playerIG->selectPiece(x,y);
			//demande au joueur de selectionner une piece tant que la piece selectionnée n'est pas une piece a lui 
			while((selectedP == NULL))
			{
				std::cout << "---------------------------------------------------------" << std::endl;
				std::cout << " Aucune pièce en votre possession ne se situe sur la case : (" << x << "," << y << ")" << std::endl;
				std::cout << "---------------------------------------------------------" << std::endl;
				std::cout << " Entrer de nouvelles coordonnées : " << std::endl;
				std::cout << "x: ";
				x = getChoiceInt();
				std::cout << "y: ";
				y = getChoiceInt();

				selectedP = playerIG->selectPiece(x,y);
			}
			std::cout << "---------------------------------------------------------" << std::endl;
			std::cout << " Vous avez selectionné la pièce :" << std::endl;
			selectedP->printPiece();

			std::cout << "---------------------------------------------------------" << std::endl;
			std::cout << " Coordonnées de la case sur laquelle vous voulez déplacer la pièce : " << std::endl;
			std::cout << "x: ";
			x2 = getChoiceInt();
			std::cout << "y: ";
			y2 = getChoiceInt();
			selectedD = selectDest(playerIG, selectedP, x2, y2);

			if(!(selectedD == NULL))
			{
			// Selection valide de la destination sur le plateau ( selectedD sera soit une pièce adverse, soit une pièce "vide" )
				if(!listCanEatKing(listPieces(selectedP, advers), advers, playerIG, selectedP, selectedD))//évite de mettre le joueur en etat d'echec ou en état echec et mat s'il se trouve déja en echec
				{
					if(!(playerIG->ischeck()))
					{
					// Test s'il y a une collision ou non avec une pièce réelle lors du déplacement de selectedP vers selectedD
						if(selectedP->getLabel() == "K")
						{
							// gerer le cas du petit et grand roque
							if(selectedP->getMovements().size() == 7)//signifie indirectement que le roi n'a pas encore bougé
							{
								bool roque = false;
								// si le cas du petit roque est demandé 
								if(selectedP->getSquare()->getX()<6&&selectedD->getSquare()->getX()==(selectedP->getSquare()->getX()+2))
								{
									xroipetit = selectedP->getSquare()->getX();
									yroipetit = selectedP->getSquare()->getY();
									// regarde si aucune pieces se trouve entre le roi et la tour
									test1 = (_board[xroipetit+1][yroipetit]->getLabel()==" ");
									test2 = (_board[xroipetit+2][yroipetit]->getLabel()==" ");
									if(test1 && test2)
										roque = tryCastling(playerIG,selectedP,selectedD);
										if(roque)
											choix = true;
											castling(playerIG);
								}
								else
								{
									//si le cas du grand roque est demandé
									if(selectedP->getSquare()->getX() > 2 && selectedD->getSquare()->getX() == (selectedP->getSquare()->getX()-2))
									{
										int xroipetit = selectedP->getSquare()->getX();
										int yroipetit = selectedP->getSquare()->getY();
										// regarde si aucune pieces se trouve entre le roi et la tour
										test1 = (_board[xroipetit-1][yroipetit]->getLabel()==" ");
										test2 = (_board[xroipetit-2][yroipetit]->getLabel()==" ");
										test3 = (_board[xroipetit-3][yroipetit]->getLabel()==" ");
										if(test1 && test2 && test3)
										{
											roque = tryGCastling(playerIG,selectedP,selectedD);
											if(roque)
												choix = true;
												gCastling(playerIG);
										}
									}
									else
									{
										if(noCollision(selectedP, selectedD))
										{
											choix = true;
											movePiece(selectedP, selectedD);		// déplacement de la pièce selectionnée vers selectedD
										}
									}
								}
							}
							else
							{
								if(noCollision(selectedP, selectedD))
								{
									choix = true;
									movePiece(selectedP, selectedD);		// déplacement de la pièce selectionnée vers selectedD
								}
							}
						}
						else
						{
							if(noCollision(selectedP, selectedD))
							{
								if(!(selectedP->getLabel() == "S"))// si le pion selectionné n'est pas un spawn
								{
										choix=true;
										movePiece(selectedP, selectedD);		// déplacement de la pièce selectionnée vers selectedD
								}
								else
								{
									if( ( playerIG->getColor() == "White" ) || ( playerIG->getColor() == "Blanc") )
									{
										// cas pour transformer le spawn en reine, fou ..... si possible
										if(selectedD->getSquare()->getY() == 7)
										{
											transfoSpawn(playerIG, selectedP, selectedD);
											choix = true;
										}
										else// sinon faire le cas normal
										{
											choix = true;
											movePiece(selectedP, selectedD);		// déplacement de la pièce selectionnée vers selectedD	
										}
									}
									else
									{
										if(selectedD->getSquare()->getY() == 0)
										{
											transfoSpawn(playerIG, selectedP, selectedD);
											choix = true;
										}
										else
										{
											choix = true;
											movePiece(selectedP, selectedD);		// déplacement de la pièce selectionnée vers selectedD
										}
									}
								}
							}
							else
							{
								std::cout << "---------------------------------------------------------" << std::endl;
								std::cout << "Il y a une collision sur le chemin !" << std::endl;
							}
						}
					}else
					{
						selectedD = selectDest(playerIG, selectedP, x2, y2); 
						if(selectedD != NULL)
						{
							if(!(selectedP==playerIG->getKing()))
							{
								if(onTheWay( playerIG, selectedD, advers))//regarde si la destination est sur la passage de l'adverse qui le met en echec
								{
									if(noCollision(selectedP, selectedD))
									{
											if(!listCanEatKing(listPieces(selectedP, advers),advers,playerIG, selectedP, selectedD))//voir si le déplacement de cette piece  n'implique pas encore un echec
											{
												choix=true;
												movePiece(selectedP, selectedD);		// déplacement de la pièce selectionnée vers selectedD
											}
									}
								}
							}
							else
							{
								if(noCollision(selectedP, selectedD))
								{
									choix = true;
									movePiece(selectedP, selectedD);
								}
							}
						}
						// Test s'il y a une collision ou non avec une pièce réelle lors du déplacement de selectedP vers selectedD
						if(choix == false)
						{
							std::cout << "---------------------------------------------------------" << std::endl;
							std::cout << " Votre roi se trouve en position d'échec vous devez le sauver ! " << std::endl;
						}
					}
				}
				else
				{
					std::cout << "---------------------------------------------------------" << std::endl;
					std::cout << " Votre Roi est toujours en position d'Echec !" << std::endl; 
				}

				if(!choix)
				{
					std::cout << "---------------------------------------------------------" << std::endl;
					std::cout << " Veuillez sélectionner de nouveau une pièce" << std::endl;
					std::cout << "---------------------------------------------------------" << std::endl << std::endl;
				}
			}
			else
			{
				std::cout << "---------------------------------------------------------" << std::endl;
				std::cout << " Il est impossible d'aller à cette destination." << std::endl;
				std::cout << "---------------------------------------------------------" << std::endl << std::endl;
			}
		}
	}

	std::cout << "---------------------------------------------------------" << std::endl;
	std::cout << " Fin du tour" << std::endl;
	std::cout << "---------------------------------------------------------" << std::endl;
	// Permet de faire une pause sur la sortie standard
	std::cin.ignore(1024, '\n');
	std::cout << " Appuyez sur une touche pour continuer";
	std::cin.get();


	// Permet de clear la sortie standard en affichant un message s'il y a eu une erreur
	value_returned = std::system("clear");
	if(value_returned != 0)
		std::cout << "Problem Clear" << std::endl;

	return arreter;
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
	Piece* piece;

	for(i = 0; i < 8 ; ++i)
	{
		std::cout << 7-i << "  |";
		for(j = 0 ; j < 8 ; ++j)
		{
			piece =_board[j][7-i]; 

			if (isPieceIn(piece,p1))
				std::cout << _board[j][7-i]->getLabel() << "|";
			else
				std::cout << "\x1B[31;1m" << _board[j][7-i]->getLabel() << "\x1B[m" << "|";
		}

		std::cout << std::endl;
	}
  	std::cout << "y/x ";

	for(k = 0; k < 8 ; ++k)
		std::cout << k << " ";

	std::cout << std::endl;
}

//------------------------------------------------------------------------------------------------------
// regarde si la piece appartient au joueur
bool Chess::isPieceIn(Piece* piece, Player* playerIG)
{
	bool trouve = false;
	int i = 0;

	while(!trouve && (i < 16) )
	{
		if(piece->getSquare()==playerIG->getPieces()[i]->getSquare())
			trouve = true;
		++i;
	}
	return trouve;
}

//------------------------------------------------------------------------------------------------------
bool Chess::testEchec(Player* playerIG, Player* adver)
{
	Piece* kingIG;
	kingIG = playerIG->getKing();
	bool res = testEchec(kingIG, adver);

	if(res)
		playerIG->check();
	else
		playerIG->inGame();

	return res;
}

//------------------------------------------------------------------------------------------------------
bool Chess::testEchec(Piece* selectedP, Player* adver)
{
	bool positionEchec = false;
	Piece* selectedD;
	int i = 0;

	// regarde si une piece selectedP peut se faire manger par le joueur adverse
	while( (positionEchec == false) && (i < 16) )
	{
		selectedD = adver->getPieces()[i];
		if (!(selectDest(adver,selectedD, selectedP->getSquare()->getX(), selectedP->getSquare()->getY())==NULL))
		{
			if(noCollision(selectedD, selectedP))
				positionEchec = true;
		}
		i++;
	}
	return positionEchec;
}

//------------------------------------------------------------------------------------------------------
bool Chess::isNull()
{
	bool tabpieceenviep1[16];
	bool tabpieceenviep2[16];
	int i;
	bool res = false;
	bool test1 = true;
	bool test2;
	bool test3;
	bool test4;
	for (i = 0 ; i < 16 ; ++i)
	{
		if(p1->getPieces()[i]->isAlive())
			tabpieceenviep1[i] = true;
		else
			tabpieceenviep1[i] = false;

		if(p2->getPieces()[i]->isAlive())
			tabpieceenviep2[i] = true;
		else
			tabpieceenviep2[i] = false;
	}
	// si il ne reste plus que deux rois

	for(i = 0; i < 16 ; ++i)
	{
		if(i != 12)
		{
			if(tabpieceenviep1[i])
				test1 = false;
			if(tabpieceenviep2[i])
				test1 = false;
		}
	}
	if(test1)
	{
		res = true;
	}
	if(!res)
	{
		// s'il ne reste plus que deux rois et un fou
		test2 = true;
		for(i = 0 ; i < 16 ; ++i)
		{
			if(i != 12)
			{
				if( (i != 10) && (i != 13) )
				{
					if(tabpieceenviep1[i])
						test2 = false;
					if(tabpieceenviep2[i])
						test2 = false;
				}
			}
		}
		if(test2)
		{
			if(tabpieceenviep1[10] && tabpieceenviep2[10])
				test2 = false;
			if(tabpieceenviep1[13] && tabpieceenviep2[13])
				test2 = false;
			if(tabpieceenviep1[10] && tabpieceenviep1[13])
				test2 = false;
			if(tabpieceenviep2[10] && tabpieceenviep2[13])
				test2 = false;
		}

		if(test2)
			res = true;

		if(!res)
		{
			// s'il ne reste plus que deux roi et un cavalier
			test3 = true;
			for(i = 0 ; i < 16 ; ++i)
			{
				if(i!=12)
				{
					if(i != 9 && i != 14)
					{
						if(tabpieceenviep1[i])
							test3 = false;
						if(tabpieceenviep2[i])
							test3 = false;
					}
				}
			}
			if(test3)
			{
				if(tabpieceenviep1[9] && tabpieceenviep2[9])
					test3 = false;
				if(tabpieceenviep1[14] && tabpieceenviep2[14])
					test3 = false;
				if(tabpieceenviep1[9] && tabpieceenviep1[14])
					test3 = false;
				if(tabpieceenviep2[9] && tabpieceenviep2[14])
					test3 = false;
			}
			if(test3)
				res = true;
			if(!res)
			{	
				// s'il ne reste plus que un roi et 1 fou pour chaque joueurs
				test4 = true;
				for(i = 0; i < 16 ; ++i)
				{
					if(i != 12)
					{
						if(i !=9 && i != 14)
						{
							if(tabpieceenviep1[i])
								test3 = false;
							if(tabpieceenviep2[i])
								test3 = false;
						}
					}
				}
				if(test4)
				{
					if(tabpieceenviep1[10] && tabpieceenviep1[13])
						test4 = false;
					if(tabpieceenviep2[10] && tabpieceenviep2[13])
						test4 = false;
				}
				if(test4)
				{
					res=true;
				}
			}
		}
	}
	if(!res)
	{
		//cas pat pour p1 !!
		bool test4 = true;
		Piece* piece_test;
		Piece* pieceD;
		int q,w;
		for(i = 0 ; i < 16 ; ++i)
		{
			for(q = 0 ; q < p1->getPieces()[i]->getMovements().size(); ++q)
			{
				for(w = 0 ; w < p1->getPieces()[i]->getMovements()[q].size() ; ++w)
				{
					piece_test= p1->getPieces()[i];
					pieceD=_board[p1->getPieces()[i]->getMovements()[q][w]->getX()][p1->getPieces()[i]->getMovements()[q][w]->getY()];
					if(noCollision(piece_test, pieceD))
					{
						if(!listCanEatKing(listPieces(piece_test, p2),p2,p1, piece_test, pieceD))//voir si le déplacement de cette piece  n'implique pas encore un echec
							test4 = false;
					}
				}
			}
		}
		//cas pat pour p2!
		for(i = 0 ; i < 16 ; ++i)
		{
			for(q = 0; q < p2->getPieces()[i]->getMovements().size() ; ++q)
			{
				for(w = 0 ; w < p2->getPieces()[i]->getMovements()[q].size(); ++w)
				{
					piece_test = p2->getPieces()[i];
					pieceD = _board[p2->getPieces()[i]->getMovements()[q][w]->getX()][p2->getPieces()[i]->getMovements()[q][w]->getY()];
					if(noCollision(piece_test, pieceD))
					{
						if(!listCanEatKing(listPieces(piece_test, p1),p1,p2, piece_test, pieceD))//voir si le déplacement de cette piece  n'implique pas encore un echec
							test4 = false;
					}
				}
			}
		}
		if(test4)
			res = true;	
	}
	if (res)
	{
		p1->gameNull();
		p2->gameNull();
	}
	return res;
}
//------------------------------------------------------------------------------------------------------

bool Chess::testEchecMat(Player* playerIG, Player* adver)
{
	bool res = false;
	bool peuxbloque = false;
	bool found;
	int w = 0;
	int indice = -1;
	int indicebis = -1;

	Piece* piecetueuse;

	int positionEchecmat = 0;
	Piece* king_deplacement_virtuel = new Piece(0,0);
	Piece* kingIG;
	kingIG = playerIG->getKing();
	int i,x,y,s;

	if(!isNull()){
		if(testEchec(playerIG,adver))
		{
			s = 0;
			// regarde si le roi peut bouger sans qu'il se remette en position d'echec 
			for(i = 0; i < kingIG->getMovements().size(); ++i)
			{
				x = kingIG->getMovements()[i][0]->getX();
				y = kingIG->getMovements()[i][0]->getY();
				king_deplacement_virtuel->setSquare(new Cell(x,y));
				if(_board[x][y]->getLabel() == " ")
				{	
					++s;
					if(testEchec(king_deplacement_virtuel,adver))
						positionEchecmat++;
				}
				// s'il peut manger la piece tueuse
				if(isPieceIn(_board[x][y],adver))
				{
					if(!testEchec(king_deplacement_virtuel,adver))
						peuxbloque = true;
				}
			}
			found = false;
			/***********************************/
			// recherche du point qui manger le roi
			if(positionEchecmat == s)//roi ne peut pas bouger
			{
				i = 0;
				while( (!found) && (i < 16) )
				{
					piecetueuse= adver->getPieces()[i];//on prend toute les pieces du joueur adverse
					if (!(selectDest(adver,piecetueuse, kingIG->getSquare()->getX(), kingIG->getSquare()->getY()) == NULL))	// si la piece peut manger le roi
						found = true;
					if(!found)
						++i;
				}
				/********************************************/
				// recherche l'indice du movement de la piece tueuse
				found = false;
				i = 0;
				while(i < piecetueuse->getMovements().size() && !found)
				{
					w = 0;
					while(w < piecetueuse->getMovements()[i].size()&&!found)
					{
						if( (piecetueuse->getMovements()[i][w]->getX() == kingIG->getSquare()->getX()) &&
							(piecetueuse->getMovements()[i][w]->getY() == kingIG->getSquare()->getY()) )
						{
							indice = i;
							indicebis = w;
							found = true;
						}
						if(!found)
							++w;
					}
					if(!found)
						++i;
				}
				//////////////  Maintenant faire toutes les pieces du joueurIG et voir s'ils peuvent lui couper le chemin !!!!
				Piece* piece_test;
				Piece* piece_tableau;
				for(i = 0; i < 16; ++i)
				{
					if(i != 12)
					{
						piece_test = playerIG->getPieces()[i];// on prend toute les pieces du joueur 						
						// on regarde si la piece du joueur peut manger la pièce tueuse !
						if(!(selectDest(playerIG,piece_test, piecetueuse->getSquare()->getX(), piecetueuse->getSquare()->getY())==NULL)) // on regarde s'il peut manger la piece qui le met en echec
						{
							if(noCollision(piece_test, piecetueuse))
							{
								if(!listCanEatKing(listPieces(piece_test, adver),adver,playerIG, piece_test, piecetueuse))//voir si le déplacement de cette piece  n'implique pas encore un echec
									peuxbloque = true;
							}
						}
						//on regarde si la piece du joueur peut se mettre sur le passage de la piece tueuse !
						for(w = 0 ; w < indicebis ; ++w)
						{
							if(!(selectDest(playerIG,piece_test, piecetueuse->getMovements()[indice][w]->getX(), piecetueuse->getMovements()[indice][w]->getY())==NULL)) // on regarde s'il ne peut pas manger la piece qui le met en echec
							{
								piece_tableau = _board[piecetueuse->getMovements()[indice][w]->getX()][piecetueuse->getMovements()[indice][w]->getY()];
								if(noCollision(piece_test, piece_tableau))
								{
									if(!listCanEatKing(listPieces(piece_test, adver),adver,playerIG, piece_test, piece_tableau))//voir si le déplacement de cette piece  n'implique pas encore un echec
										peuxbloque = true;							
								}
							}
						}
					}
				}
			}else
				peuxbloque = true;
			//si le joueur n'a pas moyen de couper le chemin ou de manger la piece tueuse alors le resultat est vrai
			if (!peuxbloque)
				res = true;
		}
	}
	// si resultat est vrai alors on passe le joueur en état d'echec et mat
	if (res){
		playerIG->checkMate();
	}

	delete king_deplacement_virtuel;

	return res;
}

//------------------------------------------------------------------------------------------------------
void Chess::startGame()
{
	bool finpartie = false;
	bool checkmate = false;
	std::string gagnant;

	while(!finpartie)
	{
		p1->getState()->print();

		finpartie = gameRound(p1, p2);

		if (testEchecMat(p2,p1) || isNull())
		{
			p1->getState()->print();
			finpartie = true;
		}
		else
		{
			p2->getState()->print();
			finpartie = gameRound(p2, p1);
		}
		if (testEchecMat(p1,p2) || isNull())
		{
			p1->getState()->print();
			finpartie = true;
		}
	}

	if(!p1->isnulle())
	{
		if(p1->isCheckMate())
		{
			checkmate = true;
			gagnant = p2->getName();
		}
		else if(p2->isCheckMate())
		{
			checkmate = true;
			gagnant = p1->getName();
		}
		if(checkmate)
			std::cout << " La partie est terminée, le Gagnant de cette partie est : " << gagnant << std::endl;
		else
			std::cout << " La partie est terminée ! " << gagnant << std::endl;
	}
	else
		std::cout << " La partie est terminée, car la partie est nulle." << std::endl;
}

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
	bool manger=false;
	Player* adver=p1;
	if(piece->isAlive()){
		// Si la case selectionnée correspond à une pièce que le joueur player possède
		for(i = 0 ; i < 16 ; ++i)
		{
			if( _board[x][y]->getSquare() == player->getPieces()[i]->getSquare() )
				return NULL;
		}
		// Si la case selectionnée correspond à une pièce que le joueur adver possède
		
		if(player->getName()==p1->getName())
			adver=p2;
		
		for(i = 0; i<16;++i)
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
bool Chess::noCollision(Piece* selectedP, Piece* selectedD, Piece* pieceeaeviter = NULL)
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
	x = selectedP->getMovements()[i][k]->getX();		
	y = selectedP->getMovements()[i][k]->getY();	
	while( noCollision && 
		  ( (selectedD->getSquare()->getX() != x) || (selectedD->getSquare()->getY() != y )) )
	{
			if(pieceeaeviter==NULL)
			{
				noCollision = (_board[x][y]->getLabel() == " "); // Si le label de la case (x,y) est " ", alors il n'y a pas de pièce réelle sur la case [i][k]
			}else
			{
				if( ! (( pieceeaeviter->getSquare()->getX()==x ) && ( pieceeaeviter->getSquare()->getY()==y ) ) )
					noCollision = (_board[x][y]->getLabel() == " "); // Si le label de la case (x,y) est " ", alors il n'y a pas de pièce réelle sur la case [i][k]
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
std::vector<Piece*> Chess::listepieces(Piece* selectedP, Player* advers)
{
	std::vector<Piece*> list;
	Piece* piecetueuse=NULL;
	for(int i=0;i<16;++i)
	{
		piecetueuse= advers->getPieces()[i];//on prend toute les pieces du joueur adverse
		if (!(selectDest(advers,piecetueuse, selectedP->getSquare()->getX(), selectedP->getSquare()->getY())==NULL))// si la piecetueuse peut aller théoriquement manger la piece selectedp
		{
			if(noCollision(piecetueuse, selectedP))//si la piecetueuse peut aller manger selectedP 
				{
					list.push_back(piecetueuse);
				}
		}
	}
	return list;
}

//------------------------------------------------------------------------------------------------------
bool Chess::listpeutmangerleroi(std::vector<Piece*> list, Player* advers, Player* playerIG, Piece* selectedP, Piece* selectedD)
{
	bool res= false;
	Piece* king = playerIG->getPieces()[12];
	Piece* piecetueuse=NULL;

	for(int i=0; i<list.size();++i)
	{
		piecetueuse= list[i];//on prend toute les pieces du joueur adverse
		if (!(selectDest(advers,piecetueuse, king->getSquare()->getX(), king->getSquare()->getY())==NULL))// si la piecetueuse peut aller théoriquement manger la piece selectedp
		{
			if((selectDest(advers,piecetueuse, selectedD->getSquare()->getX(), selectedD->getSquare()->getY())==NULL))
			{
				if(noCollision(piecetueuse, king, selectedP))//si la piecetueuse peut aller manger le roi en sautant la piece selectedP
					{
						res =true;

					}
			}
		}
	}
	if(res)
	{
		std::cout<<"Vous ne pouvez pas bouger cette piece sinon votre Roi sera encore en position d'échec";
	}
	return res;
}
//------------------------------------------------------------------------------------------------------
bool Chess::surlepassage(Player* playerIG, Piece* pieceD, Player* advers){
	Piece* king = playerIG->getPieces()[12];
	Piece* piecetueuse=NULL;
	bool trouve=false;
	int i=0;
	int yy=pieceD->getSquare()->getY();
	int xx=pieceD->getSquare()->getX();
	while((!trouve)&&i<16)
	{
		piecetueuse= advers->getPieces()[i];//on prend toute les pieces du joueur adverse
		if (!(selectDest(advers,piecetueuse, king->getSquare()->getX(), king->getSquare()->getY())==NULL))// si la piece peut manger le roi
		{
			trouve= true;
		}
		if(!trouve)
			i++;
	}
	//recherche l'indice dans movements
	int w=0;
	i=0;
	int indice =0;
	int indicebis=0;
	trouve=false;
	std::cout<<" piece tueuse "<<piecetueuse->getLabel()<<std::endl;
	if(!(piecetueuse==NULL))
	{
		/********************************************/
		// recherche l'indice du movement de la piece tueuse
		trouve=false;
		i=0;
		while(i<piecetueuse->getMovements().size()&&!trouve)
		{
			w=0;
			while(w<piecetueuse->getMovements()[i].size()&&!trouve)
			{
				if((piecetueuse->getMovements()[i][w]->getX()==king->getSquare()->getX())&&(piecetueuse->getMovements()[i][w]->getY()==king->getSquare()->getY()))
				{
					indice=i;
					indicebis=w;
					trouve=true;
					
				}
				if(!trouve)
					w++;
			}
			if(!trouve)
				i++;
		}
		trouve=false;
		i=0;
		//regarde si la destination est bien sur le passage de la piece
		int xxx;	
		int yyy;
		bool testttt1=false;
		bool testttt2=false;
		for(w=0;w<indicebis;++w)
		{
			xxx=piecetueuse->getMovements()[indice][w]->getX();
			yyy=piecetueuse->getMovements()[indice][w]->getY();
			std::cout<<"xx : "<< xx<< " yy "<<yy<<" xxx "<<xxx<<" yyy "<<yyy<<std::endl;
			testttt1=(xx==xxx);
			testttt2=(yy==yyy);
			if (testttt1 && testttt2)
				trouve = true;						
		}
	}
	return trouve;
}
//------------------------------------------------------------------------------------------------------
void Chess::transformationspawn(Player* playerIG, Piece* selectedP, Piece* selectedD)
{
	int choose;
	std::cout << "Vous pouvez transformer votre pion en : "<<std::endl;
	std::cout << "- Saissisez 0 pour le transformer en Reine."<<std::endl;
	std::cout << "- Saissisez 1 pour le transformer en fou."<<std::endl;
	std::cout << "- Saissisez 2 pour le transformer en cavalier."<<std::endl;
	std::cout << "- Saissisez 3 pour le transformer en tour."<<std::endl;
	choose = getChoiceInt();
	while(choose>3)
	{
		std::cout << "Veuillez saisir un chiffre entre 0 et 4 !"<<std::endl;
		choose = getChoiceInt();
	}
	// recheche de la coordonnée de la piece dans ces mains
	bool recherche=false;
	int coordonnee=0;
	while(!recherche&&coordonnee<16)
	{
		if(playerIG->getPieces()[coordonnee]->getSquare()==selectedP->getSquare())
			recherche=true;
		if(!recherche)
			++coordonnee;
	}
	// le spnaw devient une reine
	if(choose==0)
	{
		movePiece(selectedP, selectedD);
		playerIG->getPieces()[coordonnee]= new Queen(selectedD->getSquare()->getX(),selectedD->getSquare()->getY());
		selectedP->movement();// Mise à jour des déplacements possibles de la pièce depuis sa nouvelle position
		_board[selectedD->getSquare()->getX()][selectedD->getSquare()->getY()] = playerIG->getPieces()[coordonnee];	// La pièce est remplacé sur le plateau
	}
	// le spnaw devient un fou
	if(choose==1)
	{
		movePiece(selectedP, selectedD);
		playerIG->getPieces()[coordonnee]= new Bishop(selectedD->getSquare()->getX(),selectedD->getSquare()->getY());
		selectedP->movement();// Mise à jour des déplacements possibles de la pièce depuis sa nouvelle position
		_board[selectedD->getSquare()->getX()][selectedD->getSquare()->getY()] = playerIG->getPieces()[coordonnee];	// La pièce est remplacé sur le plateau

	}
	// le spnaw devient un cavalier
	if(choose==2)
	{
		movePiece(selectedP, selectedD);
		playerIG->getPieces()[coordonnee]= new Knight(selectedD->getSquare()->getX(),selectedD->getSquare()->getY());
		selectedP->movement();// Mise à jour des déplacements possibles de la pièce depuis sa nouvelle position
		_board[selectedD->getSquare()->getX()][selectedD->getSquare()->getY()] = playerIG->getPieces()[coordonnee];	// La pièce est remplacé sur le plateau

	}
	// le spnaw devient une tour
	if(choose==3)
	{
		movePiece(selectedP, selectedD);
		playerIG->getPieces()[coordonnee]= new Rook(selectedD->getSquare()->getX(),selectedD->getSquare()->getY());
		selectedP->movement();// Mise à jour des déplacements possibles de la pièce depuis sa nouvelle position
		_board[selectedD->getSquare()->getX()][selectedD->getSquare()->getY()] = playerIG->getPieces()[coordonnee];	// La pièce est remplacé sur le plateau	
	}
}
//------------------------------------------------------------------------------------------------------
// regarde si le petit roque est possible

bool Chess::gererpetitroque(Player* playerIG,Piece* selectedP,Piece* selectedD)
{
	bool res=false;
	if(playerIG->getPieces()[15]->isAlive()&&playerIG->getPieces()[15]->getMovements()[0][0]->getX()==playerIG->getPieces()[15]->getSquare()->getX()&&playerIG->getPieces()[15]->getMovements()[0][0]->getY()==playerIG->getPieces()[15]->getSquare()->getY())
		res=true;
	if(res)
		std::cout<<"Le petit roque est possible !"<<std::endl;
	return res;
}

//------------------------------------------------------------------------------------------------------
// regarde si le grand roque est possible
bool Chess::gerergrandroque(Player* playerIG,Piece* selectedP,Piece* selectedD)
{
	bool res=false;
	if(playerIG->getPieces()[8]->isAlive()&&playerIG->getPieces()[8]->getMovements()[0][0]->getX()==playerIG->getPieces()[8]->getSquare()->getX()&&playerIG->getPieces()[8]->getMovements()[0][0]->getY()==playerIG->getPieces()[8]->getSquare()->getY())
	{
		int x = playerIG->getPieces()[8]->getSquare()->getX()+1;
		int y = playerIG->getPieces()[8]->getSquare()->getY();
		if( ( _board[x][y]->getLabel()) == " ") 
			res=true;
	}
	if(res)
		std::cout<<"Le grand roque est possible !"<<std::endl;
	return res;
}

//------------------------------------------------------------------------------------------------------
//procédure permettant d'effectuer le petit roque, on suppose que gererpetitroque == true

void Chess::fairepetitroque(Player* playerIG)
{
	int xroi=playerIG->getking()->getSquare()->getX();
	int yroi=playerIG->getking()->getSquare()->getY();
	int xtour=playerIG->getPieces()[15]->getSquare()->getX();
	int ytour=playerIG->getPieces()[15]->getSquare()->getY();
	int x1=playerIG->getking()->getSquare()->getX()+2;
	int y1=playerIG->getking()->getSquare()->getY();
	int x2=x1-1;
	int y2=y1;
	_board[x1][y1] = playerIG->getking();	// Le roi est déplacée sur le plateau
	playerIG->getking()->setSquare(new Cell(x1,y1));// Mise à jour des coordonnées du roi qui vient d'être déplacée
	playerIG->getking()->movement();	
	_board[x2][y2] = playerIG->getPieces()[15];// la tour es déplacée
	playerIG->getPieces()[15]->setSquare(new Cell(x2,y2));// Mise à jour des coordonnées de la tour qui vient d'être déplacée
	_board[xroi][yroi] = new Piece(xroi,yroi);			// L'ancienne position de la pièce est maintenant une pièce "vide"
	_board[xtour][ytour] = new Piece(xtour,ytour);			// L'ancienne position de la pièce est maintenant une pièce "vide"



}
//------------------------------------------------------------------------------------------------------
//procédure permettant d'effectuer le grand roque, on suppose que gerergrandroque == true
void Chess::fairegrandroque(Player* playerIG)
{
	int xroi=playerIG->getking()->getSquare()->getX();
	int yroi=playerIG->getking()->getSquare()->getY();
	int xtour=playerIG->getPieces()[8]->getSquare()->getX();
	int ytour=playerIG->getPieces()[8]->getSquare()->getY();
	int x1=playerIG->getking()->getSquare()->getX()-2;
	int y1=playerIG->getking()->getSquare()->getY();
	int x2=x1+1;
	int y2=playerIG->getking()->getSquare()->getY();
	_board[x1][y1] = playerIG->getking();	// Le roi est déplacée sur le plateau
	playerIG->getking()->setSquare(new Cell(x1,y1));// Mise à jour des coordonnées du roi qui vient d'être déplacée
	playerIG->getking()->movement();	
	_board[x2][y2] = playerIG->getPieces()[8]; // la tour es déplacée
	playerIG->getPieces()[8]->setSquare(new Cell(x2,y2));// Mise à jour des coordonnées de la tour qui vient d'être déplacée
	playerIG->getPieces()[8]->movement();
	_board[xroi][yroi] = new Piece(xroi,yroi);			// L'ancienne position de la pièce est maintenant une pièce "vide"
	_board[xtour][ytour] = new Piece(xtour,ytour);			// L'ancienne position de la pièce est maintenant une pièce "vide"
}

//------------------------------------------------------------------------------------------------------
void Chess::gameRound(Player* playerIG, Player* advers)
{
	std::cout<<"C'est au tour de : "<<playerIG->getName()<<std::endl;
	Piece* selectedP;
	Piece* selectedD;
	unsigned int x, y, x2, y2,i,j;
	// Selection de la pièce du joueur
	bool choix=false;
	while(!choix)
	{
		printBoard();
		std::cout << "Coordonnées de la pièce que vous voulez selectionner : " << std::endl;
		std::cout << "x: ";
		x = getChoiceInt();
		std::cout << "y: ";
		y = getChoiceInt();

		selectedP = playerIG->selectPiece(x,y);
		//demande au joueur de selectionner une piece tant que la piece selectionnée n'est pas une piece a lui 
		while((selectedP == NULL))
		{
			std::cout << "Aucune pièce en votre possession ne se situe sur la case : (" << x << "," << y << ")" << std::endl;

			std::cout << "Entrer des nouvelles coordonnées : " << std::endl;
			std::cout << "x: ";
			x = getChoiceInt();
			std::cout << "y: ";
			y = getChoiceInt();

			selectedP = playerIG->selectPiece(x,y);
		}
		std::cout<<"voici les déplacements possible de la pièce : "<<std::endl;
		// afficher les déplacement possible de la piece
		for(i = 0 ; i < selectedP->getMovements().size() ; ++i)
		{
			for(j = 0 ; j < selectedP->getMovements()[i].size() ; ++j)
			{
				std::cout << "(" << selectedP->getMovements()[i][j]->getX() << "," << selectedP->getMovements()[i][j]->getY() << ")" << std::endl;
			}
			std::cout << std::endl;
		}
		std::cout << "Vous avez selectionné la pièce :" << std::endl;
		selectedP->printPiece();

		std::cout << "Coordonnées de la case sur laquelle vous voulez déplacer la pièce : " << std::endl;
		std::cout << "x: ";
		x2 = getChoiceInt();
		std::cout << "y: ";
		y2 = getChoiceInt();
		selectedD = selectDest(playerIG, selectedP, x2, y2); 	
		if(!(selectedD == NULL))
		{
		// Selection valide de la destination sur le plateau ( selectedD sera soit une pièce adverse, soit une pièce "vide" )
			if(!listpeutmangerleroi(listepieces(selectedP, advers), advers, playerIG, selectedP, selectedD))//évite de mettre le joueur en etat d'echec ou en état echec et mat s'il se trouve déja en echec
			{
				if(!(playerIG->ischeck()))
				{
				// Test s'il y a une collision ou non avec une pièce réelle lors du déplacement de selectedP vers selectedD
					if(selectedP->getLabel()=="K")
					{
						// gerer le cas du petit et grand roque
						if(selectedP->getMovements().size()==7)//signifie indirectement que le roi n'a pas encore bougé
						{
							bool roque=false;
							// si le cas du petit roque est demandé 
							if(selectedP->getSquare()->getX()<6&&selectedD->getSquare()->getX()==(selectedP->getSquare()->getX()+2))
							{
								int xroipetit = selectedP->getSquare()->getX();
								int yroipetit = selectedP->getSquare()->getY();
								// regarde si aucune pieces se trouve entre le roi et la tour
								bool test1 = (_board[xroipetit+1][yroipetit]->getLabel()==" ");
								bool test2 = (_board[xroipetit+2][yroipetit]->getLabel()==" ");
								if(test1&&test2)
									roque = gererpetitroque(playerIG,selectedP,selectedD);
									if(roque)
										choix=true;
										fairepetitroque(playerIG);
							}else
							{
								//si le cas du grand roque est demandé
								if(selectedP->getSquare()->getX()>2&&selectedD->getSquare()->getX()==(selectedP->getSquare()->getX()-2))
								{
									int xroipetit = selectedP->getSquare()->getX();
									int yroipetit = selectedP->getSquare()->getY();
									// regarde si aucune pieces se trouve entre le roi et la tour
									bool test1 = (_board[xroipetit-1][yroipetit]->getLabel()==" ");
									bool test2 = (_board[xroipetit-2][yroipetit]->getLabel()==" ");
									bool test3 = (_board[xroipetit-3][yroipetit]->getLabel()==" ");
									if(test1&&test2&&test3)
									{
										roque = gerergrandroque(playerIG,selectedP,selectedD);
										if(roque)
											choix=true;
											fairegrandroque(playerIG);
									}
								}else
								{
									if(noCollision(selectedP, selectedD))
									{
										choix=true;
										movePiece(selectedP, selectedD);		// déplacement de la pièce selectionnée vers selectedD
									}
								}
							}
						}else
						{
							if(noCollision(selectedP, selectedD))
							{
								choix=true;
								movePiece(selectedP, selectedD);		// déplacement de la pièce selectionnée vers selectedD
							}
						}
					}else
					{
						if(noCollision(selectedP, selectedD))
						{
							if(!(selectedP->getLabel()=="S"))// si le pion selectionné n'est pas un spawn
							{
									choix=true;
									movePiece(selectedP, selectedD);		// déplacement de la pièce selectionnée vers selectedD
							}else
							{
								if( ( playerIG->getColor()=="White" ) || ( playerIG->getColor()=="Blanc") )
								{
									// cas pour transformer le spawn en reine, fou ..... si possible
									if(selectedD->getSquare()->getY()==7)
									{
										transformationspawn(playerIG, selectedP, selectedD);
										choix=true;
									}else// sinon faire le cas normal
									{
										choix=true;
										movePiece(selectedP, selectedD);		// déplacement de la pièce selectionnée vers selectedD	
									}
								}else
								{
									if(selectedD->getSquare()->getY()==0)
									{
										transformationspawn(playerIG, selectedP, selectedD);
										choix=true;
									}else
									{
										choix=true;
										movePiece(selectedP, selectedD);		// déplacement de la pièce selectionnée vers selectedD
									}
								}
							}
						}
						else
						{
							std::cout << "collision !!" << std::endl;
						}
					}
				}else
				{
					std::cout<<"Coucou "<<std::endl;
					selectedD = selectDest(playerIG, selectedP, x2, y2); 	
					if(selectedD != NULL)
					{
						std::cout<<"Coucou "<<std::endl;
						if(surlepassage( playerIG, selectedD, advers))//regarde si la destination est sur la passage de l'adverse qui le met en echec
						{
							if(noCollision(selectedP, selectedD))
							{
									if(!listpeutmangerleroi(listepieces(selectedP, advers),advers,playerIG, selectedP, selectedD))//voir si le déplacement de cette piece  n'implique pas encore un echec
									{
										choix=true;
										movePiece(selectedP, selectedD);		// déplacement de la pièce selectionnée vers selectedD
									}
							}
						}
					}
					// Test s'il y a une collision ou non avec une pièce réelle lors du déplacement de selectedP vers selectedD
					if(choix == false)
					{
						std::cout << "Votre roi est en position d'echec alors veuillez bouger une autre piece ! " << std::endl;
					}
				}
			}
			if(!choix)
			{
				std::cout<<"Veuillez resaisir une piece!!"<<std::endl; 
			}
		}
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
	Piece* piece;
	for(i = 0; i < 8 ; ++i)
	{
		std::cout << 7-i<<"  |";
		for(j = 0 ; j < 8 ; ++j)
		{
			piece =_board[j][7-i]; 
			if (testpieceappartence(piece,p1))
			{
				std::cout << _board[j][7-i]->getLabel() << "|";
			}else{
				std::cout <<  "\x1B[31;1m"<<_board[j][7-i]->getLabel()<<"\x1B[m" << "|";
			}
		}

		std::cout << std::endl;
	}
	
  	std::cout <<"y/x ";

	for(k = 0; k < 8 ; ++k)
		std::cout << k <<" ";

	std::cout << std::endl;
}

//------------------------------------------------------------------------------------------------------
// regarde si la piece appartient au joueur
bool Chess::testpieceappartence(Piece* piece, Player* playerIG)
{
	bool trouve=false;
	int i =0;
	while(!trouve&&i<16)
	{
		if(piece->getSquare()==playerIG->getPieces()[i]->getSquare())
			trouve =true;
		++i;
	}
	return trouve;
}

//------------------------------------------------------------------------------------------------------
bool Chess::testechec(Player* playerIG, Player* adver)
{
	Piece* kingIG;
	kingIG = playerIG->getking();
	bool res = testechec(kingIG, adver);
	if(res)
		playerIG->check();
	else
		playerIG->inGame();
	return res;
}

//------------------------------------------------------------------------------------------------------
bool Chess::testechec(Piece* selectedP, Player* adver)
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
			{
				positionEchec = true;
			}
		}
		i++;
	}
	return positionEchec;
}

//------------------------------------------------------------------------------------------------------
bool Chess::testnull()
{
	bool tabpieceenviep1[16];
	bool tabpieceenviep2[16];
	int i;
	bool res=false;
	for (i=0;i<16;i++)
	{
		if(p1->getPieces()[i]->isAlive())
		{
			tabpieceenviep1[i]=true;
		}else
		{
			tabpieceenviep1[i]=false;
		}
		if(p2->getPieces()[i]->isAlive())
		{
			tabpieceenviep2[i]=true;
		}else
		{
			tabpieceenviep2[i]=false;
		}
	}
	// si il ne reste plus que deux rois
	bool test1 = true;
	for(i=0;i<16;i++)
	{
		if(i!=12)
		{
			if(tabpieceenviep1[i]==true)
				test1 = false;
			if(tabpieceenviep2[i]==true)
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
		bool test2 =true;
		for(i=0;i<16;i++)
		{
			if(i!=12)
			{
				if(i!=10&&i!=13)
				{
					if(tabpieceenviep1[i]==true)
						test2 = false;
					if(tabpieceenviep2[i]==true)
						test2 = false;
				}
			}
		}
		if(test2)
		{
			if(tabpieceenviep1[10]==true&&tabpieceenviep2[10]==true)
				test2=false;
			if(tabpieceenviep1[13]==true&&tabpieceenviep2[13]==true)
				test2=false;
			if(tabpieceenviep1[10]==true&&tabpieceenviep1[13]==true)
				test2=false;
			if(tabpieceenviep2[10]==true&&tabpieceenviep2[13]==true)
				test2=false;
		}
		if(test2)
		{
			res=true;
		}
		if(!res)
		{
			// s'il ne reste plus que deux roi et un cavalier
			bool test3 =true;
			for(i=0;i<16;i++)
			{
				if(i!=12)
				{
					if(i!=9&&i!=14)
					{
						if(tabpieceenviep1[i]==true)
							test3 = false;
						if(tabpieceenviep2[i]==true)
							test3 = false;
					}
				}
			}
			if(test3)
			{
				if(tabpieceenviep1[9]==true&&tabpieceenviep2[9]==true)
					test3=false;
				if(tabpieceenviep1[14]==true&&tabpieceenviep2[14]==true)
					test3=false;
				if(tabpieceenviep1[9]==true&&tabpieceenviep1[14]==true)
					test3=false;
				if(tabpieceenviep2[9]==true&&tabpieceenviep2[14]==true)
					test3=false;
			}
			if(test3)
			{
				res=true;
			}
			if(!res)
			{	
				// s'il ne reste plus que deux roi et 1 fou pour chaque joueurs
				bool test4 =true;
				for(i=0;i<16;i++)
				{
					if(i!=12)
					{
						if(i!=9&&i!=14)
						{
							if(tabpieceenviep1[i]==true)
								test3 = false;
							if(tabpieceenviep2[i]==true)
								test3 = false;
						}
					}
				}
				if(test4)
				{
					if(tabpieceenviep1[10]==true&&tabpieceenviep1[13]==true)
						test4=false;
					if(tabpieceenviep2[10]==true&&tabpieceenviep2[13]==true)
						test4=false;
				}
				if(test4)
				{
					res=true;
				}
			}
		}
	}
	if (res)
	{
		p1->gameNull();
		p2->gameNull();
	}
	return res;
}
//------------------------------------------------------------------------------------------------------

bool Chess::testechecmat(Player* playerIG, Player* adver)
{
	bool res = false;
	bool peuxbloque=false;
	if(!testnull()){
		if(testechec(playerIG,adver))
		{
			int positionEchecmat = 0;
			Piece* king_deplacement_virtuel=new Piece(0,0);
			Piece* kingIG;
			kingIG = playerIG->getking();
			int i,x,y,s;
			s=0;
			// regarde si le roi peut bouger sans qu'il se remette en position d'echec 
			for(i=0; i<kingIG->getMovements().size(); ++i)
			{
				x=kingIG->getMovements()[i][0]->getX();
				y=kingIG->getMovements()[i][0]->getY();
				king_deplacement_virtuel->setSquare(new Cell(x,y));
				if(_board[x][y]->getLabel()==" ")
				{	
					s++;
					if(testechec(king_deplacement_virtuel,adver))
					{
						positionEchecmat++;
					
					}
				}
				// s'il peut manger la piece tueuse
				if(testpieceappartence(_board[x][y],adver))
				{
					if(!testechec(king_deplacement_virtuel,adver))
					{
						peuxbloque=true;
					}	
				}
			}
			bool found= false;
			Piece* piecetueuse;
			int w=0;
			int indice=-1;
			int indicebis=-1;
			/***********************************/
			std::cout<<"position :"<<positionEchecmat<<" et s : "<<s<<std::endl;
			// recherche du point qui manger le roi
			if(positionEchecmat==s)//roi ne peut pas bouger
			{
				i=0;
				while((!found)&&i<16)
				{
					piecetueuse= adver->getPieces()[i];//on prend toute les pieces du joueur adverse
					if (!(selectDest(adver,piecetueuse, kingIG->getSquare()->getX(), kingIG->getSquare()->getY())==NULL))// si la piece peut manger le roi
					{
						found= true;
					}
					if(!found)
						i++;
				}
				/********************************************/
				// recherche l'indice du movement de la piece tueuse
				bool found=false;
				i=0;
				while(i<piecetueuse->getMovements().size()&&!found)
				{
					w=0;
					while(w<piecetueuse->getMovements()[i].size()&&!found)
					{
						if((piecetueuse->getMovements()[i][w]->getX()==kingIG->getSquare()->getX())&&(piecetueuse->getMovements()[i][w]->getY()==kingIG->getSquare()->getY()))
						{
							indice=i;
							indicebis=w;
							found=true;
							
						}
						if(!found)
							w++;
					}
					if(!found)
						i++;
				}
				//////////////  Maintenant faire toute les piece du joueurIG et voir s'il peuvent lui couper le chemin !!!!
				Piece* piece_test;
				Piece* piece_tableau;
				for(i=0;i<16;++i)
				{
					if(i!=12)
					{
						piece_test= playerIG->getPieces()[i];// on prend toute les pieces du joueur 						
						// on regarde si la piece du joueur peut manger la pièce tueuse !
						if(!(selectDest(playerIG,piece_test, piecetueuse->getSquare()->getX(), piecetueuse->getSquare()->getY())==NULL)) // on regarde s'il peut manger la piece qui le met en echec
						{
							if(noCollision(piece_test, piecetueuse))
							{
								if(!listpeutmangerleroi(listepieces(piece_test, adver),adver,playerIG, piece_test, piecetueuse))//voir si le déplacement de cette piece  n'implique pas encore un echec
									peuxbloque=true;
							}
						}
						//on regarde si la piece du joueur peut se mettre sur le passage de la piece tueuse !
						for(w=0;w<indicebis;++w)
						{
							if(!(selectDest(playerIG,piece_test, piecetueuse->getMovements()[indice][w]->getX(), piecetueuse->getMovements()[indice][w]->getY())==NULL)) // on regarde s'il ne peut pas manger la piece qui le met en echec
							{
								piece_tableau=_board[piecetueuse->getMovements()[indice][w]->getX()][piecetueuse->getMovements()[indice][w]->getY()];
								if(noCollision(piece_test, piece_tableau))
								{
									if(!listpeutmangerleroi(listepieces(piece_test, adver),adver,playerIG, piece_test, piece_tableau))//voir si le déplacement de cette piece  n'implique pas encore un echec
										peuxbloque=true;							
								}
							}
						}
					}
				}
			}
			//si le joueur n'a pas moyen de couper le chemin ou de manger la piece tueuse alors le resultat est vrai
			if (!peuxbloque)
			{
				res=true;
			}	
		}
	}
	// si resultat est vrai alors on passe le joueur en état d'echec et mat
	if (res){
		playerIG->checkMate();
	}
	return res;
}

//------------------------------------------------------------------------------------------------------
void Chess::startGame()
{
	//Piece* p = _board[0][1];
	bool finpartie=false;
	while(!finpartie)
	{
		p1->getState()->print();
		gameRound(p1, p2);
		if (testechecmat(p2,p1)||testnull())
		{
			p1->getState()->print();
			finpartie=true;
		}else
		{
			p2->getState()->print();
			gameRound(p2, p1);
		}
		if (testechecmat(p1,p2)||testnull())
		{
			p1->getState()->print();
			finpartie=true;
		}
	}
	if(!p1->isnulle())
	{
		std::string gagnant;
		if(p1->ischeckmate())
		{
			gagnant=p2->getName();
		}else
		{	
			gagnant=p1->getName();
		}	
		std::cout<<"La partie est terminé, le Gagnant de ce partie est : "<<gagnant<<std::endl;
	}else{
		std::cout<<"La partie est terminé, car la partie est nulle."<<std::endl;
	}
}

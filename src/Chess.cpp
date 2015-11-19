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
		// recherche dans quel rend se trouve la piece dans ses mains
		int cpt =0;
		while(cpt<16 && !( *(player->getPieces()[cpt]->getSquare()) == *(piece->getSquare()) ) )
		{
			cpt++;
		}
		// Si la case sélectionnée correspond à un déplacement théorique possible de la pièce
		if(cpt>7)
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
	x = selectedP->getMovements()[i][k]->getX();		
	y = selectedP->getMovements()[i][k]->getY();	
	while( noCollision && 
		  ( (selectedD->getSquare()->getX() != x) || (selectedD->getSquare()->getY() != y )) )
	{
		noCollision = (_board[x][y]->getLabel() == " "); // Si le label de la case (x,y) est " ", alors il n'y a pas de pièce réelle sur la case [i][k]
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

			testttt1=(xx==xxx);
			testttt2=(yy==yyy);
			// probleme car quand j'ai true && true il ne veux pas rentré dedans !!! pourquoi ??
			trouve=(testttt1 && testttt2);							


		}
	}
	std::cout<<"solution est :::::::"<<trouve<<std::endl;
	return trouve;
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
		std::cout<<"voici les déplacements possible de la pièce : "<<std::endl;
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
		// Selection valide de la destination sur le plateau ( selectedD sera soit une pièce adverse, soit une pièce "vide" )
		if(!(playerIG->ischeck()))
		{
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
				choix=true;
				movePiece(selectedP, selectedD);		// déplacement de la pièce selectionnée vers selectedD
			}
			else
			{
				std::cout << "collision !!" << std::endl;
			}
		}else
		{
			std::cout<<"echec :"<<playerIG->ischeck()<<std::endl;
			//std::cout<<"testttt xxxxxxxxxxx :"<<testsauv->getSquare()->getX()<<std::endl;
			//std::cout<<"testttt yyyyyyyyyyyy :"<<testsauv->getSquare()->getY()<<std::endl;
			selectedD = selectDest(playerIG, selectedP, x2, y2); 	
			std::cout<<"x destination ? "<<selectedD->getSquare()->getX()<<std::endl;
			std::cout<<"y destination ? "<<selectedD->getSquare()->getY()<<std::endl;			
			std::cout<<"testttt sur le passage "<<surlepassage( playerIG, selectedD, advers)<<std::endl;
			if(selectedD != NULL)
			{
				if(surlepassage( playerIG, selectedD, advers))
				{
					if(noCollision(selectedP, selectedD))
					{
						choix=true;
						movePiece(selectedP, selectedD);		// déplacement de la pièce selectionnée vers selectedD
					}
				}
			}
			// Test s'il y a une collision ou non avec une pièce réelle lors du déplacement de selectedP vers selectedD

			if(choix == false)
			{
				std::cout << "Votre roi est en position d'echec alors veuillez bouger une autre piece ! " << std::endl;
			}
			/*}else
			{
					std::cout << "veuillez prendre une autre piece car vous êtes en mode echec !!" << std::endl;
			}*/
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
bool Chess::testechecmat(Player* playerIG, Player* adver)
{
	bool res = false;
	bool peuxbloque=false;
	if(testechec(playerIG,adver))
	{
		int positionEchecmat = 0;
		Piece* king_deplacement_virtuel=new Piece(0,0);
		Piece* kingIG;
		kingIG = playerIG->getking();
		int i,x,y,s;
		s=0;
		for(i=0; i<kingIG->getMovements().size(); ++i)
		{
			x=kingIG->getMovements()[i][0]->getX();
			y=kingIG->getMovements()[i][0]->getY();
			king_deplacement_virtuel->setSquare(new Cell(x,y));
			if(playerIG->selectPiece(x,y)==NULL)
			{	
				s++;
				if(testechec(king_deplacement_virtuel,adver))
				{
					positionEchecmat++;
				
				}
			}
		}
		bool found= false;
		Piece* piecetueuse;
		int w=0;
		int indice=-1;
		int indicebis=-1;
		/***********************************/
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
			//////////////  Maintenant faire toute les piece de lautre joueur et voir s'il peuvent lui couper le chemin !!!!
			////////////////////////////a faire !!!!!!!!!!!!!!!
			Piece* piece_test;
			Piece* piece_tableau;

			for(i=0;i<16;++i)
			{
				piece_test= playerIG->getPieces()[i];// on prend toute les pieces du joueur 						
				if(i!=12)
				{
					if(!(selectDest(playerIG,piece_test, piecetueuse->getSquare()->getX(), piecetueuse->getSquare()->getY())==NULL)) // on regarde s'il peut manger la piece qui le met en echec
					{
						if(noCollision(piece_test, piecetueuse))
						{
							peuxbloque=true;
						}
					}
					for(w=0;w<indicebis;++w)
					{
						if(!(selectDest(playerIG,piece_test, piecetueuse->getMovements()[indice][w]->getX(), piecetueuse->getMovements()[indice][w]->getY())==NULL)) // on regarde s'il ne peut pas manger la piece qui le met en echec
						{
							piece_tableau=_board[piecetueuse->getMovements()[indice][w]->getX()][piecetueuse->getMovements()[indice][w]->getY()];
							if(noCollision(piece_test, piece_tableau))
								peuxbloque=true;							
						}
					}
				}
			}
		}
		if (!peuxbloque)
		{
			res=true;
		}	
	}
	////////////////cas petit et grand roque
	///////////////////////////A REVOIR ////////////////////////////////////////////////
	bool roque=false;
	/*bool direction;//true vers le haut
	bool test=false;
	int y=0;
	int i;
	if(res)
	{
		if( (playerIG->getColor() == "White") || (playerIG->getColor() == "Blanc") )
		{
			direction =true;
		}else 
		{		
			direction=false;
		}		
		if(direction)
		{
			y=0;
		}else 
		{
			y=7;
		}
		if( (playerIG->getPieces()[8]->isAlive()) && !(playerIG->getPieces()[8]->asMoved()) )//la tour n'a pas bougé et est en vie
		{
			test=true;
			for(i=1;i<4;i++)
			{
				if(!(_board[y][i]!=NULL) )
					test=false;
			}
		}
		if(test==true)
		{
			res=false;
			roque=true;
			std::cout<<" le joueur n'est pas en echec et mat car il peut faire le grand roque !! "<<std::endl;
		}
		if( !roque && (playerIG->getPieces()[8]->isAlive()) && !(playerIG->getPieces()[8]->asMoved()) )
		{
			test=true;
			for(i=7;i>4;i--)
			{
				if(!(_board[y][i]!=NULL) )
					test=false;
			}
		}
		if(test==true)
		{
			res=false;
			roque=true;
			std::cout<<" le joueur n'est pas en echec et mat car il peut faire le petit roque !! "<<std::endl;
		}
	}*/
	if (res&&!roque){
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
		if (testechecmat(p2,p1))
		{
			p1->getState()->print();
			finpartie=true;
		}else
		{
			p2->getState()->print();
			gameRound(p2, p1);
		}
		if (testechecmat(p1,p2))
		{
			p1->getState()->print();
			finpartie=true;
		}
	}
	std::string gagnant;
	if(p1->ischeckmate())
	{
		gagnant=p2->getName();
	}else
	{	
		gagnant=p1->getName();
	}	
	std::cout<<"La partie est terminé, le Gagnant de ce partie est : "<<gagnant<<std::endl;
	/*unsigned int i, j;

	Piece* p = _board[3][7];			// Coordonnées de la pièce sur laquelle tu veux afficher les déplacements possible

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
	for(i = 0 ; i < 2 ; ++i)
		{
		std::cout<<" joueur 2 a vous de jouer !! "<<std::endl;
		gameRound(p1, p2);
		printBoard();
		for(m = 0 ; m < p->getMovements().size() ; ++m)
		{
			for(j = 0 ; j < p->getMovements()[m].size() ; ++j)
			{
				
				std::cout << "(" <<m<< p->getMovements()[m][j]->getX() << "," << p->getMovements()[m][j]->getY() <<j<< ")" << std::endl;
			}
			std::cout << std::endl;
		}
	}
	for(i = 0 ; i < 8 ; ++i)
	{
		std::cout<<" testechec p2 p1 :?????????? "<<testechec(p1,p2)<<std::endl;
		std::cout<<" testechecmat p2 p1 : "<<testechecmat(p1,p2)<<std::endl;
		std::cout<<" joueur 1 a vous de jouer !! "<<std::endl;
		gameRound(p2, p2);
		printBoard();
		for(m = 0 ; m < p->getMovements().size() ; ++m)
		{
			for(j = 0 ; j < p->getMovements()[m].size() ; ++j)
			{
				std::cout << "(" << p->getMovements()[m][j]->getX() << "," << p->getMovements()[m][j]->getY() << ")" << std::endl;
			}
			std::cout << std::endl;
		}
		//std::cout<<" testechecmat p1 p2 : "<<testechecmat(p1,p2)<<std::endl;
		
	}*/

	/*std::cout << _board[3][4]->getLabel() << "(" << _board[3][4]->getSquare()->getX() << "," << _board[3][4]->getSquare()->getY() << ")" << std::endl;
	for(i = 0 ; i < _board[3][4]->getMovements().size() ; ++i)
	{
		for(j = 0 ; j < _board[3][4]->getMovements()[i].size() ; ++j)
		{
			std::cout << "(" << _board[3][4]->getMovements()[i][j]->getX() << "," << _board[3][4]->getMovements()[i][j]->getY() << ")" << std::endl;
		}
		std::cout << std::endl;
	}*/
	//p1->printState();
	//p2->printPieces();

}

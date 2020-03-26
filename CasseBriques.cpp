#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include <time.h>
#include "GrilleSDL.h"
#include "Ressources.h"

// Dimensions de la grille de jeu
#define NB_LIGNES   21
#define NB_COLONNES 20

// Macros utilisees dans le tableau tab
#define VIDE                     0
#define BARRE                    -1
#define BILLE                    -2
#define BONUS                    -3

// Autres macros
#define NO                       100001
#define NE                       100002
#define SO                       100003
#define SE                       100004

int tab[NB_LIGNES][NB_COLONNES]
={ {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};

#define NB_BONUS_JAUNE  5      // la raquette s'allonge
#define NB_BONUS_VERT   5      // la raquette se retrecit
#define NB_BONUS_MAUVE  10     // multi-billes
#define NB_BONUS_BOMBE  1     // bombe

typedef struct
{
	int L;
	int C;
	int couleur;
	int nbTouches;
	int brise;
	int bonus;
} S_BRIQUE;

typedef struct
{
	int L ;
	int C ;
	int longueur ;
	bool billeSurRaquette ;
} S_RAQUETTE ;

typedef struct
{
	int L ;
	int C ;
	int dir ;
	int couleur ;
} S_BILLE ;

typedef struct
{
	int L;
	int C;
	int couleur;
} S_BONUS ;



#define NB_BRIQUES      56     // nombre de briques au depart
S_BRIQUE Briques[]
={ {2,2,GRIS,1,0,0},{2,4,GRIS,1,0,0},{2,6,GRIS,1,0,0},{2,8,GRIS,1,0,0},
   {2,10,GRIS,1,0,0},{2,12,GRIS,1,0,0},{2,14,GRIS,1,0,0},{2,16,GRIS,1,0,0},
   {3,2,MAUVE,2,0,0},{3,4,MAUVE,2,0,0},{3,6,MAUVE,2,0,0},{3,8,MAUVE,2,0,0},
   {3,10,MAUVE,2,0,0},{3,12,MAUVE,2,0,0},{3,14,MAUVE,2,0,0},{3,16,MAUVE,2,0,0},
   {4,2,GRIS,1,0,0},{4,4,GRIS,1,0,0},{4,6,GRIS,1,0,0},{4,8,GRIS,1,0,0},
   {4,10,GRIS,1,0,0},{4,12,GRIS,1,0,0},{4,14,GRIS,1,0,0},{4,16,GRIS,1,0,0},
   {5,2,VERT,2,0,0},{5,4,VERT,2,0,0},{5,6,VERT,2,0,0},{5,8,VERT,2,0,0},
   {5,10,VERT,2,0,0},{5,12,VERT,2,0,0},{5,14,VERT,2,0,0},{5,16,VERT,2,0,0},
   {6,2,GRIS,1,0,0},{6,4,GRIS,1,0,0},{6,6,GRIS,1,0,0},{6,8,GRIS,1,0,0},
   {6,10,GRIS,1,0,0},{6,12,GRIS,1,0,0},{6,14,GRIS,1,0,0},{6,16,GRIS,1,0,0},
   {7,2,BLEU,2,0,0},{7,4,BLEU,2,0,0},{7,6,BLEU,2,0,0},{7,8,BLEU,2,0,0},
   {7,10,BLEU,2,0,0},{7,12,BLEU,2,0,0},{7,14,BLEU,2,0,0},{7,16,BLEU,2,0,0},
   {8,2,GRIS,1,0,0},{8,4,GRIS,1,0,0},{8,6,GRIS,1,0,0},{8,8,GRIS,1,0,0},
   {8,10,GRIS,1,0,0},{8,12,GRIS,1,0,0},{8,14,GRIS,1,0,0},{8,16,GRIS,1,0,0}};

struct sigaction sigAct;
pthread_key_t cleRaquette, cleBille, cleBrique;
pthread_t tidRaquette, threadAffTime, tidEvent, tidBille, tidBrique,tidNiveau, tidScore, tidBonus;
pthread_mutex_t mutexTab,mutexBilleBrique, mutexScore,mutexRaquetteLong, mutexLetsGo;
pthread_cond_t condBilleBrique, condScore,condRaquetteLong;

pthread_once_t ControleCle = PTHREAD_ONCE_INIT;
pthread_once_t ControleMutex = PTHREAD_ONCE_INIT;
pthread_once_t ControleVarCond = PTHREAD_ONCE_INIT;

int	nbBriques;
int	nbBilles;
bool	niveauFini;
int	delaiBille = 150;
int 	score = 0;
bool	MAJScore;
int	letsgo = 0;

void Attente(int milli);
void *fctThreadRaquette(int *param);
void *fctThreadEvent(int *param);
void *fctThreadBille(S_BILLE *bille);
void *fctThreadBrique(S_BRIQUE *brique);
void *fctThreadNiveau(void *p);
void *fctThreadScore(void *p);
void *fctThreadBonus(S_BONUS *bonus);

void finThreadBille(void *p);
void finThreadBrique(void *p);
void finThreadBonus(S_BONUS *bonus);

void destructeur(void *p);

void HandlerSIGINT(int sig);
void HandlerSIGUSR1(int sig);
void HandlerSIGUSR2(int sig);
void HandlerSIGHUP(int sig);
void HandlerSIGTRAP(int sig);
void HandlerSIGURG(int sig);
void HandlerSIGSYS(int sig);
void HandlerSIGPIPE(int sig);
void HandlerSIGEMT(int sig);
void HandlerSIGALRM(int sig);
void HandlerSIGPROF(int sig);

void	initCle();
void	initMutex();
void	initVarCond();


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc,char* argv[])
{
	int paramEff, retThread;
	int i;

	sigset_t mask;
	sigAct.sa_flags = 0;

	// Ouverture de la fenetre graphique
	printf("(THREAD MAIN %d) Ouverture de la fenetre graphique\n",pthread_self());
	fflush(stdout);
	if (OuvertureFenetreGraphique() < 0)
	{
		printf("Erreur de OuvrirGrilleSDL\n");
		fflush(stdout);
		exit(1);
	}
	
	sigemptyset(&sigAct.sa_mask);	
	
	sigAct.sa_handler = HandlerSIGINT;
	sigaction(SIGINT, &sigAct, NULL);

	sigAct.sa_handler = HandlerSIGUSR1;
	sigaction(SIGUSR1, &sigAct, NULL);

	sigAct.sa_handler = HandlerSIGUSR2;
	sigaction(SIGUSR2, &sigAct, NULL);
	
	sigAct.sa_handler = HandlerSIGURG;
	sigaction(SIGURG, &sigAct, NULL);

	sigAct.sa_handler = HandlerSIGHUP;
	sigaction(SIGHUP, &sigAct, NULL);

	sigAct.sa_handler = HandlerSIGTRAP;
	sigaction(SIGTRAP, &sigAct, NULL);

	sigAct.sa_handler = HandlerSIGSYS;
	sigaction(SIGSYS, &sigAct, NULL);
	
	sigAct.sa_handler = HandlerSIGPIPE;
	sigaction(SIGPIPE, &sigAct, NULL);
	
	sigAct.sa_handler = HandlerSIGURG;
	sigaction(SIGURG, &sigAct, NULL);
	
	sigAct.sa_handler = HandlerSIGALRM;
	sigaction(SIGALRM, &sigAct, NULL);
	
	sigAct.sa_handler = HandlerSIGPROF;
	sigaction(SIGPROF, &sigAct, NULL);
	
	sigAct.sa_handler = HandlerSIGEMT;
	sigaction(SIGEMT, &sigAct, NULL);

	sigfillset(&mask);
	sigprocmask(SIG_SETMASK, &mask, NULL);

	srand((unsigned)time(NULL));

	pthread_once(&ControleCle, initCle);
	pthread_once(&ControleMutex, initMutex);
	pthread_once(&ControleVarCond, initVarCond);

	pthread_mutex_init(&mutexTab, NULL);
	pthread_mutex_init(&mutexBilleBrique, NULL);
	pthread_mutex_init(&mutexScore, NULL);
	pthread_mutex_init(&mutexLetsGo, NULL);
	pthread_cond_init(&condBilleBrique, NULL);
	pthread_cond_init(&condBilleBrique, NULL);


	// Creation de thread Raquette
	pthread_create(&tidRaquette, NULL, (void*(*)(void*))fctThreadRaquette, &paramEff);
	// Creation de thread Event
	pthread_create(&tidEvent, NULL, (void*(*)(void*))fctThreadEvent, &paramEff);
	//Creation de thread Niveau
	pthread_create(&tidNiveau, NULL, (void*(*)(void*))fctThreadNiveau, NULL);
	//Creation de thread Score
	pthread_create(&tidScore, NULL, (void*(*)(void*))fctThreadScore, NULL);

	pthread_join(tidEvent, (void **)&retThread);

	// Fermeture de la fenetre
	printf("(THREAD MAIN %d) Fermeture de la fenetre graphique...",pthread_self()); fflush(stdout);
	FermetureFenetreGraphique();
	printf("OK\n"); fflush(stdout);

	//pthread_exit(NULL);
	exit(0);
}

//*********************************************************************************************
//Raquette

void *fctThreadRaquette(int *param)
{
	int i,j;
	sigset_t mask;
	S_RAQUETTE *raquette = (S_RAQUETTE*)malloc(sizeof(S_RAQUETTE)); /* Allocation dynamique de la raquette */

	pthread_setspecific(cleRaquette, raquette);

	sigfillset(&mask);
	sigdelset(&mask, SIGUSR1);
	sigdelset(&mask, SIGUSR2);
	sigdelset(&mask, SIGHUP);
	sigdelset(&mask, SIGINT);
	sigdelset(&mask, SIGPIPE);
	sigdelset(&mask, SIGSYS);
	sigdelset(&mask, SIGALRM);
	sigdelset(&mask, SIGPROF);
	sigprocmask(SIG_SETMASK, &mask, NULL);


	raquette->L = 19; /* Position de la raquette sur le tableau */
	raquette->C = 10;
	raquette->longueur = 5; /* Longueur par défaut de la raquette */
	raquette->billeSurRaquette = true; /* Bille sur raquette en début de niveau */

	pthread_mutex_lock(&mutexTab);
	tab[18][10] = BILLE;
	tab[19][8] = pthread_self();
	tab[19][9] = pthread_self();
	tab[19][10] = pthread_self();
	tab[19][11] = pthread_self();
	tab[19][12] = pthread_self();
	pthread_mutex_unlock(&mutexTab),

	DessineRaquette(raquette->L ,raquette->C , raquette->longueur);
	DessineBille(18,10,ROUGE);
	
	while(1)
		pause();

}

//*********************************************************************************************
//Event
void *fctThreadEvent(int *param)
{
	EVENT_GRILLE_SDL event;
	char ok;
	
	ok = 0;
	while(!ok)
	{
		event = ReadEvent();
		if (event.type == CROIX) ok = 1; /* Fin du programme */
		if (event.type == CLAVIER)
		{
			switch(event.touche)
			{
				case 'q' : /* Fin du programme */
					ok = 1;
					break;

				case KEY_RIGHT :
					pthread_kill(titadRaquette, SIGUSR2); /* Flèche droite */
					break;

				case KEY_LEFT :
					pthread_kill(tidRaquette, SIGUSR1); /* Flèche gauche */
					break;

				case KEY_SPACE :
					pthread_kill(tidRaquette, SIGHUP); /* Espace */
					break;
			}
		}
	}

	printf("Attente de 1500 millisecondes...\n");
	Attente(1500);

	printf("\nFin thread Event\n");
	pthread_exit(NULL);
}

//*********************************************************************************************
//Bille
void *fctThreadBille(S_BILLE *bille)
{

	sigset_t mask;
	
	pthread_setspecific(cleBille, bille);
	
	sigfillset(&mask);
	sigdelset(&mask, SIGEMT);
	sigprocmask(SIG_SETMASK, &mask, NULL);
	

	while(1)
	{
		if(!niveauFini)
		{
			switch(bille->dir) /* On vérifié la direction de la bille */
			{
				case NE : 

					if(tab[bille->L-1][bille->C] != VIDE) /* Si elle touche le haut du tableau */
					{
						bille->dir = SE;
						pthread_kill(tab[bille->L-1][bille->C], SIGTRAP);
					}
					else if(bille->C == NB_COLONNES-1) /* Si elle touche la droite du tableau */
						bille->dir = NO;
					else if(tab[bille->L][bille->C+1] != VIDE) /* Si elle touche quelque chose (brique/bonus) sur sa droite */
					{
						bille->dir = NO;
						pthread_kill(tab[bille->L][bille->C+1], SIGTRAP);
					}
					else if(tab[bille->L-1][bille->C+1] != VIDE) /* Si elle touche le haut droite du tableau */
					{
						bille->dir = SO;
						pthread_kill(tab[bille->L-1][bille->C+1], SIGTRAP);
					}
					else /* La bille ne touche strictement rien et continue son chemin */
					{
						EffaceCarre(bille->L ,bille->C); 

						pthread_mutex_lock(&mutexTab);
						tab[bille->L][bille->C] = 0;
						tab[bille->L-1][bille->C+1] = BILLE;
						pthread_mutex_unlock(&mutexTab);

						bille->L = bille->L-1;
						bille->C = bille->C+1;
						DessineBille(bille->L ,bille->C, bille->couleur);
						Attente(delaiBille); /* Vitesse de la bille */
					}
					break;

				case NO :

					if(tab[bille->L-1][bille->C] != VIDE)
					{
						bille->dir = SO;
						pthread_kill(tab[bille->L-1][bille->C], SIGTRAP);
					}
					else if(bille->C == 0)
						bille->dir = NE;
					else if(tab[bille->L][bille->C-1] != VIDE)
					{
						bille->dir = NE;
						pthread_kill(tab[bille->L][bille->C-1], SIGTRAP);
					}
					else if(tab[bille->L-1][bille->C-1] != VIDE)
					{
						bille->dir = SE;
					 	pthread_kill(tab[bille->L-1][bille->C-1], SIGTRAP);
					}
					else
					{
						EffaceCarre(bille->L ,bille->C);

						pthread_mutex_lock(&mutexTab);
						tab[bille->L][bille->C] = 0;
						tab[bille->L-1][bille->C-1] = BILLE;
						pthread_mutex_unlock(&mutexTab);

						bille->L = bille->L-1;
						bille->C = bille->C-1;
						DessineBille(bille->L ,bille->C, bille->couleur);
						Attente(delaiBille);
					}
					break;

				case SE :
					if(bille->L == NB_LIGNES-1)
					{
						EffaceCarre(bille->L ,bille->C);
						pthread_mutex_lock(&mutexTab);
						tab[bille->L][bille->C] = 0;
						pthread_mutex_unlock(&mutexTab);

						pthread_mutex_lock(&mutexBilleBrique);
						nbBilles--;
						pthread_mutex_unlock(&mutexBilleBrique);
						pthread_cond_signal(&condBilleBrique);
						pthread_exit(NULL);
					}
					else if(tab[bille->L+1][bille->C] != VIDE)
					{
						bille->dir = NE;
						pthread_kill(tab[bille->L+1][bille->C] , SIGTRAP);
					}
					else if(bille->C == NB_COLONNES-1)
						bille->dir = SO;

					else if(tab[bille->L][bille->C+1] != VIDE)
					{
						bille->dir = SO;
						pthread_kill(tab[bille->L][bille->C+1], SIGTRAP);
					}
					else if(tab[bille->L+1][bille->C+1] != VIDE)
					{
						bille->dir = NO;
						pthread_kill(tab[bille->L+1][bille->C+1], SIGTRAP);
					}
					else
					{
						EffaceCarre(bille->L ,bille->C);

						pthread_mutex_lock(&mutexTab);
						tab[bille->L][bille->C] = 0;
						tab[bille->L+1][bille->C+1] = BILLE;
						pthread_mutex_unlock(&mutexTab);

						bille->L = bille->L+1;
						bille->C = bille->C+1;
						DessineBille(bille->L ,bille->C, bille->couleur);
						Attente(delaiBille);
					}
					break;

				case SO :
					if(bille->L == NB_LIGNES-1)
					{
						EffaceCarre(bille->L ,bille->C);
						pthread_mutex_lock(&mutexTab);
						tab[bille->L][bille->C] = 0;
						pthread_mutex_unlock(&mutexTab);

						pthread_mutex_lock(&mutexBilleBrique);
						nbBilles--;
						pthread_mutex_unlock(&mutexBilleBrique);
						pthread_cond_signal(&condBilleBrique);
						pthread_exit(NULL);
					}
					else if(tab[bille->L+1][bille->C] != VIDE)
					{
						bille->dir = NO;
						pthread_kill(tab[bille->L+1][bille->C], SIGTRAP);
					}
					else if(bille->C == 0)
						bille->dir = SE;
					else if(tab[bille->L][bille->C-1] != VIDE)
					{
						bille->dir = SE;
						pthread_kill(tab[bille->L][bille->C-1], SIGTRAP);
					}
					else if(tab[bille->L+1][bille->C-1] != VIDE)
					{
						bille->dir = NE;
						pthread_kill(tab[bille->L+1][bille->C-1], SIGTRAP);
					}
					else
					{
						EffaceCarre(bille->L ,bille->C);

						pthread_mutex_lock(&mutexTab);
						tab[bille->L][bille->C] = 0;
						tab[bille->L+1][bille->C-1] = BILLE;
						pthread_mutex_unlock(&mutexTab);

						bille->L = bille->L+1;
						bille->C = bille->C-1;
						DessineBille(bille->L ,bille->C, bille->couleur);
						Attente(delaiBille);
					}
					break;
			}
		}
		else /* On perd la bille en bas du tableau */
		{
			EffaceCarre(bille->L ,bille->C);
			pthread_mutex_lock(&mutexTab);
			tab[bille->L][bille->C] = 0; /* DEFINE 0 -> VIDE */
			pthread_mutex_unlock(&mutexTab);

			//pthread_cleanup_pop(1);
			pthread_mutex_lock(&mutexBilleBrique);
			nbBilles--;
			pthread_mutex_unlock(&mutexBilleBrique);
			pthread_cond_signal(&condBilleBrique);
			pthread_exit(NULL);
		}
	}	
}

//*********************************************************************************************
//Brique
void *fctThreadBrique(S_BRIQUE *brique)
{
	
	sigset_t mask;

	pthread_cleanup_push(finThreadBrique,0);

	sigfillset(&mask);
	sigdelset(&mask, SIGTRAP);
	sigdelset(&mask, SIGURG);
	sigprocmask(SIG_SETMASK, &mask, NULL);

	pthread_setspecific(cleBrique, brique);

	pthread_mutex_lock(&mutexTab);
	tab[brique->L][brique->C] = tab[brique->L][brique->C+1] = pthread_self();
	pthread_mutex_unlock(&mutexTab);

	DessineBrique(brique->L, brique->C, brique->couleur, brique->brise);
	
	while(1)
		pause();

	pthread_cleanup_pop(1);
}
//*********************************************************************************************
//Niveau

void *fctThreadNiveau(void *p)
{
	int nbVie = 2, niveau = 1;
	int i, j, k;
	int ctrl = 0;
	int BriqueBonus[NB_BRIQUES];
	int CouleurBonus, CompteurMauve=10, CompteurJaune=5, CompteurVert=5, CompteurBombe=1;

	DessineDiamant(0, 9, ROUGE);
	DessineDiamant(0, 10, ROUGE);

	if (niveau < 10)
	{
		DessineChiffre(0, 3, 0);
		DessineChiffre(0, 4, niveau);	
	}

	while(1)
	{
		for (j=0;j<NB_BRIQUES; j++) /* On initialise un vecteur de NB_BRIQUES à 0*/
			BriqueBonus[j] = 0;
		j=0;
		while (j<21) /* On met 21 cases random à 1 */
		{
			k = rand() % 56;
			if (BriqueBonus[k] == 0)
			{
				BriqueBonus[k] = 1;	
				j++;		
			}

		}
		//Creation des threads Briques
		for(i=0; i<NB_BRIQUES; i++)
		{
			S_BRIQUE *iBrique = (S_BRIQUE*)malloc(sizeof(S_BRIQUE));
			memcpy(iBrique,&Briques[i],sizeof(S_BRIQUE));
			
			if (BriqueBonus[i] == 1) /* Si dans le vecteur la case est à 1, on insère un bonus */
			{
				CouleurBonus = rand() % 4; /* On choisit random le bonus (3 différents bonus) */
				if (CouleurBonus == 0 && CompteurMauve > 0) 
				{
					iBrique->bonus = MAUVE;
					CompteurMauve--; /* On décrémente le compteur pour n'avoir que le bon nombre de diamants de couleur MAUVE */ 
				}
				else
				{
					if (CouleurBonus == 1 && CompteurVert > 0)
					{
						iBrique->bonus = VERT;
						CompteurVert--; /* On décrémente le compteur pour n'avoir que le bon nombre de diamants de couleur VERT */ 
					}
					else
					{
						if (CouleurBonus == 2 && CompteurJaune > 0)
						{
							iBrique->bonus = JAUNE;
							CompteurJaune--; /* On décrémente le compteur pour n'avoir que le bon nombre de diamants de couleur JAUNE */ 
						}
						else
						{
							if (CouleurBonus == 3 && CompteurBombe > 0)
							{
								iBrique->bonus = BOMBE;
								CompteurBombe--; /* On décrémente le compteur pour la bombe */ 
							}
						}
					}
				}
			}
			pthread_create(&tidBrique, NULL, (void*(*)(void*))fctThreadBrique, iBrique); /* Création du thread BRIQUE */
		}

		nbBriques = NB_BRIQUES;
		nbBilles = 1;
		
		if(ctrl)
			pthread_kill(tidRaquette, SIGINT);
			

		niveauFini = false;
		
		while(!niveauFini)
		{
			
			pthread_mutex_lock(&mutexBilleBrique);
			while((nbBilles > 0) && (nbBriques > 0))
				pthread_cond_wait(&condBilleBrique, &mutexBilleBrique);
			pthread_mutex_unlock(&mutexBilleBrique);

			if(nbBilles == 0)
			{
				if(nbVie == 1)
				{
					DessineGameOver(9,6); /* Fin de la partie */
					pthread_exit(NULL);
				}
				else
				{
					nbVie--; /* Perte d'une bille dans le jeu donc vie décrémenté et bille remise à 1 */
					EffaceCarre(0, 9+nbVie);
					nbBilles = 1;
					kill(getpid(),SIGINT);
				}
			}
			if(nbBriques == 0 || letsgo == 1)
			{
				niveauFini = true; /* Fin du niveau */
				niveau++;
				
				if(niveau<10)
				{
					DessineChiffre(0, 4, niveau);
				}
				else if(niveau < 100)
				{
					DessineChiffre(0, 3, niveau/10);
					DessineChiffre(0, 4, niveau%10);
				}

				Attente(1000);
				delaiBille = delaiBille - delaiBille * 0.1; /* Augmentation de la vitesse de la bille */
				//printf("\nNiveau suivant");

			}
			ctrl = 1;
		}
	}
	
}
//*********************************************************************************************
//Bonus
void *fctThreadBonus(S_BONUS *bonus)
{
	printf ("Thread bonus demarre");
	fflush(stdout);
	int posBille = 0, raq = tidRaquette, CheckBillesurBille = 0, CheckBillesurRaquette = 0;
	int ctrl = 1;
	pthread_cleanup_push(finThreadBonus, bonus);

	pthread_mutex_lock(&mutexBilleBrique);
	while(tab[bonus->L][bonus->C] != 0)
		pthread_cond_wait(&condBilleBrique, &mutexBilleBrique);
	pthread_mutex_unlock(&mutexBilleBrique);
	//S_RAQUETTE * raquette = (S_RAQUETTE*)pthread_getspecific(cleRaquette);

	pthread_mutex_lock(&mutexTab);
	tab[bonus->L][bonus->C] = BONUS;
	pthread_mutex_unlock(&mutexTab);

	DessineDiamant(bonus->L, bonus->C, bonus->couleur);
	
	Attente(delaiBille);

	while(1)
	{	
		if(bonus->L == NB_LIGNES-1 || niveauFini) //Bonus quitte la zone de jeu
			pthread_exit(NULL);
		
		if(tab[bonus->L+1][bonus->C] != BILLE && tab[bonus->L+1][bonus->C] != BONUS)
		{
			if(posBille > tidRaquette)
				CheckBillesurBille = posBille;
			
			if(tab[bonus->L+1][bonus->C] != tidRaquette)
			{
				EffaceCarre(bonus->L, bonus->C);
			
				pthread_mutex_lock(&mutexTab);
				tab[bonus->L][bonus->C] = 0;
				posBille = tab[bonus->L+1][bonus->C];
				tab[bonus->L+1][bonus->C] = BONUS;
				pthread_mutex_unlock(&mutexTab);
		
				bonus->L++;
				 
				DessineDiamant(bonus->L, bonus->C, bonus->couleur);
			}
			else
				CheckBillesurRaquette = tidRaquette;
			
		}
		if(CheckBillesurRaquette == tidRaquette)
		{
			CheckBillesurRaquette = 0;
			if(bonus->couleur == VERT)
				pthread_kill(tidRaquette, SIGSYS);
			if(bonus->couleur == JAUNE)
				pthread_kill(tidRaquette, SIGPIPE);
			if(bonus->couleur == BOMBE)
				pthread_kill(tidRaquette, SIGPROF);
			if(bonus->couleur == MAUVE)
				kill(getpid(), SIGEMT);
		
			pthread_mutex_lock(&mutexScore);
			MAJScore = true;
			score++;
			pthread_mutex_unlock(&mutexScore);
			pthread_cond_signal(&condScore);

	
			pthread_exit(NULL);
		}
		
		if(CheckBillesurBille != 0)
		{
			pthread_kill(CheckBillesurBille, SIGURG);
			CheckBillesurBille = 0;
		}
		
		Attente(delaiBille);
	}

	
	pthread_cleanup_pop(1);
	
	/*while(1)
		pause();*/
}

//*********************************************************************************************
//Score
void *fctThreadScore(void *p)
{
	DessineChiffre(0, 16, 0);
	DessineChiffre(0, 17, 0);
	DessineChiffre(0, 18, 0);
	DessineChiffre(0, 19, 0);
	while(1)
	{
		pthread_mutex_lock(&mutexScore);
		while(!MAJScore)
			pthread_cond_wait(&condScore, &mutexScore);
		pthread_mutex_unlock(&mutexScore);
		
		//Dessiner le chiffre
		if(score < 10) /* On check pour une question d'interface graphique */
		{
			DessineChiffre(0, 19, score);
		}
		else if(score < 100)
		{
			DessineChiffre(0, 18, score/10);
			DessineChiffre(0, 19, score%10);
		}
		else if(score < 1000)
		{
			DessineChiffre(0, 17, score/100);
			DessineChiffre(0, 18, (score%100) /10);
			DessineChiffre(0, 19, (score%100) %10);
		}
		else if(score < 10000)
		{
			DessineChiffre(0, 16, score/1000);
			DessineChiffre(0, 17, (score%1000)/100);
			DessineChiffre(0, 18, ((score%1000)%100) /10);
			DessineChiffre(0, 19, ((score%1000)%100) %10);
		}
		MAJScore = false;
	}
}

//*********************************************************************************************
//Handler
/* Signal de la raquette */
void HandlerSIGINT (int sig)
{
	//S_RAQUETTE *raquette = (S_RAQUETTE*)malloc(sizeof(S_RAQUETTE));

	S_RAQUETTE * raquette = (S_RAQUETTE*)pthread_getspecific(cleRaquette);

	
	switch(raquette->longueur) //Supprime le tab selon la taille de la raquette
	{
		case 3 : /* Longueur de la raquette : 3*/
			EffaceCarre(19, raquette->C-1);
			EffaceCarre(19, raquette->C);
			EffaceCarre(19, raquette->C+1);

			pthread_mutex_lock(&mutexTab);
			tab[19][raquette->C-1] = 0;
			tab[19][raquette->C] = 0;
			tab[19][raquette->C+1] = 0;
			pthread_mutex_unlock(&mutexTab);
			break;

		case 5 : /* Longueur de la raquette : 5*/
			EffaceCarre(19, raquette->C-2);
			EffaceCarre(19, raquette->C-1);
			EffaceCarre(19, raquette->C);
			EffaceCarre(19, raquette->C+1);
			EffaceCarre(19, raquette->C+2);

			pthread_mutex_lock(&mutexTab);
			tab[19][raquette->C-2] = 0;
			tab[19][raquette->C-1] = 0;
			tab[19][raquette->C] = 0;
			tab[19][raquette->C+1] = 0;
			tab[19][raquette->C+2] = 0;
			pthread_mutex_unlock(&mutexTab);
			break;

		case 7 : /* Longueur de la raquette : 7*/
			EffaceCarre(19, raquette->C-3);
			EffaceCarre(19, raquette->C-2);
			EffaceCarre(19, raquette->C-1);
			EffaceCarre(19, raquette->C);
			EffaceCarre(19, raquette->C+1);
			EffaceCarre(19, raquette->C+2);
			EffaceCarre(19, raquette->C+3);

			pthread_mutex_lock(&mutexTab);
			tab[19][raquette->C-3] = 0;
			tab[19][raquette->C-2] = 0;
			tab[19][raquette->C-1] = 0;
			tab[19][raquette->C] = 0;
			tab[19][raquette->C+1] = 0;
			tab[19][raquette->C+2] = 0;
			tab[19][raquette->C+3] = 0;
			pthread_mutex_unlock(&mutexTab);
			break;
	}

	raquette->L = 19;
	raquette->C = 10;
	raquette->longueur = 5;
	raquette->billeSurRaquette = true;

	pthread_mutex_lock(&mutexTab);
	tab[18][10] = BILLE;
	tab[19][8] = pthread_self();
	tab[19][9] = pthread_self();
	tab[19][10] = pthread_self();
	tab[19][11] = pthread_self();
	tab[19][12] = pthread_self();
	pthread_mutex_unlock(&mutexTab),


	DessineRaquette(raquette->L ,raquette->C , raquette->longueur); /* Début de niveau */
	DessineBille(18,10,ROUGE);
	
}


void HandlerSIGUSR1 (int sig) /* Déplacement de la raquette à gauche */
{
	S_RAQUETTE *raquette = (S_RAQUETTE*)malloc(sizeof(S_RAQUETTE));

	raquette = (S_RAQUETTE*)pthread_getspecific(cleRaquette);

	switch(raquette->longueur)
	{
		case 3 :
			if(raquette->C > 1)
			{
				EffaceCarre(raquette->L, raquette->C+1);

				pthread_mutex_lock(&mutexTab);
				tab[raquette->L][raquette->C+1] = 0;
				tab[raquette->L][raquette->C-2] = pthread_self();
				pthread_mutex_unlock(&mutexTab);

				raquette->C = raquette->C - 1;

			}
			break;

		case 5 :
			if(raquette->C > 2)
			{
				if(raquette->billeSurRaquette)
				{
					EffaceCarre(raquette->L -1, raquette->C);

					pthread_mutex_lock(&mutexTab);
					tab[raquette->L -1][raquette->C] = VIDE;
					tab[raquette->L -1][raquette->C-1] = BILLE;
					pthread_mutex_unlock(&mutexTab);

					DessineBille(raquette->L -1, raquette->C-1, ROUGE);

				}
				EffaceCarre(raquette->L, raquette->C+2);

				pthread_mutex_lock(&mutexTab);
				tab[raquette->L][raquette->C+2] = VIDE;
				tab[raquette->L][raquette->C-3] = pthread_self();
				pthread_mutex_unlock(&mutexTab);

				raquette->C = raquette->C - 1;
			}
			break;
		case 7 :
			if(raquette->C > 3)
			{
				EffaceCarre(raquette->L, raquette->C+3);

				pthread_mutex_lock(&mutexTab);
				tab[raquette->L][raquette->C+3] = 0;
				tab[raquette->L][raquette->C-4] = pthread_self();
				pthread_mutex_unlock(&mutexTab);

				raquette->C = raquette->C - 1;
			}
			break;

	}
	DessineRaquette(raquette->L ,raquette->C , raquette->longueur);
}

void HandlerSIGUSR2 (int sig) /* Déplacement de la raquette à droite */
{
	S_RAQUETTE *raquette = (S_RAQUETTE*)malloc(sizeof(S_RAQUETTE));

	raquette = (S_RAQUETTE*)pthread_getspecific(cleRaquette);

	switch(raquette->longueur)
	{
		case 3 :
			if(raquette->C < 18)
			{
				EffaceCarre(raquette->L, raquette->C-1);

				pthread_mutex_lock(&mutexTab);
				tab[raquette->L][raquette->C-1] = 0;
				tab[raquette->L][raquette->C+2] = pthread_self();
				pthread_mutex_unlock(&mutexTab);

				raquette->C = raquette->C + 1;
			}
			break;

		case 5 :
			if(raquette->C < 17)
			{
				if(raquette->billeSurRaquette)
				{
					EffaceCarre(raquette->L -1, raquette->C);

					pthread_mutex_lock(&mutexTab);
					tab[raquette->L -1][raquette->C] = 0;
					tab[raquette->L -1][raquette->C+1] = BILLE;
					pthread_mutex_unlock(&mutexTab);

					DessineBille(raquette->L -1, raquette->C+1, ROUGE);
				}
				EffaceCarre(raquette->L, raquette->C-2);

				pthread_mutex_lock(&mutexTab);
				tab[raquette->L][raquette->C-2] = 0;
				tab[raquette->L][raquette->C+3] = pthread_self();
				pthread_mutex_unlock(&mutexTab);

				raquette->C = raquette->C + 1;
			}
			break;
		case 7 :
			if(raquette->C < 16)
			{
				EffaceCarre(raquette->L, raquette->C-3);

				pthread_mutex_lock(&mutexTab);
				tab[raquette->L][raquette->C-3] = 0;
				tab[raquette->L][raquette->C+4] = pthread_self();
				pthread_mutex_unlock(&mutexTab);

				raquette->C = raquette->C + 1;
			}
			break;

	}
	DessineRaquette(raquette->L ,raquette->C , raquette->longueur);
}

void HandlerSIGHUP(int sig) /* La raquette lance la bille qui est collé à elle */
{
	int a;
	S_BILLE *bille = (S_BILLE*)malloc(sizeof(S_BILLE));
	S_RAQUETTE *raquette = (S_RAQUETTE*)malloc(sizeof(S_RAQUETTE));

	raquette = (S_RAQUETTE*)pthread_getspecific(cleRaquette);

	if(raquette->billeSurRaquette)
	{
		bille->L = raquette->L-1;
		bille->C = raquette->C;
		a = rand() % 2;
		
		if (a == 0)
			bille->dir = NE;
		else
			bille->dir = NO;
		bille->couleur = ROUGE;

		raquette->billeSurRaquette = false;

		pthread_create(&tidBille, NULL, (void*(*)(void*))fctThreadBille, bille);
	}

}

void HandlerSIGTRAP(int sig) /* Quand la bille touche une brique */
{
	int Aleatoire;
	
	S_BRIQUE *briqueCle = (S_BRIQUE *) malloc(sizeof(S_BRIQUE));
	briqueCle = (S_BRIQUE*)pthread_getspecific(cleBrique);
	
	pthread_mutex_lock(&mutexScore);
	MAJScore = true;
	score++;
	pthread_mutex_unlock(&mutexScore);
	pthread_cond_signal(&condScore);
	
	if(briqueCle->nbTouches == 1) /* Si c'est une simple brique */
	{
		EffaceCarre(briqueCle->L, briqueCle->C);
		EffaceCarre(briqueCle->L, briqueCle->C+1);
		
		pthread_mutex_lock(&mutexTab);
		tab[briqueCle->L][briqueCle->C] = VIDE;
		tab[briqueCle->L][briqueCle->C+1] = VIDE;
		pthread_mutex_unlock(&mutexTab);
		
		if (briqueCle->bonus != 0)
		{
			printf ("Brique simple avec bonus");
			fflush (stdout);
			S_BONUS *bonus = (S_BONUS *)malloc(sizeof(S_BONUS));
			Aleatoire = rand() % 2; /* Pour savoir si le bonus tombe à gauche ou à droite de la case brique */
			bonus->L = briqueCle->L;
			bonus->couleur = briqueCle->bonus;
			if (Aleatoire == 0)
				bonus->C = briqueCle->C; /* à gauche */		
			else
				bonus->C = briqueCle->C+1; /* à droite */		

		
			pthread_create(&tidBonus, NULL, (void*(*)(void*))fctThreadBonus, bonus);		
		}
		pthread_exit(NULL);

	}
	else
	{
		briqueCle->nbTouches--;
		EffaceCarre(briqueCle->L, briqueCle->C);
		EffaceCarre(briqueCle->L, briqueCle->C+1);
		briqueCle->brise = 1;
		DessineBrique(briqueCle->L,briqueCle->C,briqueCle->couleur,briqueCle->brise);
	}
	
}


void HandlerSIGURG(int sig) /* La brique doit se redessiner suite au passage du bonus */
{
	S_BRIQUE *brique = (S_BRIQUE *) pthread_getspecific(cleBrique);
	
	brique = (S_BRIQUE *)pthread_getspecific(cleBrique);
	pthread_mutex_lock(&mutexTab);
	if (tab[brique->L][brique->C] > 0)
	{
		tab[brique->L][brique->C+1] =  tab[brique->L][brique->C];
	}
	if (tab[brique->L][brique->C+1] > 0)
	{
		tab[brique->L][brique->C] =  tab[brique->L][brique->C+1];
	}
	pthread_mutex_unlock(&mutexTab);
	
	DessineBrique(brique->L,brique->C,brique->couleur,brique->brise);
}

void HandlerSIGPROF(int sig) /* La bombe detruit toutes les briques */
{
	printf ("DEMARRAGE GROSSE BOMBE OMG");+
	fflush(stdout);
	pthread_mutex_lock(&mutexLetsGo);
	letsgo = 1;
	pthread_mutex_unlock(&mutexLetsGo);
}
void HandlerSIGSYS(int sig) /* La raquette retrecit */
{
	S_RAQUETTE *raquette = (S_RAQUETTE*)malloc(sizeof(S_RAQUETTE));
	
	raquette = (S_RAQUETTE*)pthread_getspecific(cleRaquette);
	

	if(raquette->longueur != 5) //Si la raquette est de longueur 3 OU 7
	{
		alarm(0);
		pthread_kill(tidRaquette, SIGALRM);
		
		pthread_mutex_lock(&mutexRaquetteLong);
		while(raquette->longueur != 5)
			pthread_cond_wait(&condRaquetteLong, &mutexRaquetteLong);
		pthread_mutex_unlock(&mutexRaquetteLong);
	}


	pthread_mutex_lock(&mutexTab);
	tab[raquette->L][raquette->C+2] = 0;
	tab[raquette->L][raquette->C-2] = 0;
	pthread_mutex_unlock(&mutexTab);
	
	EffaceCarre(raquette->L, raquette->C+2);
	EffaceCarre(raquette->L, raquette->C-2);
	
	raquette->longueur = 3;
	DessineRaquette(raquette->L ,raquette->C , raquette->longueur);
	
	alarm(15);
}
void HandlerSIGPIPE(int sig) /* La raquette s'allonge */
{
	int i, a, b;
	S_RAQUETTE *raquette = (S_RAQUETTE*)malloc(sizeof(S_RAQUETTE));
	
	raquette = (S_RAQUETTE*)pthread_getspecific(cleRaquette);
	
	if(raquette->longueur != 5)
	{
		alarm(0);
		pthread_kill(tidRaquette, SIGALRM);
		
		pthread_mutex_lock(&mutexRaquetteLong);
		while(raquette->longueur != 5)
			pthread_cond_wait(&condRaquetteLong, &mutexRaquetteLong);
		pthread_mutex_unlock(&mutexRaquetteLong);
	}

	
	if(raquette->C >= 3 && raquette->C <= 16)
	{
		while(tab[raquette->L][raquette->C+3]  != 0 || tab[raquette->L][raquette->C-3] != 0)
			Attente(20);
			
		pthread_mutex_lock(&mutexTab);
		tab[raquette->L][raquette->C+3] = tidRaquette;
		tab[raquette->L][raquette->C-3] = tidRaquette;
		pthread_mutex_unlock(&mutexTab);
	}
		
	if(raquette->C < 3)
	{
		while(tab[raquette->L][raquette->C+3] != 0 || tab[raquette->L][raquette->C+4] != 0)
			Attente(20);
			
		raquette->C = 3;
		pthread_mutex_lock(&mutexTab);
		tab[raquette->L][raquette->C+2] = tidRaquette;
		tab[raquette->L][raquette->C+3] = tidRaquette;
		pthread_mutex_unlock(&mutexTab);
	}
		
	
	if(raquette->C > 16)
	{
		while(tab[raquette->L][raquette->C-3]  != 0 || tab[raquette->L][raquette->C-4] != 0)
			Attente(20);
			
		raquette->C = 16;
		pthread_mutex_lock(&mutexTab);
		tab[raquette->L][raquette->C-2] = tidRaquette;
		tab[raquette->L][raquette->C-3] = tidRaquette;
		pthread_mutex_unlock(&mutexTab);
	}
	
	raquette->longueur = 7;
	DessineRaquette(raquette->L ,raquette->C , raquette->longueur);
	alarm(15);
}
void HandlerSIGEMT(int sig) /* Deux nouvelles billes en + */
{
	printf ("DEMARRAGE PLUSIEURS BILLES");
	fflush(stdout);
	
	S_BILLE *bille = (S_BILLE *) malloc(sizeof(S_BILLE));
	
	S_BILLE *billeA = (S_BILLE*)malloc(sizeof(S_BILLE));
	S_BILLE *billeB = (S_BILLE*)malloc(sizeof(S_BILLE));
	
	bille = (S_BILLE*)pthread_getspecific(cleBille);
	
	billeA->L = billeB->L = bille->L;
	billeA->C = billeB->C = bille->C;
	
	switch(bille->dir)
	{
		case NE:
			billeA->dir = NO;
			billeB->dir = SE;
			break;
			
		case SE:
			billeA->dir = NE;
			billeB->dir = SO;
			break;
			
		case SO:
			billeA->dir = NO;
			billeB->dir = SE;
			break;
			
		case NO:
			billeA->dir = NE;
			billeB->dir = SO;
			break;
	}
	
	billeA->couleur = ROUGE;
	billeB->couleur = ROUGE;
	
	pthread_mutex_lock(&mutexBilleBrique);
	nbBilles+=2;
	pthread_mutex_unlock(&mutexBilleBrique);
	
	pthread_create(&tidBille, NULL, (void*(*)(void*))fctThreadBille, billeA);
	pthread_create(&tidBille, NULL, (void*(*)(void*))fctThreadBille, billeB);
	
}
void HandlerSIGALRM(int sig) /* La raquette reprend sa longueur initial */
{
	S_RAQUETTE *raquette = (S_RAQUETTE*)malloc(sizeof(S_RAQUETTE));
	
	raquette = (S_RAQUETTE*)pthread_getspecific(cleRaquette);
	

	if(raquette->longueur == 3) //Si la longueur vaut 3
	{
			if(raquette->C >= 2 && raquette->C <= 17) //Si après début du tab & avant fin du tab
			{
				while(tab[raquette->L][raquette->C+2]  != 0 || tab[raquette->L][raquette->C-2] != 0)
				Attente(20);
				pthread_mutex_lock(&mutexTab);
				tab[raquette->L][raquette->C+2] = tidRaquette;
				tab[raquette->L][raquette->C-2] = tidRaquette;
				pthread_mutex_unlock(&mutexTab);
			}
			
			if(raquette->C < 2) //Si extrémité du tab à gauche 
			{
				while(tab[raquette->L][raquette->C+2]  != 0 || tab[raquette->L][raquette->C+3] != 0)
					Attente(20);
					
				raquette->C = 2;
				pthread_mutex_lock(&mutexTab);
				tab[raquette->L][raquette->C+1] = tidRaquette;
				tab[raquette->L][raquette->C+2] = tidRaquette;
				pthread_mutex_unlock(&mutexTab);
			}
		
	
			if(raquette->C > 17) //Si extrémité du tab à droite
			{
				while(tab[raquette->L][raquette->C-2]  != 0 || tab[raquette->L][raquette->C-3] != 0)
					Attente(20);
					
				raquette->C = 17;
				pthread_mutex_lock(&mutexTab);
				tab[raquette->L][raquette->C-1] = tidRaquette;
				tab[raquette->L][raquette->C-2] = tidRaquette;
				pthread_mutex_unlock(&mutexTab);
			}
		pthread_mutex_lock(&mutexRaquetteLong);
		raquette->longueur = 5;
		pthread_mutex_unlock(&mutexRaquetteLong);
		pthread_cond_signal(&condRaquetteLong);
		DessineRaquette(raquette->L ,raquette->C , raquette->longueur);
	}
	
	if(raquette->longueur == 7) //Si la longueur vaut 7
	{
		pthread_mutex_lock(&mutexTab);
		tab[raquette->L][raquette->C+3] = 0;
		tab[raquette->L][raquette->C-3] = 0;
		pthread_mutex_unlock(&mutexTab);
		
		EffaceCarre(raquette->L, raquette->C+3);
		EffaceCarre(raquette->L, raquette->C-3);
		
		pthread_mutex_lock(&mutexRaquetteLong);
		raquette->longueur = 5;
		pthread_mutex_unlock(&mutexRaquetteLong);
		pthread_cond_signal(&condRaquetteLong);
		DessineRaquette(raquette->L ,raquette->C , raquette->longueur);
	}	
}

//*********************************************************************************************
void Attente(int milli)
{
	struct timespec delai;
	delai.tv_sec = milli/1000;
	delai.tv_nsec = (milli%1000)*1000000;
	nanosleep(&delai,NULL);
}

//*********************************************************************************************
//Initialisation des clés
void initCle()
{
	//puts("===initialisation des clés===");
	pthread_key_create(&cleRaquette, destructeur);
	pthread_key_create(&cleBille, destructeur);
	pthread_key_create(&cleBrique, destructeur);
}
//Initialisation  des mutex
void initMutex()
{
	//puts("\n===initialisation des mutex===");
	pthread_mutex_init(&mutexTab, NULL);
	pthread_mutex_init(&mutexBilleBrique, NULL);
	pthread_mutex_init(&mutexScore, NULL);
	pthread_mutex_init(&mutexRaquetteLong, NULL);
}
//Initialisation des Variables de conditions
void initVarCond()
{
	//puts("\n===initialisation des variables condition===");
	pthread_cond_init(&condBilleBrique, NULL);
	pthread_cond_init(&condBilleBrique, NULL);
	pthread_cond_init(&condRaquetteLong, NULL);
}
void destructeur(void *p)
{
	//puts("===liberation d'une zone specifique===");
	free(p);
}


void finThreadBille(void *p)
{
	pthread_mutex_lock(&mutexBilleBrique);
	nbBilles--;
	pthread_mutex_unlock(&mutexBilleBrique);
	pthread_cond_signal(&condBilleBrique);
}

void finThreadBrique(void *p)
{
	pthread_mutex_lock(&mutexBilleBrique);
	nbBriques--;
	pthread_mutex_unlock(&mutexBilleBrique);
	pthread_cond_signal(&condBilleBrique);
}
void finThreadBonus(S_BONUS *bonus)
{
	EffaceCarre(bonus->L, bonus->C);
			
	pthread_mutex_lock(&mutexTab);
	tab[bonus->L][bonus->C] = 0;
	pthread_mutex_unlock(&mutexTab);
}

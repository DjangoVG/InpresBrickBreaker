#ifndef RESSOURCES_H
#define RESSOURCES_H

// Macros pour les couleurs de bille
#define GRIS                      400000
#define ROUGE                     400001
#define BLEU                      400002
#define JAUNE                     400003
#define MAUVE                     400004
#define VERT                      400005
#define BOMBE			  400007
#define TURQUOISE                 400006

int  OuvertureFenetreGraphique();
int  FermetureFenetreGraphique();
void DessineMur(int l,int c);
void DessineBille(int l,int c,int couleur);
void DessineBrique(int l,int c,int couleur,char brise);  
  // (l,c) coordonnees de la case gauche de la brique
  // si brise == 0 --> brique non brisee
  // si brise == 1 --> brique brisee
void DessineDiamant(int l,int c,int couleur);
void DessineRaquette(int l,int c,int taille); 
  // (l,c) coordonnees du centre de la raquette
  // taille = 3, 5 ou 7
void DessineChiffre(int l,int c,int val);
void DessineGameOver(int l,int c);

#endif

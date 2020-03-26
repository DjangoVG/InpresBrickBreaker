#include "Ressources.h"
#include "GrilleSDL.h"

// Macros pour les sprites
#define S_MUR                      300000

#define S_BILLE_GRISE              300001
#define S_BILLE_ROUGE              300002
#define S_BILLE_BLEUE              300003
#define S_BILLE_JAUNE              300004
#define S_BILLE_TURQUOISE          300005
#define S_BILLE_VERTE              300006
#define S_BILLE_MAUVE              300007

#define S_BRIQUE_GRISE             300008
#define S_BRIQUE_ROUGE             300009
#define S_BRIQUE_BLEUE             300010
#define S_BRIQUE_JAUNE             300011
#define S_BRIQUE_TURQUOISE         300012
#define S_BRIQUE_VERTE             300013
#define S_BRIQUE_MAUVE             300014

#define S_DIAMANT_JAUNE            300015
#define S_DIAMANT_ROUGE            300016
#define S_DIAMANT_VERT             300017
#define S_DIAMANT_MAUVE            300018
#define S_BOMBE	                   300041
    
#define S_RAQUETTE_3               300019
#define S_RAQUETTE_5               300020
#define S_RAQUETTE_7               300021

#define S_BRIQUE_GRISE_BRISEE      300022
#define S_BRIQUE_ROUGE_BRISEE      300023
#define S_BRIQUE_BLEUE_BRISEE      300024
#define S_BRIQUE_JAUNE_BRISEE      300025
#define S_BRIQUE_TURQUOISE_BRISEE  300026
#define S_BRIQUE_VERTE_BRISEE      300027
#define S_BRIQUE_MAUVE_BRISEE      300028

#define S_CHIFFRE_0                300030
#define S_CHIFFRE_1                300031
#define S_CHIFFRE_2                300032
#define S_CHIFFRE_3                300033
#define S_CHIFFRE_4                300034
#define S_CHIFFRE_5                300035
#define S_CHIFFRE_6                300036
#define S_CHIFFRE_7                300037
#define S_CHIFFRE_8                300038
#define S_CHIFFRE_9                300039

#define S_GAMEOVER                 300040

void ChargementImages()
{
  // Definition de l'image de fond
  DessineImageFond("./images/Fond_21x20.bmp");

  // Sprites
  AjouteSprite(S_MUR,"./images/Mur32.bmp");

  AjouteSpriteAFondTransparent(S_BILLE_GRISE,"./images/BilleGrise32.bmp",255,255,255);
  AjouteSpriteAFondTransparent(S_BILLE_ROUGE,"./images/BilleRouge32.bmp",255,255,255);
  AjouteSpriteAFondTransparent(S_BILLE_BLEUE,"./images/BilleBleue32.bmp",255,255,255);
  AjouteSpriteAFondTransparent(S_BILLE_JAUNE,"./images/BilleJaune32.bmp",255,255,255);
  AjouteSpriteAFondTransparent(S_BILLE_MAUVE,"./images/BilleMauve32.bmp",255,255,255);
  AjouteSpriteAFondTransparent(S_BILLE_VERTE,"./images/BilleVerte32.bmp",255,255,255);
  AjouteSpriteAFondTransparent(S_BILLE_TURQUOISE,"./images/BilleMagenta32.bmp",255,255,255);

  AjouteSpriteAFondTransparent(S_BRIQUE_GRISE,"./images/briqueGrise.bmp",255,255,255);
  AjouteSpriteAFondTransparent(S_BRIQUE_ROUGE,"./images/briqueRouge.bmp",255,255,255);
  AjouteSpriteAFondTransparent(S_BRIQUE_BLEUE,"./images/briqueBleue.bmp",255,255,255);
  AjouteSpriteAFondTransparent(S_BRIQUE_JAUNE,"./images/briqueJaune.bmp",255,255,255);
  AjouteSpriteAFondTransparent(S_BRIQUE_MAUVE,"./images/briqueViolette.bmp",255,255,255);
  AjouteSpriteAFondTransparent(S_BRIQUE_VERTE,"./images/briqueVerte.bmp",255,255,255);
  AjouteSpriteAFondTransparent(S_BRIQUE_TURQUOISE,"./images/briqueTurquoise.bmp",255,255,255);

  AjouteSpriteAFondTransparent(S_BRIQUE_GRISE_BRISEE,"./images/briqueGriseBrisee.bmp",255,255,255);
  AjouteSpriteAFondTransparent(S_BRIQUE_ROUGE_BRISEE,"./images/briqueRougeBrisee.bmp",255,255,255);
  AjouteSpriteAFondTransparent(S_BRIQUE_BLEUE_BRISEE,"./images/briqueBleueBrisee.bmp",255,255,255);
  AjouteSpriteAFondTransparent(S_BRIQUE_JAUNE_BRISEE,"./images/briqueJauneBrisee.bmp",255,255,255);
  AjouteSpriteAFondTransparent(S_BRIQUE_MAUVE_BRISEE,"./images/briqueVioletteBrisee.bmp",255,255,255);
  AjouteSpriteAFondTransparent(S_BRIQUE_VERTE_BRISEE,"./images/briqueVerteBrisee.bmp",255,255,255);
  AjouteSpriteAFondTransparent(S_BRIQUE_TURQUOISE_BRISEE,"./images/briqueTurquoiseBrisee.bmp",255,255,255);

  AjouteSpriteAFondTransparent(S_DIAMANT_JAUNE,"./images/diamantJaune.bmp",255,255,255);
  AjouteSpriteAFondTransparent(S_DIAMANT_ROUGE,"./images/diamantRouge.bmp",255,255,255);
  AjouteSpriteAFondTransparent(S_DIAMANT_VERT,"./images/diamantVert.bmp",255,255,255);
  AjouteSpriteAFondTransparent(S_DIAMANT_MAUVE,"./images/diamantViolet.bmp",255,255,255);
  AjouteSpriteAFondTransparent(S_BOMBE,"./images/Bombe.bmp",255,255,255);

  AjouteSprite(S_RAQUETTE_3,"./images/Raquette3.bmp");
  AjouteSprite(S_RAQUETTE_5,"./images/Raquette5.bmp");
  AjouteSprite(S_RAQUETTE_7,"./images/Raquette7.bmp"); 

  AjouteSprite(S_CHIFFRE_0,"./images/Zero32.bmp");
  AjouteSprite(S_CHIFFRE_1,"./images/Un32.bmp");
  AjouteSprite(S_CHIFFRE_2,"./images/Deux32.bmp");
  AjouteSprite(S_CHIFFRE_3,"./images/Trois32.bmp");
  AjouteSprite(S_CHIFFRE_4,"./images/Quatre32.bmp");
  AjouteSprite(S_CHIFFRE_5,"./images/Cinq32.bmp");
  AjouteSprite(S_CHIFFRE_6,"./images/Six32.bmp");
  AjouteSprite(S_CHIFFRE_7,"./images/Sept32.bmp");
  AjouteSprite(S_CHIFFRE_8,"./images/Huit32.bmp");
  AjouteSprite(S_CHIFFRE_9,"./images/Neuf32.bmp");  

  AjouteSpriteAFondTransparent(S_GAMEOVER,"./images/GameOver.bmp",255,255,255);
}

// Fonctions Ressources
int OuvertureFenetreGraphique()
{
  if (OuvrirGrilleSDL(21,20,32,"!!! CASSE BRIQUES !!!","./images/iconeFenetre256.bmp") < 0)
    return -1;
 
  ChargementImages();
  return 0;
}

int FermetureFenetreGraphique()
{
  FermerGrilleSDL();
  return 0;
}

void DessineMur(int l,int c)
{
  DessineSprite(l,c,S_MUR);
}

void DessineBille(int l,int c,int couleur)
{
  switch(couleur)
  {
    case GRIS      : DessineSprite(l,c,S_BILLE_GRISE); break;
    case ROUGE     : DessineSprite(l,c,S_BILLE_ROUGE); break;
    case BLEU      : DessineSprite(l,c,S_BILLE_BLEUE); break;
    case JAUNE     : DessineSprite(l,c,S_BILLE_JAUNE); break;
    case MAUVE     : DessineSprite(l,c,S_BILLE_MAUVE); break;
    case VERT      : DessineSprite(l,c,S_BILLE_VERTE); break;
    case TURQUOISE : DessineSprite(l,c,S_BILLE_TURQUOISE); break;
    default        : DessineSprite(l,c,S_BILLE_GRISE); break;    
  }
}

void DessineBrique(int l,int c,int couleur,char brise)
{
  if (!brise)
  {
    switch(couleur)
    {
      case GRIS      : DessineSprite(l,c,S_BRIQUE_GRISE); break;
      case ROUGE     : DessineSprite(l,c,S_BRIQUE_ROUGE); break;
      case BLEU      : DessineSprite(l,c,S_BRIQUE_BLEUE); break;
      case JAUNE     : DessineSprite(l,c,S_BRIQUE_JAUNE); break;
      case MAUVE     : DessineSprite(l,c,S_BRIQUE_MAUVE); break;
      case VERT      : DessineSprite(l,c,S_BRIQUE_VERTE); break;
      case TURQUOISE : DessineSprite(l,c,S_BRIQUE_TURQUOISE); break;
      default        : DessineSprite(l,c,S_BRIQUE_GRISE); break;    
    }
    return;
  }
  switch(couleur)
  {
    case GRIS      : DessineSprite(l,c,S_BRIQUE_GRISE_BRISEE); break;
    case ROUGE     : DessineSprite(l,c,S_BRIQUE_ROUGE_BRISEE); break;
    case BLEU      : DessineSprite(l,c,S_BRIQUE_BLEUE_BRISEE); break;
    case JAUNE     : DessineSprite(l,c,S_BRIQUE_JAUNE_BRISEE); break;
    case MAUVE     : DessineSprite(l,c,S_BRIQUE_MAUVE_BRISEE); break;
    case VERT      : DessineSprite(l,c,S_BRIQUE_VERTE_BRISEE); break;
    case TURQUOISE : DessineSprite(l,c,S_BRIQUE_TURQUOISE_BRISEE); break;
    default        : DessineSprite(l,c,S_BRIQUE_GRISE_BRISEE); break;    
  }
}

void DessineDiamant(int l,int c,int couleur)
{
  switch(couleur)
  {
    case ROUGE  : DessineSprite(l,c,S_DIAMANT_ROUGE); break;
    case JAUNE  : DessineSprite(l,c,S_DIAMANT_JAUNE); break;
    case VERT   : DessineSprite(l,c,S_DIAMANT_VERT); break;
    case MAUVE  : DessineSprite(l,c,S_DIAMANT_MAUVE); break;
    case BOMBE  : DessineSprite(l,c,S_BOMBE); break;
    default     : DessineSprite(l,c,S_DIAMANT_ROUGE); break;    
  }
}

void DessineRaquette(int l,int c,int taille)
{
  switch(taille)
  {
    case 3 : DessineSprite(l,c-1,S_RAQUETTE_3); break;
    case 5 : DessineSprite(l,c-2,S_RAQUETTE_5); break;
    case 7 : DessineSprite(l,c-3,S_RAQUETTE_7); break;
    default : DessineSprite(l,c-2,S_RAQUETTE_5); break;
  }
}

void DessineChiffre(int l,int c,int val)
{
  switch(val)
  {
    case 0 : DessineSprite(l,c,S_CHIFFRE_0); break;
    case 1 : DessineSprite(l,c,S_CHIFFRE_1); break;
    case 2 : DessineSprite(l,c,S_CHIFFRE_2); break;
    case 3 : DessineSprite(l,c,S_CHIFFRE_3); break;
    case 4 : DessineSprite(l,c,S_CHIFFRE_4); break;
    case 5 : DessineSprite(l,c,S_CHIFFRE_5); break;
    case 6 : DessineSprite(l,c,S_CHIFFRE_6); break;
    case 7 : DessineSprite(l,c,S_CHIFFRE_7); break;
    case 8 : DessineSprite(l,c,S_CHIFFRE_8); break;
    case 9 : DessineSprite(l,c,S_CHIFFRE_9); break;
    default : DessineSprite(l,c,S_CHIFFRE_0); break;    
  }
}

void DessineGameOver(int l,int c)
{
  DessineSprite(l,c,S_GAMEOVER);
}


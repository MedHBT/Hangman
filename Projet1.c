#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include <time.h>
#include <math.h>

/*Declaration des fonctions*/
int nombreJoueurs();        //choisir 1 ou 2 joueur pour jouer
int nombreTentatives();        //choisir le nombre de tentative avant la fin automatique du jeux
int nombreCaractere();        //choisir le nombre de caractere qui compose chaque mot
void intialisationMot(char mot[],int nb_caractere);        //permet de crée un mot valide composer par les deux joueurs en mode double players
int verifierAlpha(char mot[],int nb_caractere);        //permet de verifier si les caractere qui compose le mot sont bien alphabetique
char essaiLettre();        //saisir une lettre par l'utilisateur qui soit valide
void modeDuo();        //c'est le mode deux joueurs
void modeSolo();        //c'est le mode un joueur
int verifierExist(char mot[],char mot_etoile[],char essai_lettre);        //verifie si la letrre proposer par le joueur existe bien don le mot secret et la montrer dans le mot etoile
int verifierEtoile(char mot_etoile[]);        //verifie si les caracteres du mot etoilses sont bien des etoiles ou non
int modeJeux();        //choisir entre mode solo ou mode duo
void modeLibre();        //permet de jouer en solo tout en choisissant le nombre de caractere et le nombre de tentative avec une geration automatique du mot a deviner
int random(int a,int b);        //permet de genere un entier aléatoirement entre [a,b]
void generationMot(char mot[],int nb_caractere);        //permet de generer automatiquement un mot parmis une grande liste de mot
void modeAuto();        //permet de jouer contre ordinateur en decouvrant un mot dans une liste bien definit
void selectMot(char *select_mot,int niveau_diff);        //choisir un mot dans une liste
int niveauDiff();        //choisir le niveau de difficulté du mode automatique
void intialisationTabAlpha(char *tab_alpha);        //remplie un tableau par tout l'alphabet
int verifierTabAlpha(char *tab_alpha,char essai_lettre);        //verifie si la lettre proposer par le joueur n'est pas encore sorti 
void afficheTabAlpha(char *tab_alpha);        //permet d'afficher le tableau d'alphabet

/*Fonction Principal*/
void main(int argc, char *argv[])
{ 
    int nb_joueur;
    srand(time(NULL));
    printf("|----------------------------------------------------------------------------|\n");
    printf("|**********************************Hangman***********************************|\n");
    printf("|----------------------------------------------------------------------------|\n");
    nb_joueur = nombreJoueurs();
    if (nb_joueur==1)
      modeSolo();
      else modeDuo();
    
    system("PAUSE");
}



/*Fonctions Secondaires*/


void modeSolo()
{
     int mode_jeux=modeJeux();
     if (mode_jeux==2)
       modeLibre();
       else modeAuto();
     }

void modeDuo()
{
     int i;
     int nb_tentative;
     int nb_caractere;
     int verif;
     char mot1[25];
     char mot2[25];
     char tab_alpha1[26];
     char tab_alpha2[26];
     char essai_lettre1;
     char essai_lettre2;
	 
     nb_tentative = nombreTentatives();
     nb_caractere = nombreCaractere();
     char mot_etoile1[25];
     char mot_etoile2[25];
     for(i=0;i<nb_caractere;i++)        //intialiser les deux tableaux etoiles par des etoiles 
     {
                                mot_etoile1[i]='*';
                                mot_etoile2[i]='*';
     }
     mot_etoile1[nb_caractere]='\0';
     mot_etoile2[nb_caractere]='\0';
	 
     printf("|----------------------------------------------------------------------------|\n");
     printf("|                         C'est le tour du joueur 1                          |\n");
     printf("|----------------------------------------------------------------------------|\n");
	 
     do      
     {
                                               intialisationMot(mot2,nb_caractere);        //le joueur 1 choisie un mot a faire deviner pour le joueur 2
     }
     while(verifierAlpha(mot2,nb_caractere)!=1);
	 
     printf("|----------------------------------------------------------------------------|\n");
     printf("|                         C'est le tour du joueur 2                          |\n");
     printf("|----------------------------------------------------------------------------|\n");
	 
     do      
     {
                                               intialisationMot(mot1,nb_caractere);        //le joueur 2 choisie un mot a faire deviner pour le joueur
     }
     while(verifierAlpha(mot1,nb_caractere)!=1);
	 intialisationTabAlpha(tab_alpha1);
     intialisationTabAlpha(tab_alpha2);
     do
     {
     printf("|----------------------------------------------------------------------------|\n");
     printf("| Joueur 1                           | Tentatives restantes %d                |\n",nb_tentative);
     printf("|----------------------------------------------------------------------------|\n");
     printf("| Mot cacher : ");
     puts(mot_etoile1);
     do
          { 
          afficheTabAlpha(tab_alpha1);                                                                                                                   
          essai_lettre1=essaiLettre();
          verif = verifierTabAlpha(tab_alpha1,essai_lettre1);
          }
          while (verif!=0);
     verifierExist(mot1,mot_etoile1,essai_lettre1);
     printf("| Le mot cache est :\t");
     puts(mot_etoile1);
     printf("|----------------------------------------------------------------------------|\n");
     printf("| Joueur 2                           | Tentatives restantes %d                |\n",nb_tentative);
     printf("|----------------------------------------------------------------------------|\n");
     printf("| Mot cacher : ");
     puts(mot_etoile2);
     do
          { 
          afficheTabAlpha(tab_alpha2);                                                                                                                   
          essai_lettre2=essaiLettre();
          verif = verifierTabAlpha(tab_alpha2,essai_lettre2);
          }
          while (verif!=0);
     verifierExist(mot2,mot_etoile2,essai_lettre2);
     printf("| Le mot cache est :\t");
     puts(mot_etoile2);
     nb_tentative--;
     }
     while(nb_tentative!=0 && (verifierEtoile(mot_etoile1)!=0 && verifierEtoile(mot_etoile2)!=0));        //la partie s'arrate si le nombre de tentative est fini pour les deux joueurs ou bien l'un des deux a bien deviner le mot
     printf("|----------------------------------------------------------------------------|\n");    
     if(nb_tentative!=0 && verifierEtoile(mot_etoile1)==0 && verifierEtoile(mot_etoile2)==0)
     {
     printf("| Felicitation au deux joueurs!Vous a avez gagne                             |\n");
     }
     else if(nb_tentative!=0 && verifierEtoile(mot_etoile1) == 0)
     {
     printf("| Felicitation!!Le joueur 1 a gagne                                          |\n");
     }
     else if (nb_tentative!=0 && verifierEtoile(mot_etoile2)==0)
     {
     printf("| Felicitation!!Le joueur 2 a gagne                                          |\n");
     }
     else printf("| Vous avez perdu                                                           |\n");
     printf("|----------------------------------------------------------------------------|\n");
}

void modeLibre()
{
     
     int i;
     int verif;
     int nb_tentative;
     int nb_caractere;
     char mot[25];
     char tab_alpha[26];
     char essai_lettre;
     nb_tentative = nombreTentatives();
     nb_caractere = nombreCaractere();
     char mot_etoile[25];
     printf("|----------------------------------------------------------------------------|\n");
     printf("| Chargement du mot en cour...veuillez attendre                              |\n");
     printf("|----------------------------------------------------------------------------|\n");
     for(i=0;i<nb_caractere;i++)
     {
                                mot_etoile[i]='*';
     }
     mot_etoile[nb_caractere]='\0';
     intialisationTabAlpha(tab_alpha);
     generationMot(mot,nb_caractere);
     do
     {
          printf("|----------------------------------------------------------------------------|\n");
          printf("| Mot cache %s            | Tentatives restantes %d                \n",mot_etoile,nb_tentative);
          printf("|----------------------------------------------------------------------------|\n"); 
          do
          { 
          afficheTabAlpha(tab_alpha);                                                                                                                   
          essai_lettre=essaiLettre();
          verif = verifierTabAlpha(tab_alpha,essai_lettre);
          }
          while (verif!=0);
          verifierExist(mot,mot_etoile,essai_lettre);
          nb_tentative--; 
     }
     while(nb_tentative!=0 &&  verifierEtoile(mot_etoile)!=0);    
     if (nb_tentative!=0 && verifierEtoile(mot_etoile) == 0) 
     { 
        printf("|----------------------------------------------------------------------------|\n");
        printf("| Le mot cache etait %s \n",mot_etoile);                 
        printf("|============================================================================|\n");                   
        printf("||--------------------------------------------------------------------------||\n");
        printf("|||*************************** Vous avez gagner ***************************|||\n");
        printf("||--------------------------------------------------------------------------||\n");
        printf("|============================================================================|\n");
     }
     else
     {
        printf("|============================================================================|\n");                   
        printf("||--------------------------------------------------------------------------||\n");
        printf("|||*************************** Vous avez perdu ****************************|||\n");
        printf("||--------------------------------------------------------------------------||\n");
        printf("|============================================================================|\n");
     }
}

void modeAuto()
{
     char mot[25];
     char tab_alpha[26];
     char mot_etoile[25];
     char essai_lettre;
     int niveau_diff;
     int verif;
     int i;
     int nb_caractere;
     int nb_tentative;
     niveau_diff = niveauDiff();
     printf("|----------------------------------------------------------------------------|\n");
     printf("| Chargement du mot en cour...veuillez attendre                              |\n");
     printf("|----------------------------------------------------------------------------|\n");
     selectMot(mot,niveau_diff);
     nb_caractere=strlen(mot);
     if(niveau_diff==1)        //affecte le nombre de tentative automatiquement selon la langueur du mot a deviner et le niveau difficulté
       nb_tentative=strlen(mot)+5;
       else if(niveau_diff==2)
              nb_tentative=strlen(mot)+3;
              else nb_tentative=strlen(mot)+1;  
          
     for(i=0;i<nb_caractere;i++)
     {
                                mot_etoile[i]='*';
     }
     mot_etoile[nb_caractere]='\0';
     
     intialisationTabAlpha(tab_alpha);
     do
     {
          printf("|----------------------------------------------------------------------------|\n");
          printf("| Mot cache %s            | Tentatives restantes %d                \n",mot_etoile,nb_tentative);
          printf("|----------------------------------------------------------------------------|\n"); 
          do
          { 
          afficheTabAlpha(tab_alpha);                                                                                                                   
          essai_lettre=essaiLettre();
          verif = verifierTabAlpha(tab_alpha,essai_lettre);
          }
          while (verif!=0);
          verifierExist(mot,mot_etoile,essai_lettre);
          nb_tentative--; 
     }
     while(nb_tentative!=0 &&  verifierEtoile(mot_etoile)!=0);    
     if (nb_tentative!=0 && verifierEtoile(mot_etoile) == 0) 
     { 
        printf("|----------------------------------------------------------------------------|\n");
        printf("| Le mot cache etait %s \n",mot_etoile);                 
        printf("|============================================================================|\n");                   
        printf("||--------------------------------------------------------------------------||\n");
        printf("|||*************************** Vous avez gagner ***************************|||\n");
        printf("||--------------------------------------------------------------------------||\n");
        printf("|============================================================================|\n");
     }
     else
     {
        printf("|============================================================================|\n");                   
        printf("||--------------------------------------------------------------------------||\n");
        printf("|||*************************** Vous avez perdu ****************************|||\n");
        printf("||--------------------------------------------------------------------------||\n");
        printf("|============================================================================|\n");
     }
     
     puts(mot);
}

int random(int a,int b)
{
   
    return ( rand()%(b-a)+a);
}

void generationMot(char mot[],int nb_caractere)
{
     int i;
     for(i=0;i<nb_caractere;i++)
        {   
                                mot[i]=random(65,91);
        }
        mot[nb_caractere]='\0';
}
     

int nombreJoueurs()
{
     int nb_joueurs;
     do
     {
                      printf("|----------------------------------------------------------------------------|\n");
                      printf("|                    Veuillez choisir le nombre de joueur                    |\n");
                      printf("|                   1 :Contre ordinateur   2 :Deux joueurs                   |\n");
                      printf("|                                       ");
                      scanf("%d",&nb_joueurs);
                      printf("|----------------------------------------------------------------------------|\n");
     }
     while(nb_joueurs!=1 && nb_joueurs!=2);
     return(nb_joueurs);
}

int nombreTentatives()
{
    int nb_tentative;
    do
    {
                      printf("|----------------------------------------------------------------------------|\n");
                      printf("|           Veuillez donner le nombre de tentative maximal autorise          |\n");
                      printf("|                                       ");
                      scanf("%d",&nb_tentative);
                      printf("|----------------------------------------------------------------------------|\n");
    }
    while(nb_tentative == 0);
    return(nb_tentative);
}


int nombreCaractere()
{
    int nb_caractere = 0;
    do
    {
        printf("|----------------------------------------------------------------------------|\n");
        printf("|                 Donnez le nombre de caractere pour chaque mot              |\n");
        printf("|                                       ");
        scanf("%d",&nb_caractere);
        printf("|----------------------------------------------------------------------------|\n");
    }
    while(nb_caractere >= 25);
    return(nb_caractere);
}


void intialisationMot(char mot[],int nb_caractere)
{
     int i=0;
     printf("|----------------------------------------------------------------------------|\n");
     printf("|        Donnez le mot a deviner compose de %d caracteres alphabetiques       |\n",nb_caractere);
     printf("|                                    ");
     do
                    {
                    mot[i]=toupper(getch());
                    printf("*");
                    i++;
                    }
     while(mot[i-1] != '\n' && i <= nb_caractere);
     mot[nb_caractere]='\0';
                    
     printf("\n|----------------------------------------------------------------------------|\n");
     
}
int verifierAlpha(char mot[],int nb_caractere)
{
     int i=0;
     int verif=1;
     while(verif!=0 && i<nb_caractere)
     {
                    if(isalpha(mot[i])==0)
                      {
                                  verif=0;
                      }
                    i++;
     }
     return verif;
}


char essaiLettre()
{
     char essai_lettre;
     printf("|----------------------------------------------------------------------------|\n");
     printf("|                      Donner un caractere alphabetique                      |\n");
     printf("                                       ");
     do
     { 
          
          essai_lettre = getchar();
          fflush(stdin);  //vide le cache memoire si un utilisateurs entre plus qu'un caractere
     }
     while(isalpha(essai_lettre)==0);
     essai_lettre=toupper(essai_lettre);
     printf("\n|----------------------------------------------------------------------------|\n");
     return essai_lettre;
}


int verifierExist(char mot[],char mot_etoile[],char essai_lettre)
{
    int i=0;
    do
    {
                        if(mot[i]==essai_lettre)
                          mot_etoile[i]=essai_lettre;
                        i++;
    }
    while(mot[i]!='\0');
    
    
}


int verifierEtoile(char mot_etoile[])
{
    int i=0;
    int verif=0;
    while(mot_etoile[i]!='\0' && verif==0)
    {
           if(mot_etoile[i]=='*')
             verif=1;
           i++;
    }
    return verif;
}

int modeJeux()
{
     int mode_jeux;
     do
     {
                      printf("|----------------------------------------------------------------------------|\n");
                      printf("|                    Veuiller choisir le mode du jeux                        |\n");
                      printf("|                   1 :Mode automatique   2 :Mode libre                      |\n");
                      printf("|                                       ");
                      scanf("%d",&mode_jeux);
                      printf("|----------------------------------------------------------------------------|\n");
     }
     while(mode_jeux!=1 && mode_jeux!=2);
     return(mode_jeux);
}


void selectMot(char *select_mot,int niveau_diff)
{
    int num_mot_select = 0, i = 0,caractere_lu = 0;
    FILE* bib= NULL;
    if (niveau_diff == 1)
    {
                    bib = fopen("less.txt","r");
    }
    else if (niveau_diff == 2)
    {
                    bib = fopen("to.txt","r");
    }
    else if (niveau_diff == 3)
    {
                    bib = fopen("more.txt","r");
    }
                    if (bib == NULL)
                    {
                                printf("|----------------------------------------------------------------------------|\n");
                                printf("| Impossible de charger le dictionnaire de mots                              |\n");
                                printf("|----------------------------------------------------------------------------|\n");
                    
                    }
                    num_mot_select = random(0,201);
                    rewind(bib);
                    while (num_mot_select > 0)
                         {
                         caractere_lu = fgetc(bib);
                         if (caractere_lu == '\n')
                         num_mot_select--;
                         }
    fgets(select_mot,25,bib);
    select_mot[strlen(select_mot) - 1] = '\0';
    for(i=0;i<strlen(select_mot);i++)
       select_mot[i]=toupper(select_mot[i]);
    fclose(bib);
}

int niveauDiff()
{
     int niveau_diff;
     do
     {
                      printf("|----------------------------------------------------------------------------|\n");
                      printf("|                 Veuiller choisir le niveau de difficulte                   |\n");
                      printf("|                     1 :Facile   2 :Normal   3 :Fort                        |\n");
                      printf("|                                       ");
                      scanf("%d",&niveau_diff);
                      printf("|----------------------------------------------------------------------------|\n");
     }
     while(niveau_diff!=1 && niveau_diff!=2 && niveau_diff!=3);
     return(niveau_diff);
}

void intialisationTabAlpha(char *tab_alpha)
{
     int i;
     for(i=0;i<26;i++)
        tab_alpha[i]=i+65;
}

int verifierTabAlpha(char *tab_alpha,char essai_lettre)
{
     int i=0;
     int verif=1;
     while(i<26 && verif!=0)
     {
                if(tab_alpha[i]==toupper(essai_lettre))
                {
                  tab_alpha[i]=' ';
                  verif = 0;
                }
                i++;
     }
     if(verif==1)
     {
              printf("|----------------------------------------------------------------------------|\n");
              printf("| Vous avez  deja compsee cette letrre!!!Essayez une autre                   |\n");
              printf("|----------------------------------------------------------------------------|\n");
     }
     return(verif);
}
                        
void afficheTabAlpha(char *tab_alpha)
{
     int i;
     printf("|----------------------------------------------------------------------------|\n");
     printf("|            ");
     for(i=0;i<26;i++)
     printf("|%c",tab_alpha[i]);
     printf("|           |\n");
}

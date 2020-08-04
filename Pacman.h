#ifndef PACMAN_H_INCLUDED
#define PACMAN_H_INCLUDED


#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
//#include <fmodex/fmod.h>


typedef struct PERSONNAGES PERSONNAGES;
struct PERSONNAGES
{
    int X;
    int Y;
    int XOld;
    int YOld;
    char affichage;
    int couleur;
    int animation;
    int direction;
    int direction_new;

    clock_t apparition;


};

typedef struct HScore HScore;
struct HScore
{
    int Score;
    char Pseudo[10];
};


typedef struct Coord Coord;
struct Coord
{
    int X;
    int Y;

};

typedef struct ALGOA ALGOA;
struct ALGOA
{
    Coord enfant;
    Coord parent;
    int cout_somme;
    int cout_actu;
    int cout_parent;
};



void gestion_pacman(PERSONNAGES *perso, char matrice[2][32][32], int posX, int posY, int max_taille_plateau, int min_taille_plateau);
void deplacement_perso(PERSONNAGES *perso, char matrice[2][32][32]);
void IA1_deplacements(PERSONNAGES *perso, char grille[2][32][32], PERSONNAGES Pacman);
void affichage_IA(PERSONNAGES perso, char grille[2][32][32], int posX, int posY);
int mort_pacman(PERSONNAGES Pacman, PERSONNAGES IA, int *vie);


int gestion_score(char matrice[2][32][32], int coordX, int coordY);
int pourcentage_niveau(int score_grille, int score_niveau);
void high_score(int score_partie);
void tri_bulle_score(HScore best_player[11]);


void afficher_interface();
void recuperer_grille(int taille_grille, char matrice[2][taille_grille][taille_grille], char dir[30], int Spawn[2], int SpawnFantome[2], int *Score_max, int fantome_au_spawn[4]);
void afficher_grille(int taille_grille, char matrice[2][taille_grille][taille_grille], int posX, int posY);
void afficher_grille_detail(int taille_grille, char matrice[2][taille_grille][taille_grille], int i, int j, int posX, int posY);
void clignottement_pacgum(char tab[2][32][32], int animation_pacgum, int posX, int posY);


void clearscreen();
void gotoligcol( int lig, int col );
void couleur(int t,int f);
int taille_console();
int setConsoleScreenBufferInfo(COORD dwSize);
void fullscreen();


void IA_fuite(char tab[2][32][32], PERSONNAGES *Perso, PERSONNAGES Pacman);

void IA_Pinky(char tab[2][32][32], PERSONNAGES *Pinky);
void IA_Inky(char tab[2][32][32], PERSONNAGES *Inky);
void IA_Clyde(char tab[2][32][32], PERSONNAGES *Clyde);
void IA_Blinky(char tab[2][32][32], PERSONNAGES *Blinky, PERSONNAGES Pacman);
void direction_random_IA(PERSONNAGES *Perso, char tab[2][32][32]);


#endif // PACMAN_H_INCLUDED

#include "Pacman.h"

void gestion_pacman(PERSONNAGES *perso, char matrice[2][32][32], int posX, int posY, int max_taille_plateau, int min_taille_plateau)
{

    if (perso->X < min_taille_plateau+1)
            perso->X = max_taille_plateau;

    else if (perso->X > max_taille_plateau)
        perso->X = min_taille_plateau+1;

    if (perso->Y < min_taille_plateau+1)
        perso->Y = max_taille_plateau;

    else if (perso->Y > max_taille_plateau)
        perso->Y = min_taille_plateau+1;



    if (perso->animation >= 0 && perso->animation <= 3)
    {
        if (perso->direction == 0 || perso->direction == 1)
        {
            perso->affichage = '|';
        }
        else if (perso->direction == 2 || perso->direction == 3)
        {
            perso->affichage = '=';
        }
    }

    else if (perso->animation >=4)
    {
        if (perso->direction == 0)
        {
            perso->affichage = 'V';
        }

        else if (perso->direction == 1)
        {
            perso->affichage = 'A';
        }

        else if (perso->direction == 2)
        {
            perso->affichage = '>';
        }

        else if (perso->direction == 3)
        {
            perso->affichage = '<';
        }
    }

    if (perso->animation >=6)
        perso->animation = 0;


    perso->animation++;


    if (matrice[1][perso->XOld][perso->YOld] > 0)
    {
        gotoligcol(posX+perso->XOld, posY+perso->YOld);
        printf(" ");
    }

    if (matrice[1][perso->X][perso->Y] > 0)
    {
        gotoligcol(posX+perso->X, posY+perso->Y);
        couleur(perso->couleur,0);
        printf("%c", perso->affichage);
        gotoligcol(0,55);
    }


    perso->XOld = perso->X;
    perso->YOld = perso->Y;

}

void deplacement_perso(PERSONNAGES *perso, char matrice[2][32][32])
{
    int pos;

    if (perso->direction == 0) // haut
    {
        if(matrice[1][perso->X-1][perso->Y] > 0)
        {
            pos = perso->X;
            pos--;
            perso->X = pos;
        }
    }

    if (perso->direction == 1) // Bas
    {
        if(matrice [1][perso->X+1][perso->Y] > 0)
        {
            pos = perso->X;
            pos++;
            perso->X = pos;
        }
    }

    if (perso->direction == 2) // gauche
    {
        if(matrice [1][perso->X][perso->Y-1] > 0)
        {
            pos = perso->Y;
            pos--;
            perso->Y = pos;
        }
    }

    if (perso->direction == 3) // haut
    {
        if(matrice [1][perso->X][perso->Y+1] > 0)
        {
            pos = perso->Y;
            pos++;
            perso->Y = pos;
        }
    }
}


void IA1_deplacements(PERSONNAGES *perso, char grille[2][32][32], PERSONNAGES Pacman)
{
    int coordX = perso->X;
    int coordY = perso->Y;
    int distanceX, distanceY;

    distanceX = coordX - Pacman.X;
    distanceY = coordY - Pacman.Y;

    if (distanceX >= 0 && distanceY >= 0)
    {
        //Pacman est en haut a gauche du fantome
        if (distanceX < distanceY)
        {
            if (grille[1][coordX][coordY-1] == 1)
            {
                perso->Y --;
            }
            else if(grille[1][coordX-1][coordY] == 1)
            {
                perso->X --;
            }
            else if (grille[1][coordX+1][coordY] == 1)
            {
                perso->X ++;
            }
            else if (grille[1][coordX][coordY+1] == 1)
            {
                perso->Y ++;
            }
        }
        else
        {
            if(grille[1][coordX-1][coordY] == 1)
            {
                perso->X --;
            }
            else if (grille[1][coordX][coordY-1] == 1)
            {
                perso->Y --;
            }
            else if (grille[1][coordX][coordY+1] == 1)
            {
                perso->Y ++;
            }
            else if (grille[1][coordX+1][coordY] == 1)
            {
                perso->X ++;
            }
        }
    }
    else if (distanceX >= 0 && distanceY < 0)
    {
        //Pacman est en bas a gauche du fantome
        distanceY = -distanceY;
        if (distanceX < distanceY)
        {
            if (grille[1][coordX][coordY+1] == 1)
            {
                perso->Y++;
            }
            else if(grille[1][coordX-1][coordY] == 1)
            {
                perso->X--;
            }
            else if (grille[1][coordX+1][coordY] == 1)
            {
                perso->X ++;
            }
            else if (grille[1][coordX][coordY-1] == 1)
            {
                perso->Y --;
            }
        }
        else
        {
            if(grille[1][coordX-1][coordY] == 1)
            {
                perso->X --;
            }
            else if (grille[1][coordX][coordY+1] == 1)
            {
                perso->Y ++;
            }
            else if (grille[1][coordX][coordY-1] == 1)
            {
                perso->Y --;
            }
            else if (grille[1][coordX+1][coordY] == 1)
            {
                perso->X ++;
            }
        }
    }

    else if (distanceX < 0 && distanceY >= 0)
    {
        //Pacman est en haut a droite du fantome
        distanceX = -distanceX;

        if (distanceX < distanceY)
        {
            if (grille[1][coordX][coordY-1] == 1)
            {
                perso->Y--;
            }
            else if(grille[1][coordX+1][coordY] == 1)
            {
                perso->X++;
            }
            else if (grille[1][coordX-1][coordY] == 1)
            {
                perso->X --;
            }
            else if (grille[1][coordX][coordY+1] == 1)
            {
                perso->Y ++;
            }
        }
        else
        {
            if(grille[1][coordX+1][coordY] == 1)
            {
                perso->X ++;
            }
            else if (grille[1][coordX][coordY-1] == 1)
            {
                perso->Y --;
            }
            else if (grille[1][coordX][coordY+1] == 1)
            {
                perso->Y ++;
            }
            else if (grille[1][coordX-1][coordY] == 1)
            {
                perso->X --;
            }
        }

    }
    if(distanceX < 0 && distanceY < 0)
    {
        //pacman est en haut a gauche du fantome
        distanceX = - distanceX;
        distanceY = - distanceY;
        if (distanceX < distanceY)
        {
            if (grille[1][coordX][coordY+1] == 1)
            {
                perso->Y ++;
            }
            else if(grille[1][coordX+1][coordY] == 1)
            {
                perso->X ++;
            }
            else if (grille[1][coordX-1][coordY] == 1)
            {
                perso->X --;
            }
            else if (grille[1][coordX][coordY-1] == 1)
            {
                perso->Y --;
            }
        }
        else
        {
            if(grille[1][coordX+1][coordY] == 1)
            {
                perso->X ++;
            }
            else if (grille[1][coordX][coordY+1] == 1)
            {
                perso->Y ++;
            }
            else if (grille[1][coordX][coordY-1] == 1)
            {
                perso->Y --;
            }
            else if (grille[1][coordX-1][coordY] == 1)
            {
                perso->X --;
            }
        }
    }
}

void affichage_IA(PERSONNAGES perso, char grille[2][32][32], int posX, int posY)
{
    afficher_grille_detail(32, grille, perso.XOld, perso.YOld, posX, posY);

    gotoligcol(posX + perso.X, posY + perso.Y);
    couleur(perso.couleur,0);
    printf("%c", perso.affichage);
}

int mort_pacman(PERSONNAGES Pacman, PERSONNAGES IA, int *vie)
{

    if (Pacman.X == IA.X && Pacman.Y == IA.Y)
    {
        return 2;
    }

    else if (Pacman.XOld == IA.X && Pacman.YOld == IA.Y)
    {
        return 2;
    }

    else
        return 0;
}

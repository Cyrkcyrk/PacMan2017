#include "Pacman.h"

void afficher_interface()
{
    FILE* affichage_interface;

    affichage_interface = fopen("./Affichage/interface.txt", "r");
    char c = 0;

    char bordure_vertical_vide= 179;///│
    char bordure_horizontale= 196;///─
    char coin_bas_gauche = 192; ///└
    char coin_bas_droit = 217; ///┘
    char coin_haut_gauche = 218; ///┌
    char coin_haut_droite = 191; ///┐

    while (c != EOF)
    {
        c = fgetc(affichage_interface);

        if (c == 'A')
        {
            couleur(1,0);
            printf("%c", coin_haut_gauche);
        }

        else if (c == 'B')
        {
            couleur(1,0);
            printf("%c", coin_haut_droite);
        }
        else if (c == 'C')
        {
            couleur(1,0);
            printf("%c", coin_bas_gauche);
        }
        else if (c == 'D')
        {
            couleur(1,0);
            printf("%c", coin_bas_droit);
        }
        else if (c == '-')
        {
            couleur(1,0);
            printf("%c", bordure_horizontale);
        }
        else if (c == '|')
        {
            couleur(1,0);
            printf("%c", bordure_vertical_vide);
        }
        else if (c == '*')
        {
            couleur(15,0);
            printf(".");
        }
        else if (c == '+')
        {
            couleur(15,0);
            printf("O");
        }
        else if (c == '=')
        {
            couleur(12,0);
            printf("m");
        }
        else if (c == '.')
        {
            couleur(0,0);
            printf(" ");
        }
        else if (c == '$')
        {
            couleur(15,0);
            printf(" ");
            while(c != '$')
            {
                c = fgetc(affichage_interface);
                printf("%c",c);
            }
        }
        else
            printf("%c", c);
    }
    fclose(affichage_interface);
}

void recuperer_grille(int taille_grille, char matrice[2][taille_grille][taille_grille], char dir[30], int Spawn[2], int SpawnFantome[2], int *Score_max, int fantome_au_spawn[4])
{
    FILE* grille;
    grille = fopen(dir, "r");
    int i = 0, j=0;

    if (grille != NULL)
    {
        fscanf(grille, "%d", &*Score_max);
        fscanf(grille, "%d", &Spawn[0]);
        fscanf(grille, "%d", &Spawn[1]);
        fscanf(grille, "%d", &SpawnFantome[0]);
        fscanf(grille, "%d", &SpawnFantome[1]);

        if (SpawnFantome[0] != 0)
        {
            fantome_au_spawn[0] = 1;
            fantome_au_spawn[1] = 1;
            fantome_au_spawn[2] = 1;
            fantome_au_spawn[3] = 1;
        }
        else
        {
            fantome_au_spawn[0] = 0;
            fantome_au_spawn[1] = 0;
            fantome_au_spawn[2] = 0;
            fantome_au_spawn[3] = 0;
        }
        for (i=0; i<taille_grille; i++)
        {
            for (j=0; j<taille_grille; j++)
            {
                fscanf(grille, "%c", &matrice[0][i][j]);
                if (matrice[0][i][j] == '\n')
                    j--;
            }
        }
        fclose(grille);
    }
    else
    {
        printf("ERREUR!");
    }



    for (i=0; i<taille_grille; i++)
    {
        for (j=0; j<taille_grille; j++)
        {
            if (matrice[0][i][j] == '*' || matrice[0][i][j] == '+' || matrice[0][i][j] == '=' || matrice[0][i][j] == '$')
            {
                matrice[1][i][j] = 1;
            }
            else if (matrice[0][i][j] == 'a' || matrice[0][i][j] == 'b' || matrice[0][i][j] == 'c' || matrice[0][i][j] == 'd' || matrice[0][i][j] == '?')
            {
                matrice[1][i][j] = 1;
            }
            else if (matrice[0][i][j] == 'w' || matrice[0][i][j] == 'x' || matrice[0][i][j] == 'y' || matrice[0][i][j] == 'z' || matrice[0][i][j] == '!')
            {
                matrice[1][i][j] = 1;
            }
            else if (matrice[0][i][j] == 'S')
            {
                matrice[1][i][j] = 2;
            }
            else
            {
                matrice[1][i][j] = 0;
            }
        }
    }
}


void afficher_grille(int taille_grille, char matrice[2][taille_grille][taille_grille], int posX, int posY)
{

    /**
    char bordure_vertical_vide= 186;///║
    char bordure_vertical_centre = 206; /// ╬
    char bordure_vertical_gauche = 204; ///╠
    char bordure_vertical_droite = 185; ///╣
    char bordure_vertical_bas = 202; ///╩
    char bordure_vertical_haut = 203; ///╦
    char bordure_horizontale= 205;///═
    char coin_bas_gauche = 200; ///╚
    char coin_bas_droit = 188; ///╝
    char coin_haut_gauche = 201; ///╔
    char coin_haut_droite = 187; ///╗
    */

    char bordure_vertical_vide= 179;///│
    char bordure_horizontale= 196;///─
    char coin_bas_gauche = 192; ///└
    char coin_bas_droit = 217; ///┘
    char coin_haut_gauche = 218; ///┌
    char coin_haut_droite = 191; ///┐

    int i,j;
    for (i=0; i<taille_grille; i++)
    {
        gotoligcol(posX, posY);
        for (j=0; j<taille_grille; j++)
        {
            if (matrice[0][i][j] == 'A')
            {
                couleur(1,0);
                printf("%c", coin_haut_gauche);
            }

            else if (matrice[0][i][j] == 'B')
            {
                couleur(1,0);
                printf("%c", coin_haut_droite);
            }
            else if (matrice[0][i][j] == 'C')
            {
                couleur(1,0);
                printf("%c", coin_bas_gauche);
            }
            else if (matrice[0][i][j] == 'D')
            {
                couleur(1,0);
                printf("%c", coin_bas_droit);
            }
            else if (matrice[0][i][j] == '-')
            {
                couleur(1,0);
                printf("%c", bordure_horizontale);
            }
            else if (matrice[0][i][j] == '_')
            {
                couleur(13,0);
                printf("%c", bordure_horizontale);
            }
            else if (matrice[0][i][j] == '|')
            {
                couleur(1,0);
                printf("%c", bordure_vertical_vide);
            }
            else if (matrice[0][i][j] == '*' || matrice[0][i][j] == 'a' || matrice[0][i][j] == 'b' || matrice[0][i][j] == 'c' || matrice[0][i][j] == 'd' || matrice[0][i][j] == '?')
            {
                couleur(15,0);
                printf(".");
            }
            /*
            else if (matrice[0][i][j] == 'a')
            {
                couleur(15,0);
                printf(".");
            }
            else if (matrice[0][i][j] == 'b')
            {
                couleur(15,0);
                printf(".");
            }
            else if (matrice[0][i][j] == 'c')
            {
                couleur(15,0);
                printf(".");
            }
            else if (matrice[0][i][j] == 'd')
            {
                couleur(15,0);
                printf(".");
            }

            else if (matrice[0][i][j] == '?')
            {
                couleur(15,0);
                printf(".");
            }*/
            else if (matrice[0][i][j] == '+')
            {
                couleur(15,0);
                printf("O");
            }
            else if (matrice[0][i][j] == '=')
            {
                couleur(12,0);
                printf("m");
            }
            else if (matrice[0][i][j] == '.')
            {
                couleur(0,0);
                printf(" ");
            }
            else if (matrice[0][i][j] == '$' || matrice[0][i][j] == 'w' || matrice[0][i][j] == 'x' || matrice[0][i][j] == 'y' || matrice[0][i][j] == 'z' || matrice[0][i][j] == '!')
            {
                couleur(0,0);
                printf(" ");
            }
            else if (matrice[0][i][j] == 'S')
            {
                couleur(0,0);
                printf(" ");
            }
            else
            {
                printf("%C", matrice[0][i][j]);
            }
        }
        posX++;
    }
}

void afficher_grille_detail(int taille_grille, char matrice[2][taille_grille][taille_grille], int i, int j, int posX, int posY)
{
    gotoligcol(posX+i, posY+j);
    if (matrice[1][i][j] != 1)
    {
        printf(" ");
    }
    else
    {
        char bordure_vertical_vide= 179;///│
        char bordure_horizontale= 196;///─
        char coin_bas_gauche = 192; ///└
        char coin_bas_droit = 217; ///┘
        char coin_haut_gauche = 218; ///┌
        char coin_haut_droite = 191; ///┐


        if (matrice[0][i][j] == 'A')
        {
            couleur(1,0);
            printf("%c", coin_haut_gauche);
        }

        else if (matrice[0][i][j] == 'B')
        {
            couleur(1,0);
            printf("%c", coin_haut_droite);
        }
        else if (matrice[0][i][j] == 'C')
        {
            couleur(1,0);
            printf("%c", coin_bas_gauche);
        }
        else if (matrice[0][i][j] == 'D')
        {
            couleur(1,0);
            printf("%c", coin_bas_droit);
        }
        else if (matrice[0][i][j] == '-')
        {
            couleur(1,0);
            printf("%c", bordure_horizontale);
        }
        else if (matrice[0][i][j] == '_')
        {
            couleur(13,0);
            printf("%c", bordure_horizontale);
        }
        else if (matrice[0][i][j] == '|')
        {
            couleur(1,0);
            printf("%c", bordure_vertical_vide);
        }
        else if (matrice[0][i][j] == '*' || matrice[0][i][j] == 'a' || matrice[0][i][j] == 'b' || matrice[0][i][j] == 'c' || matrice[0][i][j] == 'd' || matrice[0][i][j] == '?')
        {
            couleur(15,0);
            printf(".");
        }

        else if (matrice[0][i][j] == '+')
        {
            couleur(15,0);
            printf("O");
        }
        else if (matrice[0][i][j] == '=')
        {
            couleur(12,0);
            printf("m");
        }
        else if (matrice[0][i][j] == '.')
        {
            couleur(0,0);
            printf(" ");
        }
        else if (matrice[0][i][j] == '$' || matrice[0][i][j] == 'w' || matrice[0][i][j] == 'x' || matrice[0][i][j] == 'y' || matrice[0][i][j] == 'z' || matrice[0][i][j] == '!')
        {
            couleur(0,0);
            printf(" ");
        }
        else if (matrice[0][i][j] == 'S')
        {
            couleur(0,0);
            printf(" ");
        }
        else
        {
            printf("%C", matrice[0][i][j]);
        }
    }
}


void clignottement_pacgum(char tab[2][32][32], int animation_pacgum, int posX, int posY)
{
    couleur(15,0);
    int i,j;
    if (animation_pacgum >= 0 && animation_pacgum <5)
    {
        for (i=0; i<32; i++)
        {
            for (j=0; j<32; j++)
            {
                if (tab[0][i][j] == '+' && tab[1][i][j] == 1)
                {
                    gotoligcol(posX + i, posY + j);
                    printf("O");
                }
            }
        }
    }

    else if (animation_pacgum >= 5 && animation_pacgum < 10)
    {
        for (i=0; i<32; i++)
        {
            for (j=0; j<32; j++)
            {
                if (tab[0][i][j] == '+' && tab[1][i][j] == 1)
                {
                    gotoligcol(posX + i, posY + j);
                    printf("o");
                }
            }
        }
    }
}

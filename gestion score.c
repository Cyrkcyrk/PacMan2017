#include "Pacman.h"

int gestion_score(char matrice[2][32][32], int coordX, int coordY)
{
    int score = 0;

    if (matrice[1][coordX][coordY] == 1)
    {
        matrice[1][coordX][coordY] = 2;
        if (matrice[0][coordX][coordY] == '*' || matrice[0][coordX][coordY] == 'a' || matrice[0][coordX][coordY] == 'b' || matrice[0][coordX][coordY] == 'c' || matrice[0][coordX][coordY] == 'd' || matrice[0][coordX][coordY] == '?')
        {
            score = 10;
        }
        else if (matrice[0][coordX][coordY] == '+')
        {
            score = 50;
        }
        else if (matrice[0][coordX][coordY] == '=')
        {
            score = -1;
        }
    }

    return score;
}

int pourcentage_niveau(int score_grille, int score_niveau)
{
    float pourcentage = 100.0*score_grille / score_niveau;

    if (pourcentage < 50)
        return 1;
    else if (pourcentage>= 40 && pourcentage < 70)
        return 2;
    else if (pourcentage >= 70 && pourcentage < 90)
        return 3;
    else
        return 4;
}


void high_score(int score_partie)
{
    FILE* high_score_file;

    high_score_file = fopen("./Highscore.txt", "r");

    HScore best_player[11];
    int i;

    if (high_score_file != NULL)
    {
        for (i=0; i<10; i++)
        {
            fscanf(high_score_file, "%d %s", &best_player[i].Score, &best_player[i].Pseudo);
        }
        fclose(high_score_file);
    }
    else
    {
        for (i=0; i<10; i++)
        {
            best_player[i].Pseudo[1] = 'C';
            best_player[i].Pseudo[2] = 'o';
            best_player[i].Pseudo[3] = 'm';
            best_player[i].Pseudo[4] = 'p';
            best_player[i].Pseudo[5] = 'u';
            best_player[i].Pseudo[6] = 't';
            best_player[i].Pseudo[7] = 'e';
            best_player[i].Pseudo[8] = 'r';
        }
    }

    for (i=0; i<10; i++)
    {
        gotoligcol(16+i, 8);
        printf("%6d", best_player[i].Score);

        gotoligcol(16+i, 16);
        printf("%s", best_player[i].Pseudo);
    }

    best_player[10].Score = score_partie;
    gotoligcol(30, 8);
    printf("%6d", best_player[10].Score);

    gotoligcol(30, 16);
    scanf("%s", best_player[10].Pseudo);

    tri_bulle_score(best_player);

    high_score_file = fopen("./Highscore.txt", "w");

    if (high_score_file != NULL)
    {
        for (i=0; i<10; i++)
        {
            fprintf(high_score_file, "%d %s\n", best_player[i].Score, best_player[i].Pseudo);
        }
        fclose(high_score_file);
    }

    for (i=0; i<10; i++)
    {
        if (best_player[i].Score == score_partie)
            couleur(14,0);
        else
            couleur(7,0);


        gotoligcol(16+i, 8);
        printf("%6d", best_player[i].Score);

        gotoligcol(16+i, 16);
        printf("          ");

        gotoligcol(16+i, 16);
        printf("%s", best_player[i].Pseudo);
    }
}

void tri_bulle_score(HScore best_player[11])
{
    HScore buffer;
    int i, j;
    int fin = 0;

    while (fin != 10)
    {
        fin = 0;
        for (i=0; i<11; i++)
        {
            if (best_player[i].Score < best_player[i+1].Score)
            {
                buffer.Score = best_player[i].Score;
                best_player[i].Score = best_player[i+1].Score;
                best_player[i+1].Score = buffer.Score;

                for (j=0; j<10; j++)
                {
                    buffer.Pseudo[j] = best_player[i].Pseudo[j];
                }
                for (j=0; j<10; j++)
                {
                    best_player[i].Pseudo[j] = best_player[i+1].Pseudo[j];
                }
                for (j=0; j<10; j++)
                {
                    best_player[i+1].Pseudo[j] = buffer.Pseudo[j];
                }
            }
        }



        for (i=0; i<10; i++)
        {
            if (best_player[i].Score > best_player[i+1].Score)
            {
                fin++;
            }
        }
    }
}

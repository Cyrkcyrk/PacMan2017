#include "Pacman.h"

void IA_Clyde(char tab[2][32][32], PERSONNAGES *Clyde)
{
    /*
    if (Clyde->X < 1)
    {
        Clyde->X = 30;
        gotoligcol(30,5);
        couleur(15,13);
        printf("G");
    }
    else if (Clyde->X > 31)
    {
        Clyde->X = 1;
        gotoligcol(30,35);
        couleur(15,13);
        printf("G");
    }
*/
    if (Clyde->Y < 1)
    {
        Clyde->Y = 30;
        gotoligcol(19,4);
        printf(" ");
    }
    else if (Clyde->Y > 30)
    {
        Clyde->Y = 1;
        gotoligcol(19,35);
        printf(" ");
    }


    if (tab[0][Clyde->X][Clyde->Y] == 'a' || tab[0][Clyde->X][Clyde->Y] == 'w')
    {
        if (Clyde->direction == 0)
            Clyde->direction = 3;
        else
            Clyde->direction = 1;
    }
    else if (tab[0][Clyde->X][Clyde->Y] == 'b' || tab[0][Clyde->X][Clyde->Y] == 'x')
    {
        if (Clyde->direction == 0)
            Clyde->direction = 2;
        else
            Clyde->direction = 1;
    }
    else if (tab[0][Clyde->X][Clyde->Y] == 'c' || tab[0][Clyde->X][Clyde->Y] == 'y')
    {
        if (Clyde->direction == 1)
            Clyde->direction = 3;
        else
            Clyde->direction = 0;
    }
    else if (tab[0][Clyde->X][Clyde->Y] == 'd' || tab[0][Clyde->X][Clyde->Y] == 'z')
    {
        if (Clyde->direction == 1)
            Clyde->direction = 2;
        else
            Clyde->direction = 0;
    }

    else if (tab[0][Clyde->X][Clyde->Y] == '?' || tab[0][Clyde->X][Clyde->Y] == '!')
    {
        int fin = 0;
        int random;
        while (fin != 1)
        {
            random = rand()%4;
            switch (random)
            {
            case 0:
                {
                    if (tab[1][Clyde->X][Clyde->Y-1] > 0 && Clyde->direction != 1)
                    {
                        Clyde->direction = 0;
                        fin = 1;
                    }
                    break;
                }
            case 1:
                {
                    if (tab[1][Clyde->X][Clyde->Y+1] > 0 && Clyde->direction != 0)
                    {
                        Clyde->direction = 1;
                        fin = 1;
                    }
                    break;
                }
            case 2:
                {
                    if (tab[1][Clyde->X-1][Clyde->Y] > 0 && Clyde->direction != 3)
                    {
                        Clyde->direction = 2;
                        fin = 1;
                    }
                    break;
                }
            case 3:
                {
                    if (tab[1][Clyde->X+1][Clyde->Y] > 0 && Clyde->direction != 2)
                    {
                        Clyde->direction = 3;
                        fin = 1;
                    }
                    break;
                }
            }
        }
    }

    if (tab[0][Clyde->X][Clyde->Y] != '*')
    {
        //system("pause");
    }

    Clyde->XOld = Clyde->X;
    Clyde->YOld = Clyde->Y;
    deplacement_perso(Clyde, tab);

}

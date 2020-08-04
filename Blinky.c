#include "Pacman.h"

void IA_Blinky(char tab[2][32][32], PERSONNAGES *Blinky, PERSONNAGES Pacman)
{
    if (Blinky->X < 30+1)
        Blinky->X = 30;

    else if (Blinky->X > 30)
        Blinky->X = 0+1;

    if (Blinky->Y < 0+1)
        Blinky->Y = 30;

    else if (Blinky->Y > 30)
        Blinky->Y = 0+1;


    if (Blinky->Y < 1)
    {
        Blinky->Y = 32;
        Blinky->direction = 3;
    }

    else if (Blinky->Y > 32)
    {
        Blinky->Y = 1;
        Blinky->direction = 2;
    }
    if (Blinky->X < 1)
    {
        Blinky->X = 32;
        Blinky->direction = 1;
    }

    else if (Blinky->X > 32)
    {
        Blinky->X = 1;
        Blinky->direction = 0;
    }


    if (tab[0][Blinky->X][Blinky->Y] == 'a' || tab[0][Blinky->X][Blinky->Y] == 'w')
    {
        if (Blinky->direction == 0)
            Blinky->direction = 3;
        else
            Blinky->direction = 1;
    }
    else if (tab[0][Blinky->X][Blinky->Y] == 'b' || tab[0][Blinky->X][Blinky->Y] == 'x')
    {
        if (Blinky->direction == 0)
            Blinky->direction = 2;
        else
            Blinky->direction = 1;
    }
    else if (tab[0][Blinky->X][Blinky->Y] == 'c' || tab[0][Blinky->X][Blinky->Y] == 'y')
    {
        if (Blinky->direction == 1)
            Blinky->direction = 3;
        else
            Blinky->direction = 0;
    }
    else if (tab[0][Blinky->X][Blinky->Y] == 'd' || tab[0][Blinky->X][Blinky->Y] == 'z')
    {
        if (Blinky->direction == 1)
            Blinky->direction = 2;
        else
            Blinky->direction = 0;
    }


    else if (tab[0][Blinky->X][Blinky->Y] == '?' || tab[0][Blinky->X][Blinky->Y] == '!')
    {
        int positionH, positionV;
        int distanceH, distanceV;

        distanceV = Blinky->Y - Pacman.Y;
        distanceH = Blinky->X - Pacman.X;

        if (distanceH < 0)   //a droite
        {
            distanceH = -distanceH;
            positionV = 1;
        }
        else                            //a gauche
            positionV = -1;

        if (distanceV < 0)   //en bas
        {
            positionH = 1;
            distanceV = -distanceV;
        }
        else                            //en haut
            positionH = -1;



        if (positionH == -1 && positionV == -1) /// En haut a gauche
        {
            gotoligcol(3, 55);
            printf("Haut gauche      ");

            if (tab[1][Blinky->X-1][Blinky->Y] > 0 && tab[1][Blinky->X][Blinky->Y-1] > 0)
            {
                if (distanceH == 0)
                {
                    Blinky->direction = 0;
                }
                else if (distanceV == 0)
                {
                    Blinky->direction = 2;
                }
                else
                {
                    if (distanceH < distanceV)
                    {
                        Blinky->direction = 0;
                    }
                    else
                        Blinky->direction = 2;
                }
            }

            else if (tab[1][Blinky->X-1][Blinky->Y] > 0) //a droite
            {
                Blinky->direction = 2;
            }
            else if (tab[1][Blinky->X][Blinky->Y-1] > 0) //en haut
            {
                Blinky->direction = 0;
            }
            else
            {
                direction_random_IA(Blinky, tab);
            }
        }

        else if (positionH == 1 && positionV == -1) /// En haut a droite
        {

            if (tab[1][Blinky->X+1][Blinky->Y] > 0 && tab[1][Blinky->X][Blinky->Y-1] > 0)
            {
                if (distanceH == 0)
                {
                    Blinky->direction = 0;
                }
                else if (distanceV == 0)
                {
                    Blinky->direction = 3;
                }
                else
                {
                    if (distanceH < distanceV)
                    {
                        Blinky->direction = 0;
                    }
                    else
                        Blinky->direction = 3;
                }
            }
            else if (tab[1][Blinky->X][Blinky->Y-1] > 0) //En haut
            {
                Blinky->direction = 0;
            }
            else if (tab[1][Blinky->X+1][Blinky->Y] > 0) //a gauche
            {
                Blinky->direction = 3;
            }
            else
            {
                direction_random_IA(Blinky, tab);
            }
        }

        else if (positionH == -1 && positionV == 1) /// En bas a gauche
        {
            gotoligcol(3, 55);
            printf("Bas Gauche      ");
            if (tab[1][Blinky->X-+1][Blinky->Y] > 0 && tab[1][Blinky->X][Blinky->Y+1] > 0)
            {
                if (distanceH == 0)
                {
                    Blinky->direction = 1;
                }
                else if (distanceV == 0)
                {
                    Blinky->direction = 2;
                }
                else
                {
                    if (distanceH < distanceV)
                    {
                        Blinky->direction = 1;
                    }
                    else
                        Blinky->direction = 2;
                }
            }
            else if (tab[1][Blinky->X+1][Blinky->Y] > 0) //a gauche
            {
                Blinky->direction = 2;
            }

            else if (tab[1][Blinky->X][Blinky->Y+1] > 0) //En Bas
            {
                Blinky->direction = 1;
            }
            else
            {
                direction_random_IA(Blinky, tab);
            }
        }

        else if (positionH == 1 && positionV == 1) /// En bas a droite
        {
            gotoligcol(3, 55);
            printf("Bas Droite      ");
            if (tab[1][Blinky->X+1][Blinky->Y] > 0 && tab[1][Blinky->X][Blinky->Y+1] > 0)
            {
                if (distanceH == 0)
                {
                    Blinky->direction = 1;
                }
                else if (distanceV == 0)
                {
                    Blinky->direction = 3;
                }
                else
                {
                    if (distanceH < distanceV)
                    {
                        Blinky->direction = 1;
                    }
                    else
                        Blinky->direction = 2;
                }


            }
            else if (tab[1][Blinky->X][Blinky->Y+1] > 0) //En Bas
            {
                Blinky->direction = 1;
            }
            else if (tab[1][Blinky->X-1][Blinky->Y] > 0) //a droite
            {
                Blinky->direction = 3;
            }
            else
            {
                direction_random_IA(Blinky, tab);
            }
        }
    }

    if (tab[0][Blinky->X][Blinky->Y] != '*')
    {
        //system("pause");
    }

    Blinky->XOld = Blinky->X;
    Blinky->YOld = Blinky->Y;
    deplacement_perso(Blinky, tab);

}

void direction_random_IA(PERSONNAGES *Perso, char tab[2][32][32])
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
                if (tab[1][Perso->X][Perso->Y-1] > 0 && Perso->direction != 1)
                {
                    Perso->direction = 0;
                    fin = 1;
                }
                break;
            }
        case 1:
            {
                if (tab[1][Perso->X][Perso->Y+1] > 0 && Perso->direction != 0)
                {
                    Perso->direction = 1;
                    fin = 1;
                }
                break;
            }
        case 2:
            {
                if (tab[1][Perso->X-1][Perso->Y] > 0 && Perso->direction != 3)
                {
                    Perso->direction = 2;
                    fin = 1;
                }
                break;
            }
        case 3:
            {
                if (tab[1][Perso->X+1][Perso->Y] > 0 && Perso->direction != 2)
                {
                    Perso->direction = 3;
                    fin = 1;
                }
                break;
            }
        }
    }
}

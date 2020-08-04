#include "Pacman.h"
void afficher_demarage()
{
    printf("PACMAN:\n\n\n");
    printf("Vous êtes Caman, le personnage ");
    couleur (14,0);
    printf("jaune.\n");
    couleur(7,0);
    printf("Vous devez manger toutes les Pacgums (les points), afin de terminer le niveau.\n");
    printf("Les Super-Pacgums ('o') vous permettront d'être invincible pendant 5 secondes et de manger les fantomes.\n");
    printf("Attention à eux, justement. Si ils vous touches, vous mourez et perdez une vie.\n");
    printf("A 0 vie, la partie se termine.\n");

    printf("Vous pouvez controller Pacman a l'aide des touches dirrectionelles de votre clavier.\n\n");
    system("pause");
    clearscreen();
}
int main(int argc, char **argv)
{
    srand(time(NULL));
    taille_console();
    fullscreen();
    system("cls");

    int max_taille_plateau = 30;
    int min_taille_plateau = 0;

    int posX = 4, posY = 4;

    int fin = 0;

    char matrice[2][32][32];
    char touche, touche_buffer;
    int score_grille = 0, score_affiche = 0, score_recu = 0;
    int score_niveau;
    int Spawn_Pacman[2];
    int Spawn_Fantome[2];
    int vie = 2, niveau = 0;
    int animation_pacgum = 0;

    char chemin_grille[30] = "./Affichage/grille2.txt";

    int afficher_fantome;
    int fantome_au_spawn[4];
    int nbr_fantome_mange=0;


    clock_t temps_deplacement_pacman = clock();
    float buffer_temps_deplacement_pacman = 0.061;
    clock_t temps_bruit_chomp = clock();

    clock_t delai_bruit = clock();
    int num_siren = 1;
    float coef_apparition_fantome = 1.0;
    int ghost_run = 0;
    clock_t ghostrun_time = clock();
    clock_t ghostrun_Affichage = clock();
    int couleurs_fuite = 0;

    clock_t temps_deplacement_ghost = clock();



    afficher_interface();

    recuperer_grille(max_taille_plateau+2, matrice, chemin_grille, Spawn_Pacman, Spawn_Fantome, &score_niveau, fantome_au_spawn);
    afficher_grille(max_taille_plateau+2, matrice, posX, posY);

    if (fantome_au_spawn[0] == 0)
        afficher_fantome = 0;
    else
        afficher_fantome = 1;


    PERSONNAGES Pacman;
    Pacman.X = Spawn_Pacman[0];
    Pacman.Y = Spawn_Pacman[1];
    Pacman.XOld = 0;
    Pacman.YOld = 0;
    Pacman.direction = 3;
    Pacman.direction_new = -1;
    Pacman.animation = 0;
    Pacman.affichage = 'O';
    Pacman.couleur = 14;


    PERSONNAGES Blinky;
    Blinky.X = Spawn_Fantome[0];
    Blinky.Y = Spawn_Fantome[1]-2;
    Blinky.XOld = Spawn_Fantome[0];
    Blinky.YOld = Spawn_Fantome[1]-2;
    Blinky.direction = 3;
    Blinky.animation = 0;
    Blinky.affichage = 'B';
    Blinky.couleur = 12;


    PERSONNAGES Inky;
    Inky.X = Spawn_Fantome[0];
    Inky.Y = Spawn_Fantome[1]-1;
    Inky.XOld = Spawn_Fantome[0];
    Inky.YOld = Spawn_Fantome[1]-1;
    Inky.direction = 3;
    Inky.animation = 0;
    Inky.affichage = 'I';
    Inky.couleur = 3;

    PERSONNAGES Clyde;
    Clyde.X = Spawn_Fantome[0];
    Clyde.Y = Spawn_Fantome[1];
    Clyde.XOld = Spawn_Fantome[0];
    Clyde.YOld = Spawn_Fantome[1];
    Clyde.direction = 3;
    Clyde.animation = 0;
    Clyde.affichage = 'C';
    Clyde.couleur = 5;

    PERSONNAGES Pinky;
    Pinky.X = Spawn_Fantome[0];
    Pinky.Y = Spawn_Fantome[1]+1;
    Pinky.XOld = Spawn_Fantome[0];
    Pinky.YOld = Spawn_Fantome[1]+1;
    Pinky.direction = 3;
    Pinky.animation = 0;
    Pinky.affichage = 'P';
    Pinky.couleur =13;


    FMOD_SYSTEM *chompS;
    FMOD_System_Create(&chompS);
    FMOD_System_Init(chompS, 2, FMOD_INIT_NORMAL, NULL);
    FMOD_SOUND *chomp = NULL;
    FMOD_System_CreateSound(chompS, "./Son/pacman_chomp.wav", FMOD_CREATESAMPLE, 0, &chomp);

    FMOD_SYSTEM *beginS;
    FMOD_System_Create(&beginS);
    FMOD_System_Init(beginS, 2, FMOD_INIT_NORMAL, NULL);
    FMOD_SOUND *begin = NULL;
    FMOD_System_CreateSound(beginS, "./Son/pacman_beginning.wav", FMOD_CREATESAMPLE, 0, &begin);

    FMOD_SYSTEM *deathS;
    FMOD_System_Create(&deathS);
    FMOD_System_Init(deathS, 2, FMOD_INIT_NORMAL, NULL);
    FMOD_SOUND *death = NULL;
    FMOD_System_CreateSound(deathS, "./Son/pacman_death.wav", FMOD_CREATESAMPLE, 0, &death);

    FMOD_SYSTEM *eatfruitS;
    FMOD_System_Create(&eatfruitS);
    FMOD_System_Init(eatfruitS, 2, FMOD_INIT_NORMAL, NULL);
    FMOD_SOUND *eatfruit = NULL;
    FMOD_System_CreateSound(eatfruitS, "./Son/pacman_eatfruit.wav", FMOD_CREATESAMPLE, 0, &eatfruit);

    FMOD_SYSTEM *eatghostS;
    FMOD_System_Create(&eatghostS);
    FMOD_System_Init(eatghostS, 2, FMOD_INIT_NORMAL, NULL);
    FMOD_SOUND *eatghost = NULL;
    FMOD_System_CreateSound(eatghostS, "./Son/pacman_eatghost.wav", FMOD_CREATESAMPLE, 0, &eatghost);

    FMOD_SYSTEM *extrapacS;
    FMOD_System_Create(&extrapacS);
    FMOD_System_Init(extrapacS, 2, FMOD_INIT_NORMAL, NULL);
    FMOD_SOUND *extrapac = NULL;
    FMOD_System_CreateSound(extrapacS, "./Son/pacman_extrapac.wav", FMOD_CREATESAMPLE, 0, &extrapac);

    FMOD_SYSTEM *intermissionS;
    FMOD_System_Create(&intermissionS);
    FMOD_System_Init(intermissionS, 2, FMOD_INIT_NORMAL, NULL);
    FMOD_SOUND *intermission = NULL;
    FMOD_System_CreateSound(intermissionS, "./Son/pacman_intermission.wav", FMOD_CREATESAMPLE, 0, &intermission);

    FMOD_SYSTEM *sirenS;
    FMOD_System_Create(&sirenS);
    FMOD_System_Init(sirenS, 2, FMOD_INIT_NORMAL, NULL);
    FMOD_SOUND *siren1 = NULL;
    FMOD_System_CreateSound(sirenS, "./Son/pacman_Siren_1.wav", FMOD_CREATESAMPLE, 0, &siren1);

    FMOD_SOUND *siren2 = NULL;
    FMOD_System_CreateSound(sirenS, "./Son/pacman_Siren_2.wav", FMOD_CREATESAMPLE, 0, &siren2);

    FMOD_System_Init(sirenS, 2, FMOD_INIT_NORMAL, NULL);    FMOD_SOUND *siren3 = NULL;
    FMOD_System_CreateSound(sirenS, "./Son/pacman_Siren_3.wav", FMOD_CREATESAMPLE, 0, &siren3);

    FMOD_SOUND *siren4 = NULL;
    FMOD_System_CreateSound(sirenS, "./Son/pacman_Siren_4.wav", FMOD_CREATESAMPLE, 0, &siren4);


    FMOD_SOUND *ghostrun= NULL;
    FMOD_System_CreateSound(sirenS, "./Son/pacman_ghostrun.wav", FMOD_CREATESAMPLE, 0, &ghostrun);





    gotoligcol(0,55);
    printf(" ");
    score_grille = 0;
    couleur (14,0);

    FMOD_System_PlaySound(beginS, FMOD_CHANNEL_FREE, begin, 0, NULL);
    Sleep(4000);

    Blinky.apparition = clock() + (2*coef_apparition_fantome*CLOCKS_PER_SEC);
    Inky.apparition = clock() + (5*coef_apparition_fantome*CLOCKS_PER_SEC);
    Pinky.apparition = clock() + (10*coef_apparition_fantome*CLOCKS_PER_SEC);
    Clyde.apparition = clock() + (15*coef_apparition_fantome*CLOCKS_PER_SEC);


    while (fin!=1)
    {
        couleur(14,0);
        gotoligcol(2,15);
        printf("%d", score_affiche);

        gotoligcol(9,43);
        printf("%d x", vie+1);
        couleur(12,0);
        printf(" M");
        couleur (14,0);

        gotoligcol(13,45);
        printf("%d", niveau);

        clignottement_pacgum(matrice, animation_pacgum, posX, posY);
        animation_pacgum++;

        if (animation_pacgum >= 10)
        {
            animation_pacgum = 0;
        }



        if (clock() > Blinky.apparition && Spawn_Fantome[0] != 0 && fantome_au_spawn[0] == 1)
        {
            Blinky.X = Spawn_Fantome[0] - 2;
            Blinky.Y = Spawn_Fantome[1];

            Blinky.direction = 2;
            fantome_au_spawn[0] = 0;


            gotoligcol(posX+Blinky.XOld, posY + Blinky.YOld);
            printf(" ");

            Blinky.XOld = Blinky.X;
            Blinky.YOld = Blinky.Y;
        }

        if (clock() > Inky.apparition && Spawn_Fantome[0] != 1 && fantome_au_spawn[1] == 1)
        {
            Inky.X = Spawn_Fantome[0] - 2;
            Inky.Y = Spawn_Fantome[1];

            Inky.direction = 2;
            fantome_au_spawn[1] = 0;


            gotoligcol(posX+Inky.XOld, posY + Inky.YOld);
            printf(" ");

            Inky.XOld = Inky.X;
            Inky.YOld = Inky.Y;
        }

        if (clock() > Pinky.apparition && Spawn_Fantome[0] != 1 && fantome_au_spawn[2] == 1)
        {
            Pinky.X = Spawn_Fantome[0] - 2;
            Pinky.Y = Spawn_Fantome[1];

            Pinky.direction = 2;
            fantome_au_spawn[2] = 0;


            gotoligcol(posX+Pinky.XOld, posY + Pinky.YOld);
            printf(" ");

            Pinky.XOld = Pinky.X;
            Pinky.YOld = Pinky.Y;
        }

        if (clock() > Clyde.apparition && Spawn_Fantome[0] != 1 && fantome_au_spawn[3] == 1)
        {
            Clyde.X = Spawn_Fantome[0] - 2;
            Clyde.Y = Spawn_Fantome[1];

            Clyde.direction = 2;
            fantome_au_spawn[3] = 0;


            gotoligcol(posX+Clyde.XOld, posY + Clyde.YOld);
            printf(" ");

            Clyde.XOld = Clyde.X;
            Clyde.YOld = Clyde.Y;
        }


        if (clock() > delai_bruit)
        {
            if (ghost_run >= 1)
            {
                if (clock() < ghostrun_time)
                {
                    delai_bruit = clock() + (0.123* CLOCKS_PER_SEC);
                    FMOD_System_PlaySound(intermissionS, FMOD_CHANNEL_FREE, ghostrun, 0, NULL);
                }
                else
                {
                    ghost_run = 0;
                    Blinky.couleur = 12;
                    Inky.couleur = 3;
                    Pinky.couleur = 13;
                    Clyde.couleur = 5;
                }

            }
            if (num_siren == 1 && ghost_run == 0)
            {
                delai_bruit = clock() + (1.532* CLOCKS_PER_SEC);
                FMOD_System_PlaySound(intermissionS, FMOD_CHANNEL_FREE, siren1, 0, NULL);
                coef_apparition_fantome = 1.0;
            }
            else if (num_siren == 2 && ghost_run == 0)
            {
                delai_bruit = clock() + (1.146* CLOCKS_PER_SEC);
                FMOD_System_PlaySound(intermissionS, FMOD_CHANNEL_FREE, siren2, 0, NULL);
                coef_apparition_fantome = 0.75;
            }
            else if (num_siren == 3 && ghost_run == 0)
            {
                delai_bruit = clock() + (0.771* CLOCKS_PER_SEC);
                FMOD_System_PlaySound(intermissionS, FMOD_CHANNEL_FREE, siren3, 0, NULL);
                coef_apparition_fantome = 0.5;
            }
            else if (num_siren == 4 && ghost_run == 0)
            {
                delai_bruit = clock() + (0.762* CLOCKS_PER_SEC);
                FMOD_System_PlaySound(intermissionS, FMOD_CHANNEL_FREE, siren4, 0, NULL);
                coef_apparition_fantome = 0.25;
            }
        }


        if (clock() > temps_deplacement_ghost && afficher_fantome != 0);
        {
            if (ghost_run == 0)
            {
                temps_deplacement_ghost = clock() + (0.06 * CLOCKS_PER_SEC);

                IA_Clyde(matrice, &Blinky);
                IA_Clyde(matrice, &Inky);
                IA_Clyde(matrice, &Pinky);
                IA_Clyde(matrice, &Clyde);
            }
            else
            {
                temps_deplacement_ghost = clock() + (3* CLOCKS_PER_SEC);
                IA_fuite(matrice, &Blinky, Pacman);
                IA_fuite(matrice, &Inky, Pacman);
                IA_fuite(matrice, &Pinky, Pacman);
                IA_fuite(matrice, &Clyde, Pacman);

                if (clock () > ghostrun_Affichage)
                {
                    ghostrun_Affichage = clock() + (0.1*CLOCKS_PER_SEC);
                    if (couleurs_fuite == 0)
                    {
                        couleurs_fuite = 1;
                        Blinky.couleur = 15;
                        Inky.couleur = 15;
                        Pinky.couleur = 15;
                        Clyde.couleur = 15;
                    }
                    else
                    {
                        couleurs_fuite = 0;
                        Blinky.couleur = 9;
                        Inky.couleur = 9;
                        Pinky.couleur = 9;
                        Clyde.couleur = 9;
                    }
                }
            }

            affichage_IA(Clyde, matrice, posX, posY);
            affichage_IA(Blinky, matrice, posX, posY);
            affichage_IA(Inky, matrice, posX, posY);
            affichage_IA(Pinky, matrice, posX, posY);
        }

        if (clock() > temps_deplacement_pacman)
        {
            temps_deplacement_pacman = clock() + ( buffer_temps_deplacement_pacman * CLOCKS_PER_SEC);

            gestion_pacman(&Pacman, matrice, posX, posY, max_taille_plateau, min_taille_plateau);

            if (touche_buffer > 0)
            {
                touche_buffer--;

                if (Pacman.direction_new == 0) // haut
                {
                    if(matrice[1][Pacman.X-1][Pacman.Y] > 0)
                    {
                     Pacman.direction = Pacman.direction_new;
                    }
                }

                else if (Pacman.direction_new == 1) // Bas
                {
                    if(matrice [1][Pacman.X+1][Pacman.Y] > 0)
                    {
                        Pacman.direction = Pacman.direction_new;
                    }
                }

                else if (Pacman.direction_new == 2) // gauche
                {
                    if(matrice [1][Pacman.X][Pacman.Y-1] > 0)
                    {
                        Pacman.direction = Pacman.direction_new;
                    }
                }

                else if (Pacman.direction_new == 3) // haut
                {
                    if(matrice [1][Pacman.X][Pacman.Y+1] > 0)
                    {
                        Pacman.direction = Pacman.direction_new;
                    }
                }
                deplacement_perso(&Pacman, matrice);
            }
            else
            {
               deplacement_perso(&Pacman, matrice);
            }
        }


        score_recu = gestion_score(matrice, Pacman.X, Pacman.Y);
        if(score_recu > 1)
        {
            if (clock() > temps_bruit_chomp)
            {
                FMOD_System_PlaySound(chompS, FMOD_CHANNEL_FREE, chomp, 0, NULL);
                temps_bruit_chomp = clock() + (0.264* CLOCKS_PER_SEC);
            }

            score_affiche = score_affiche + score_recu;
            score_grille = score_grille + score_recu;
            num_siren = pourcentage_niveau(score_grille, score_niveau);
        }

        if (score_recu == 50)
        {
            delai_bruit = clock();
            ghostrun_time = clock() + (5 * CLOCKS_PER_SEC);
            nbr_fantome_mange = 0;
            ghost_run = 1;
        }

        else if (score_recu == -1)
        {
            vie++;
        }



        if (score_grille == score_niveau)
        {
            FMOD_System_PlaySound(chompS, FMOD_CHANNEL_FREE, intermission, 0, NULL);

            num_siren = 1;

            chemin_grille[18]++;
            niveau++;


            recuperer_grille(max_taille_plateau+2, matrice, chemin_grille, Spawn_Pacman, Spawn_Fantome, &score_niveau, fantome_au_spawn);
            afficher_grille(max_taille_plateau+2, matrice, posX, posY);

            Pacman.X = Spawn_Pacman[0];
            Pacman.Y = Spawn_Pacman[1];
            Pacman.XOld = Spawn_Pacman[0];
            Pacman.YOld = Spawn_Pacman[1];

            gotoligcol(posX+Pacman.X, posY+Pacman.Y);
            couleur(14,0);
            printf("O");
            gotoligcol(0,55);
            printf(" ");
            score_grille = 0;
            Sleep(5000);



            Blinky.apparition = clock() + (2*coef_apparition_fantome*CLOCKS_PER_SEC);
            Inky.apparition = clock() + (5*coef_apparition_fantome*CLOCKS_PER_SEC);
            Pinky.apparition = clock() + (10*coef_apparition_fantome*CLOCKS_PER_SEC);
            Clyde.apparition = clock() + (15*coef_apparition_fantome*CLOCKS_PER_SEC);

            fantome_au_spawn[0] = 1;
            fantome_au_spawn[1] = 1;
            fantome_au_spawn[2] = 1;
            fantome_au_spawn[3] = 1;

            affichage_IA(Blinky, matrice, posX, posY);
            affichage_IA(Inky, matrice, posX, posY);
            affichage_IA(Pinky, matrice, posX, posY);
            affichage_IA(Clyde, matrice, posX, posY);


            Pacman.X = Spawn_Pacman[0];
            Pacman.Y = Spawn_Pacman[1];

            Clyde.XOld = Clyde.X;
            Clyde.YOld = Clyde.Y;

            Blinky.XOld = Blinky.X;
            Blinky.YOld = Blinky.Y;

            Inky.XOld = Inky.X;
            Inky.YOld = Inky.Y;

            Pinky.XOld = Pinky.X;
            Pinky.YOld = Pinky.Y;

            Clyde.X = Spawn_Fantome[0];
            Clyde.Y = Spawn_Fantome[1];

            Inky.X = Spawn_Fantome[0];
            Inky.Y = Spawn_Fantome[1]-1;

            Blinky.X = Spawn_Fantome[0];
            Blinky.Y = Spawn_Fantome[1]-2;

            Pinky.X = Spawn_Fantome[0];
            Pinky.Y = Spawn_Fantome[1]+1;

            affichage_IA(Blinky, matrice, posX, posY);
            affichage_IA(Inky, matrice, posX, posY);
            affichage_IA(Pinky, matrice, posX, posY);
            affichage_IA(Clyde, matrice, posX, posY);

            int pause = 0;
            while(pause == 0)
            {
                while(kbhit())
                {
                    touche = getch();

                    if (touche == -32)
                    {
                        touche = getch();
                        pause = 1;
                        if (touche == 'H')
                        {
                            Pacman.direction = 0;
                        }
                        else if (touche == 'P')
                        {
                            Pacman.direction = 1;
                        }


                        else if (touche == 'K') //droite
                        {
                            Pacman.direction = 2;
                        }

                        else if (touche == 'M') //gauche
                        {
                            Pacman.direction = 3;
                        }

                    }

                    else if(touche == 27) ///ECHAP
                    {
                        fin=1;
                        break;
                    }
                }
            }
        }

        else
        {
            int i, j;
            for (i=0; i<32; i++)
            {
                for (j=0; j<32; j++)
                {
                    if (matrice[1][i][j] == 1)
                    {
                        i=32;
                        j=32;
                    }
                }
            }
        }

        int compteur_tour_mort;
        for(compteur_tour_mort = 0; compteur_tour_mort<4; compteur_tour_mort++)
        {
            switch(compteur_tour_mort)
            {
            case 0:
                {
                    fin = mort_pacman(Pacman, Pinky, &vie);
                    break;
                }
            case 1:
                {
                    fin = mort_pacman(Pacman, Blinky, &vie);
                    break;
                }
            case 2:
                {
                    fin = mort_pacman(Pacman, Inky, &vie);
                    break;
                }
            case 3:
                {
                    fin = mort_pacman(Pacman, Clyde, &vie);
                    break;
                }
            }

            if (fin == 2 && ghost_run == 0)
            {
                fin = 0;
                vie--;

                FMOD_System_PlaySound(deathS, FMOD_CHANNEL_FREE, death, 0, NULL);
                Sleep(1534);

                Pinky.apparition = clock() + (10*coef_apparition_fantome*CLOCKS_PER_SEC);
                Blinky.apparition = clock() + (2*coef_apparition_fantome*CLOCKS_PER_SEC);
                Inky.apparition = clock() + (5*coef_apparition_fantome*CLOCKS_PER_SEC);
                Clyde.apparition = clock() + (15*coef_apparition_fantome*CLOCKS_PER_SEC);

                fantome_au_spawn[0] = 1;
                fantome_au_spawn[1] = 1;
                fantome_au_spawn[2] = 1;
                fantome_au_spawn[3] = 1;

                compteur_tour_mort = 4;


                affichage_IA(Pinky, matrice, posX, posY);
                affichage_IA(Blinky, matrice, posX, posY);
                affichage_IA(Inky, matrice, posX, posY);
                affichage_IA(Clyde, matrice, posX, posY);


                Pacman.X = Spawn_Pacman[0];
                Pacman.Y = Spawn_Pacman[1];

                Clyde.XOld = Clyde.X;
                Clyde.YOld = Clyde.Y;

                Blinky.XOld = Blinky.X;
                Blinky.YOld = Blinky.Y;

                Inky.XOld = Inky.X;
                Inky.YOld = Inky.Y;

                Pinky.XOld = Pinky.X;
                Pinky.YOld = Pinky.Y;

                Clyde.X = Spawn_Fantome[0];
                Clyde.Y = Spawn_Fantome[1];

                Inky.X = Spawn_Fantome[0];
                Inky.Y = Spawn_Fantome[1]-1;

                Blinky.X = Spawn_Fantome[0];
                Blinky.Y = Spawn_Fantome[1]-2;

                Pinky.X = Spawn_Fantome[0];
                Pinky.Y = Spawn_Fantome[1]+1;

                affichage_IA(Blinky, matrice, posX, posY);
                affichage_IA(Inky, matrice, posX, posY);
                affichage_IA(Pinky, matrice, posX, posY);
                affichage_IA(Clyde, matrice, posX, posY);
            }

            else if (fin == 2 && ghost_run == 1)
            {
                switch(compteur_tour_mort)
                {
                case 0:
                    {
                        Pinky.apparition = clock() + (2*nbr_fantome_mange*CLOCKS_PER_SEC);
                        fantome_au_spawn[0] = 1;
                        affichage_IA(Pinky, matrice, posX, posY);
                        Pinky.XOld = Pinky.X;
                        Pinky.YOld = Pinky.Y;
                        Pinky.X = Spawn_Fantome[0];
                        Pinky.Y = Spawn_Fantome[1]+1;
                        affichage_IA(Pinky, matrice, posX, posY);

                        break;
                    }
                case 1:
                    {
                        Blinky.apparition = clock() + (2*nbr_fantome_mange*CLOCKS_PER_SEC);
                        fantome_au_spawn[1] = 1;
                        affichage_IA(Blinky, matrice, posX, posY);
                        Blinky.XOld = Blinky.X;
                        Blinky.YOld = Blinky.Y;
                        Blinky.X = Spawn_Fantome[0];
                        Blinky.Y = Spawn_Fantome[1]-2;
                        affichage_IA(Blinky, matrice, posX, posY);
                        fantome_au_spawn[0] = 1;

                        break;
                    }
                case 2:
                    {
                        Inky.apparition = clock() + (2*nbr_fantome_mange*CLOCKS_PER_SEC);
                        fantome_au_spawn[3] = 1;
                        affichage_IA(Inky, matrice, posX, posY);
                        Inky.XOld = Inky.X;
                        Inky.YOld = Inky.Y;
                        Inky.X = Spawn_Fantome[0];
                        Inky.Y = Spawn_Fantome[1]-1;
                        affichage_IA(Inky, matrice, posX, posY);
                        break;
                    }
                case 3:
                    {
                        Clyde.apparition = clock() + (2*nbr_fantome_mange*CLOCKS_PER_SEC);
                        fantome_au_spawn[0] = 1;
                        affichage_IA(Clyde, matrice, posX, posY);
                        Clyde.XOld = Clyde.X;
                        Clyde.YOld = Clyde.Y;
                        Clyde.X = Spawn_Fantome[0];
                        Clyde.Y = Spawn_Fantome[1]+1;
                        affichage_IA(Clyde, matrice, posX, posY);
                        break;
                    }
                }

                switch(nbr_fantome_mange)
                {
                case 0:
                    {
                        score_affiche = score_affiche + 100;
                        break;
                    }
                case 1:
                    {
                        score_affiche = score_affiche + 400;
                        break;
                    }
                case 2:
                    {
                        score_affiche = score_affiche + 500;
                        break;
                    }
                case 3:
                    {
                        score_affiche = score_affiche + 1000;
                        break;
                    }
                }
                nbr_fantome_mange++;
            }
        }

        if (vie<0)
            fin = 1;


        Sleep(60);

        while(kbhit())
        {
            touche = getch();

            if (touche == -32)
            {
                touche_buffer = 10;
                touche = getch();
                if (touche == 'H')
                {
                    Pacman.direction_new = 0;
                }
                else if (touche == 'P')
                {
                    Pacman.direction_new = 1;
                }


                else if (touche == 'K') //droite
                {
                    Pacman.direction_new = 2;
                }

                else if (touche == 'M') //gauche
                {
                    Pacman.direction_new = 3;
                }
            }

            else if(touche == 27) ///ECHAP
            {
                fin=1;
                break;
            }
        }
    }

    gotoligcol(0,0);
    afficher_interface();

    couleur(14,0);
    gotoligcol(2,15);
    printf("%d", score_affiche);

    gotoligcol(9,43);
    printf("0 x");
    couleur(12,0);
    printf(" M");
    couleur (14,0);

    gotoligcol(13,45);
    printf("%d", niveau);

    gotoligcol(12,14);
    couleur(14,0);
    printf("GAME OVER");

    couleur(15,0);
    gotoligcol(14,8);
    printf("High Score:");

    gotoligcol(27,8);
    printf("Your Score: ");
    gotoligcol(28, 11);
    printf("(Enter your nickname)");



    high_score(score_affiche);

    gotoligcol(40,0);

    return 0;
}

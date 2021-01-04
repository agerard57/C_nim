
/*#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
int main()
{

printf("    1  2  3  4  5\n");
printf("1 | %c| %c| %c| %c| %c| \n",);
printf("2 | %c| %c| %c| %c| %c| \n",);
printf("3 | %c| %c| %c| %c| %c| \n",);
printf("4 | %c| %c| %c| %c| %c| \n",);
printf("5 | %c| %c| %c| %c| %c| \n",);
printf("A toi de jouer !\n");
printf("choisir la destination 1 : (1, 2) 2 : (1, 3) 3 : (2, 1) 4 : (3, 1)\n");
printf("---> 3\n\n\n");
}

int triple(int nombre)
{
    int resultat = 0;

    resultat = 3 * nombre;  // On multiplie le nombre fourni par 3
    return resultat;       // On retourne la variable resultat qui vaut le triple de nombre
}
*/

/*
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char* argv[])
{
    int tableau[4], i = 0;

    tableau[0] = 10;
    tableau[1] = 23;
    tableau[2] = 505;
    tableau[3] = 8;

    for (i = 0; i < 4; i++)
    {
        printf("%d\n", tableau[i]);
    }

    return 0;
}
*/
/*int fonction() {
    */

    /*
int main() {
    const int VMIN = 5, VMAX = 30;
    printf("%d", VMAX);
    int nlig, ncol, nban, niveau, next;
    printf("Parametres du jeu :\n");

    printf("nombre de lignes entre 5 et 30 inclus: ");
    scanf_s_s("%d", &nlig);
    printf("nombre de colonnes : ");
    scanf_s_s("%d", &ncol);
    printf("nombre de cases bannies generees : ");
    scanf_s_s("%d", &nban);
    printf("niveau de 1 a 4 : ");
    scanf_s_s("%d", &niveau);
    printf("qui commence ? l'ordinateur(1) ou le joueur(2) : ");
    scanf_s_s("%d", &next);
    printf("C'est parti !\n\n");
}




k.


*/



#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int N, M, R, Niveau, Next;

//DEFINITION DES STRUCTURES

//Type coord
typedef struct T_Coord
{
    int coord;
}T_Coord;

//Type case
typedef struct T_Case
{
    T_Coord T_Tab_Coord[3];
    int nimber;
}T_Case;


typedef T_Case T_Tab_Case[31];

typedef T_Case T_Grille[31][31];

T_Tab_Case T_Voisines;


//FONCTIONS

int Lire_Entier(min, max)
{
    int var;
    do
    {
        scanf_s("%d", &var);
        if (var<min || var>max)
            printf("\nLe nombre doit être compris entre %d et %d. Veuillez ressaisir le nombre: ", min, max);
    } while (var<min || var>max);
    return var;
}


//Lance la fonction lire entier pour les paramètres de base
void Lire_Parametres()
{
    printf("Parametres du jeu\n-------------------\n");
    printf("Nombre de lignes: "); N = Lire_Entier(3, 30);
    printf("Nombre de colonnes: "); M = Lire_Entier(3, 30);
    printf("Nombre de pions: "); R = Lire_Entier(1, N);
    printf("Niveau (1 a 3): "); Niveau = Lire_Entier(1, 3);
    printf("A qui le tour de commencer ?\nOrdinateur (1) - Joueur (2): ");

    Next = Lire_Entier(1, 2);

    printf("\n");
}

//Fonction qui définit si une case donnée en entré a un pion ou pas

int Contient_Pion(T_Tab_Case T_Pions, int R, int x, int y)
{
    int occupee = 0; int index;
    for (index = 1; index <= R; index++)
    {
        if ((x == T_Pions[index].T_Tab_Coord[1].coord) && (y == T_Pions[index].T_Tab_Coord[2].coord))
        {
            occupee = 1;
        }
    }
    return occupee;
}


//Fonction qui place les premiers pions
void Init_Grille(T_Grille Grille, T_Tab_Case T_Pions, int N, int M, int R)
{
    int i, j;

    //Crée les R premiers pions et leurs coordonnées
    for (i = 1; i <= N; i++)
    {
        for (j = 1; j <= M; j++)
        {
            Grille[i][j].T_Tab_Coord[1].coord = i;
            Grille[i][j].T_Tab_Coord[2].coord = j;
            Grille[i][j].nimber = Nimber(T_Pions, i, j, N, M);
        }
    }
    for (i = 1; i <= R; i++)
    {
        T_Pions[i].T_Tab_Coord[1].coord = i;
        T_Pions[i].T_Tab_Coord[2].coord = 1;
        T_Pions[i].nimber = Nimber(T_Pions, i, j, N, M);
    }
}

//Création de la grille
void Affiche_Grille(T_Tab_Case T_Pions, int N, int M, int R)
{
    int i, j;
    printf("%9d", 1);
    for (i = 2; i <= M; i++)
    {
        printf("%4d", i);
    }
    printf("\n");
    for (i = 1; i <= N; i++)
    {
        printf("%5d%2c", i, '|');
        for (j = 1; j <= M; j++)
        {
            if (Contient_Pion(T_Pions, R, i, j) == 1)
                printf(" O |");
            else
                printf(" - |");
        }
        printf("\n");
    }
    printf("\n");
}


//Définition des cases voisines pour une case donnée + nombre de voisines
int Tab_Voisines(T_Tab_Case T_Voisines, int x, int y, int N, int M)
{
    int nbv;

    //NBV=1
    if ((x == N) && (y == M - 1))
    {
        T_Voisines[1].T_Tab_Coord[1].coord = x;
        T_Voisines[1].T_Tab_Coord[2].coord = y + 1;

        nbv = 1;
    }

    else if ((x == N - 1) && (y == M))
    {
        T_Voisines[1].T_Tab_Coord[1].coord = x + 1;
        T_Voisines[1].T_Tab_Coord[2].coord = y;

        nbv = 1;
    }

    //NBV=2
    else if ((x == N - 1) && (y == M - 1))
    {
        T_Voisines[1].T_Tab_Coord[1].coord = x + 1;
        T_Voisines[1].T_Tab_Coord[2].coord = y;

        T_Voisines[2].T_Tab_Coord[1].coord = x;
        T_Voisines[2].T_Tab_Coord[2].coord = y + 1;

        nbv = 2;
    }

    else if ((x == N) && (y <= M - 2))
    {
        T_Voisines[1].T_Tab_Coord[1].coord = x;
        T_Voisines[1].T_Tab_Coord[2].coord = y + 1;

        T_Voisines[2].T_Tab_Coord[1].coord = x;
        T_Voisines[2].T_Tab_Coord[2].coord = y + 2;

        nbv = 2;
    }

    else if ((x <= N - 2) && (y == M))
    {
        T_Voisines[1].T_Tab_Coord[1].coord = x + 1;
        T_Voisines[1].T_Tab_Coord[2].coord = y;

        T_Voisines[2].T_Tab_Coord[1].coord = x + 2;
        T_Voisines[2].T_Tab_Coord[2].coord = y;

        nbv = 2;
    }

    //NBV=3
    else if ((x == N - 1) && (y <= M - 2))
    {
        T_Voisines[1].T_Tab_Coord[1].coord = x + 1;
        T_Voisines[1].T_Tab_Coord[2].coord = y;

        T_Voisines[2].T_Tab_Coord[1].coord = x;
        T_Voisines[2].T_Tab_Coord[2].coord = y + 1;

        T_Voisines[3].T_Tab_Coord[1].coord = x;
        T_Voisines[3].T_Tab_Coord[2].coord = y + 2;

        nbv = 3;
    }

    else if ((x <= N - 2) && (y == M - 1))
    {
        T_Voisines[1].T_Tab_Coord[1].coord = x + 1;
        T_Voisines[1].T_Tab_Coord[2].coord = y;

        T_Voisines[2].T_Tab_Coord[1].coord = x + 2;
        T_Voisines[2].T_Tab_Coord[2].coord = y;

        T_Voisines[3].T_Tab_Coord[1].coord = x;
        T_Voisines[3].T_Tab_Coord[2].coord = y + 1;

        nbv = 3;

    }

    //NBV=4
    else if ((x <= N - 2) && (y <= M - 2))
    {
        T_Voisines[1].T_Tab_Coord[1].coord = x + 1;
        T_Voisines[1].T_Tab_Coord[2].coord = y;

        T_Voisines[2].T_Tab_Coord[1].coord = x + 2;
        T_Voisines[2].T_Tab_Coord[2].coord = y;

        T_Voisines[3].T_Tab_Coord[1].coord = x;
        T_Voisines[3].T_Tab_Coord[2].coord = y + 1;

        T_Voisines[4].T_Tab_Coord[1].coord = x;
        T_Voisines[4].T_Tab_Coord[2].coord = y + 2;

        nbv = 4;
    }

    return nbv;
}


//Hasard
int Hasard(int min, int max)
{
    return rand() % max + min;
}


//Calcul du Nimber
int Nimber(int T_Pions, int l, int c, int N, int M)
{
    int a = (N - l) % 3;
    int b = (M - c) % 3;
    int res = a ^ b;

    return res;

}


//Nim addition
int Nim_Addition(T_Tab_Case T_Pions, int R)
{
    int total, i;
    total = T_Pions[1].nimber;
    for (i = 2; i < R; i++)
    {
        total = total ^ T_Pions[i].nimber;
    }

    return total;
}

//Maj grille + affichage
void Maj_Grille(T_Tab_Case T_Pions, int N, int M, int R)
{
    int i, j, sav;
    for (i = 1; i <= R; i++)
    {
        if ((T_Pions[i].T_Tab_Coord[1].coord == N) && (T_Pions[i].T_Tab_Coord[2].coord == M) && (R > 0))
        {
            T_Pions[i].nimber = 0;
            T_Pions[i].T_Tab_Coord[1].coord = 0;
            T_Pions[i].T_Tab_Coord[2].coord = 0;

            for (j = i; j < R; j++)
            {
                sav = T_Pions[j + 1].nimber;
                T_Pions[j + 1].nimber = T_Pions[j].nimber;
                T_Pions[j].nimber = sav;


                sav = T_Pions[j + 1].T_Tab_Coord[1].coord;
                T_Pions[j + 1].T_Tab_Coord[1].coord = T_Pions[j].T_Tab_Coord[1].coord;
                T_Pions[j].T_Tab_Coord[1].coord = sav;


                sav = T_Pions[j + 1].T_Tab_Coord[2].coord;
                T_Pions[j + 1].T_Tab_Coord[2].coord = T_Pions[j].T_Tab_Coord[2].coord;
                T_Pions[j].T_Tab_Coord[2].coord = sav;
            }
        }
    }
    printf("\n");
    Affiche_Grille(T_Pions, N, M, R);
    printf("\n");
}

//Move joueur 
void Move_Joueur(T_Grille Grille, T_Tab_Case T_Pions, T_Tab_Case T_Voisines, int R, int N, int M)
{
    int i, ChoixPion, ChoixDep, nbcases;
    for (i = 1; i <= R; i++)
    {
        if (R == 1)//Dernier pion
        {
            printf("\n Plus qu'un seul pion en (%d,%d)!\n\n", T_Pions[i].T_Tab_Coord[1].coord, T_Pions[i].T_Tab_Coord[2].coord);
        }
    }

    printf("A toi de jouer !\n");

    //plusieurs pion       
    printf("Choisir un pion ");
    for (i = 1; i <= R; i++)
    {
        printf(" %d : (%d,%d) ", i, T_Pions[i].T_Tab_Coord[1].coord, T_Pions[i].T_Tab_Coord[2].coord);
    }
    printf("\n---> ");


    ChoixPion = Lire_Entier(1, R);

    nbcases = Tab_Voisines(T_Voisines, T_Pions[ChoixPion].T_Tab_Coord[1].coord, T_Pions[ChoixPion].T_Tab_Coord[2].coord, N, M);
    printf("Choisir la destination ");

    for (i = 1; i <= nbcases; i++)
    {
        printf(" %d : (%d,%d) ", i, T_Voisines[i].T_Tab_Coord[1].coord, T_Voisines[i].T_Tab_Coord[2].coord);
    }
    printf("\n---> ");


    ChoixDep = Lire_Entier(1, nbcases);

    //Modification coordonées et nimber suite au déplacement  
    T_Pions[ChoixPion].nimber = Grille[T_Voisines[ChoixDep].T_Tab_Coord[1].coord][T_Voisines[ChoixDep].T_Tab_Coord[2].coord].nimber;
    T_Pions[ChoixPion].T_Tab_Coord[1].coord = T_Voisines[ChoixDep].T_Tab_Coord[1].coord;
    T_Pions[ChoixPion].T_Tab_Coord[2].coord = T_Voisines[ChoixDep].T_Tab_Coord[2].coord;

}


//Move ordinateur hasard
void Move_Hasard(T_Grille Grille, T_Tab_Case T_Pions, T_Tab_Case T_Voisines, int pions, int N, int M)
{
    int i = 0, rep, rep2;

    rep = Hasard(1, pions);

    int nbvoisine = Tab_Voisines(T_Voisines, T_Pions[rep].T_Tab_Coord[1].coord, T_Pions[rep].T_Tab_Coord[2].coord, N, M);


    rep2 = Hasard(1, nbvoisine);

    //Modification coordonées et nimber suite au déplacement  
    T_Pions[rep].nimber = Grille[T_Voisines[rep2].T_Tab_Coord[1].coord][T_Voisines[rep2].T_Tab_Coord[2].coord].nimber;
    T_Pions[rep].T_Tab_Coord[1].coord = T_Voisines[rep2].T_Tab_Coord[1].coord;
    T_Pions[rep].T_Tab_Coord[2].coord = T_Voisines[rep2].T_Tab_Coord[2].coord;

    printf("L'ordinateur bouge le pion en (%d,%d)", T_Pions[rep].T_Tab_Coord[1].coord, T_Pions[rep].T_Tab_Coord[2].coord);
}


//Move ordinateur gagnant
void Move_Gagnant(T_Grille Grille, T_Tab_Case T_Pions, T_Tab_Case T_Voisines, int pions, int N, int M)
{
    int i, nbvoisine = 0, p, reph, cdtion, trouve = 0, pos;

    //CAS OU ON A UN PION
    if (pions == 1)
    {
        if (T_Pions[1].nimber == 0)
        {
            Move_Hasard(Grille, T_Pions, T_Voisines, pions, N, M);
        }

        else
        {
            nbvoisine = Tab_Voisines(T_Voisines, T_Pions[1].T_Tab_Coord[1].coord, T_Pions[1].T_Tab_Coord[2].coord, N, M);


            for (i = 1; i <= nbvoisine; i++)
            {
                if (Grille[T_Voisines[i].T_Tab_Coord[1].coord][T_Voisines[i].T_Tab_Coord[2].coord].nimber == 0)
                {
                    //Modification coordonées et nimber suite au déplacement  
                    T_Pions[1].nimber = Grille[T_Voisines[i].T_Tab_Coord[1].coord][T_Voisines[i].T_Tab_Coord[2].coord].nimber;
                    T_Pions[1].T_Tab_Coord[1].coord = T_Voisines[i].T_Tab_Coord[1].coord;
                    T_Pions[1].T_Tab_Coord[2].coord = T_Voisines[i].T_Tab_Coord[2].coord;
                }

            }
        }
    }

    //CAS OU ON A PLUSIEURS PIONS
    else
    {
        p = Nim_Addition(T_Pions, pions);
        if (p == 0)
        {
            Move_Hasard(Grille, T_Pions, T_Voisines, pions, N, M);
        }


        else
        {
            while (trouve != 1)
            {
                reph = Hasard(1, pions);//pour que l'ordi soit VRAIMENT aléatoire
                nbvoisine = Tab_Voisines(T_Voisines, T_Pions[reph].T_Tab_Coord[1].coord, T_Pions[reph].T_Tab_Coord[2].coord, N, M);



                cdtion = T_Pions[reph].nimber ^ p;//condition pour faire le coup gagnant

                for (i = 1; i <= nbvoisine; i++)
                {
                    if (T_Voisines[i].nimber == cdtion)
                    {
                        trouve = 1;

                        //Modification coordonées et nimber suite au déplacement  
                        T_Pions[reph].nimber = Grille[T_Voisines[i].T_Tab_Coord[1].coord][T_Voisines[i].T_Tab_Coord[2].coord].nimber;
                        T_Pions[reph].T_Tab_Coord[1].coord = T_Voisines[i].T_Tab_Coord[1].coord;
                        T_Pions[reph].T_Tab_Coord[2].coord = T_Voisines[i].T_Tab_Coord[2].coord;
                    }
                }
            }
            printf("L'ordinateur bouge le pion en (%d,%d)", T_Pions[reph].T_Tab_Coord[1].coord, T_Pions[reph].T_Tab_Coord[2].coord);
        }
    }
}

//Fin fonction

//Début du main
int main()
{
    int i, gagne = 0, choix, fin = 0, Has;
    printf("*-- Jeu de NIM --*\n\n");
    char* str1 = "TU AS PERDU !";
    char* str2 = "TU AS GAGNE !";
    char* str3;
    T_Grille Grille;
    T_Tab_Case T_Pions;
    T_Tab_Case T_Voisines;
    Lire_Parametres(&N, &M, &R, &Next, &Niveau);
    printf("\nC'est parti !\n-------------\n\n");
    Init_Grille(Grille, T_Pions, N, M, R);
    //On affiche la grille
    Affiche_Grille(T_Pions, N, M, R);
    //On "démarre" la partie jusqu'a ce qu'elle soit gagnée

    do
    {
        for (i = 1; i <= R; i++)
        {
            if ((T_Pions[i].T_Tab_Coord[1].coord == 0) && (T_Pions[i].T_Tab_Coord[2].coord == 0) && (R > 0))
            {
                R = R - 1;
            }
        }
        switch (Next)
        {
        case 1://l'ordi joue
        {
            Has = Hasard(1, 100);
            switch (Niveau)
            {
            case 1:
            {
                if (Has <= 10)
                {
                    Move_Gagnant(Grille, T_Pions, T_Voisines, R, N, M);
                    Maj_Grille(T_Pions, N, M, R);
                }
                else if (Has > 10)
                {
                    Move_Hasard(Grille, T_Pions, T_Voisines, R, N, M);
                    Maj_Grille(T_Pions, N, M, R);
                }
                break;
            }
            case 2:
            {
                if (Has <= 50)
                {
                    Move_Gagnant(Grille, T_Pions, T_Voisines, R, N, M);
                    Maj_Grille(T_Pions, N, M, R);
                }
                else if (Has > 50)
                {
                    Move_Hasard(Grille, T_Pions, T_Voisines, R, N, M);
                    Maj_Grille(T_Pions, N, M, R);
                }
                break;
            }
            case 3:
            {
                if (Has <= 90)
                {
                    Move_Gagnant(Grille, T_Pions, T_Voisines, R, N, M);
                    Maj_Grille(T_Pions, N, M, R);
                }
                else if (Has > 90)
                {
                    Move_Hasard(Grille, T_Pions, T_Voisines, R, N, M);
                    Maj_Grille(T_Pions, N, M, R);
                }
                break;
            }
            }
            Next = 2;


            //Si victoire
            if ((T_Pions[1].T_Tab_Coord[1].coord == 0) && (T_Pions[1].T_Tab_Coord[2].coord == 0) && (R == 1))
            {
                fin = 1;
                str3 = str1;
            }

            break;
        }




        case 2://joueur joue
        {
            Move_Joueur(Grille, T_Pions, T_Voisines, R, N, M);
            Maj_Grille(T_Pions, N, M, R);
            Next = 1;

            //Si victoire
            if ((T_Pions[1].T_Tab_Coord[1].coord == 0) && (T_Pions[1].T_Tab_Coord[2].coord == 0) && (R == 1))
            {
                fin = 1;
                str3 = str2;
            }
            break;
        }

        }
    } while (fin != 1);
    printf("C'est termine, %s", str3);
    printf("\n\nNous vous remercions d'avoir joué.\n");
}

//fin du main
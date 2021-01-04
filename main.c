#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define VMIN 5
#define VMAX 30

int N, M, R=1, Niveau, Next;

///////////////////////////////////
/////DEFINITION DES STRUCTURES/////
///////////////////////////////////

typedef struct T_Coord
{
   int coord;
}T_Coord;

typedef struct T_Case
{
   T_Coord T_Tab_Coord[VMIN];
   int nimber;
}T_Case;


typedef T_Case T_Tab_Case[VMAX+1]; //creation d'un tableau de type T_case

typedef T_Case T_Grille[VMAX+1][VMAX+1];  //creation d'un tableau 2 dimensions de type T_case

T_Tab_Case T_Voisines;

///////////////////
/////FONCTIONS/////
///////////////////

int Lire_Entier(min, max)      //verifie si le nombre saisie est correct ou non
{
   int var;
   do
   {
      scanf("%d", &var);
      if(var<min || var>max)
         printf("\nNombre incorrect, le nombre doit etre entre %d et %d. Veuillez ressaisir le nombre: ", min, max);
   }
   while(var<min || var>max);
   return var;
}

//declaration des parametres

void Lire_Parametres()
{
   printf("Parametres du jeu\n-------------------\n");
   printf("Nombre de lignes: "); N=Lire_Entier(5,30);   //Lance la fonction lire entier pour les paramètres de base
   printf("Nombre de colonnes: "); M=Lire_Entier(5,30);
   printf("1.Niveau debutant\n");
   printf("2.Niveau moyen\n");
   printf("3.Niveau expert\n");
   printf("4.Niveau virtuose\n");
   printf("Niveau (1 a 4): "); Niveau=Lire_Entier(1,4);
 /*printf("Nombre de case bannie");*/
   printf("A qui le tour de commencer ?\nOrdinateur (1) - Joueur (2): ");

   Next=Lire_Entier(1,2);

   printf("\n");
}

//Fonction qui définit si une case donnée en entré a un pion ou pas

int Contient_Pion(T_Tab_Case T_Pions,int R, int x, int y)
{
   int occupee=0;

      if ((x==T_Pions[R].T_Tab_Coord[1].coord)&&(y==T_Pions[R].T_Tab_Coord[2].coord))
      {
         occupee=1;
      }

   return occupee;
}


//Fonction qui initialise le premier pion sur la grille
void Init_Grille(T_Grille Grille, T_Tab_Case T_Pions, int N, int M, int R)
{
   int i,j;

   //Crée le pion et ses coordonnées
   for(i=1; i<=N; i++)
   {
      for(j=1;j<=M;j++)
      {
         Grille[i][j].T_Tab_Coord[1].coord=i;
         Grille[i][j].T_Tab_Coord[2].coord=j;
         Grille[i][j].nimber=Nimber(T_Pions,i,j,N,M);
      }
   }
   for(i=1;i<=R;i++)
   {
      T_Pions[i].T_Tab_Coord[1].coord=i;
      T_Pions[i].T_Tab_Coord[2].coord=1;
      T_Pions[i].nimber=Nimber(T_Pions,i,j,N,M);
   }
}

//Création de la grille et affichage
void Affiche_Grille(T_Tab_Case T_Pions,int N,int M,int R)
{
   int i,j;
   printf("%9d",1);  //insertion du 1
   for (i=2;i<=M;i++)
   {
      printf("%4d",i); //insertion du nombre de colonne
   }
   printf("\n");
   for (i=1;i<=N;i++)
   {
      printf("%5d%2c",i,'|'); //insertion du nombre de ligne
      for (j=1;j<=M;j++)
      {
         if(Contient_Pion(T_Pions,R,i,j)==1) //verifie si il y a la présence du pion
            printf(" O |");
       /*  else if (bannie)
            printf(" x |"); //case bannie (ne marche pas)*/
         else
            printf(" - |");
      }
      printf("\n");
   }
   printf("\n");
}


//Définition des cases voisines pour une case donnée + nombre de voisines
int Tab_Voisines(T_Tab_Case T_Voisines,int x,int y,int N,int M)
{
   int nbv;

   //cas ou il y a une voisine
   if  ((x==N)&&(y==M-1))
   {
      T_Voisines[1].T_Tab_Coord[1].coord=x;
      T_Voisines[1].T_Tab_Coord[2].coord=y+1;
      
      nbv=1;
   }
   
   else if((x==N-1)&&(y==M))
   {
      T_Voisines[1].T_Tab_Coord[1].coord=x+1;
      T_Voisines[1].T_Tab_Coord[2].coord=y;
      
      nbv=1;
   }
   
   //cas ou il y a deux voisines
   else if ((x==N-1)&&(y==M-1))
   {
      T_Voisines[1].T_Tab_Coord[1].coord=x+1;
      T_Voisines[1].T_Tab_Coord[2].coord=y;
   
      T_Voisines[2].T_Tab_Coord[1].coord=x;
      T_Voisines[2].T_Tab_Coord[2].coord=y+1;
      
      nbv=2;
   }
   
   else if ((x==N)&&(y<=M-2))
   {
      T_Voisines[1].T_Tab_Coord[1].coord=x;
      T_Voisines[1].T_Tab_Coord[2].coord=y+1;
   
      T_Voisines[2].T_Tab_Coord[1].coord=x;
      T_Voisines[2].T_Tab_Coord[2].coord=y+2;
      
      nbv=2;
   }
   
   else if ((x<=N-2)&&(y==M))
   {
      T_Voisines[1].T_Tab_Coord[1].coord=x+1;
      T_Voisines[1].T_Tab_Coord[2].coord=y;
   
      T_Voisines[2].T_Tab_Coord[1].coord=x+2;
      T_Voisines[2].T_Tab_Coord[2].coord=y;
      
      nbv=2;
   }
   
   //cas ou il y a trois voisine
   else if ((x==N-1)&&(y<=M-2))
   {
      T_Voisines[1].T_Tab_Coord[1].coord=x+1;
      T_Voisines[1].T_Tab_Coord[2].coord=y;
   
      T_Voisines[2].T_Tab_Coord[1].coord=x;
      T_Voisines[2].T_Tab_Coord[2].coord=y+1;
   
      T_Voisines[3].T_Tab_Coord[1].coord=x;
      T_Voisines[3].T_Tab_Coord[2].coord=y+2;
      
      nbv=3;
   }
   
   else if ((x<=N-2)&&(y==M-1))
   {
      T_Voisines[1].T_Tab_Coord[1].coord=x+1;
      T_Voisines[1].T_Tab_Coord[2].coord=y;
   
      T_Voisines[2].T_Tab_Coord[1].coord=x+2;
      T_Voisines[2].T_Tab_Coord[2].coord=y;
   
      T_Voisines[3].T_Tab_Coord[1].coord=x;
      T_Voisines[3].T_Tab_Coord[2].coord=y+1;
      
      nbv=3;
   
   }
   
   //cas ou il y a quatre voisine
   else if ((x<=N-2)&&(y<=M-2))
   {
      T_Voisines[1].T_Tab_Coord[1].coord=x+1;
      T_Voisines[1].T_Tab_Coord[2].coord=y;
   
      T_Voisines[2].T_Tab_Coord[1].coord=x+2;
      T_Voisines[2].T_Tab_Coord[2].coord=y;
   
      T_Voisines[3].T_Tab_Coord[1].coord=x;
      T_Voisines[3].T_Tab_Coord[2].coord=y+1;
   
      T_Voisines[4].T_Tab_Coord[1].coord=x;
      T_Voisines[4].T_Tab_Coord[2].coord=y+2;
      
      nbv=4;
   }

   return nbv;
}


//genere un nombre au hasard
int Hasard(int min,int max)
{
   return rand()%max+min;
}


//Calcul du Nimber
int Nimber(int T_Pions,int l,int c,int N,int M)
{
   int a=(N-l)%3;
   int b=(M-c)%3;
   int res=a^b;

   return res;

}

//Mise a jour de la grille + affichage
void Maj_Grille(T_Tab_Case T_Pions, int N,int M,int R)
{
   int i,j,sav;
   for (i=1;i<=R;i++)
   {
      if((T_Pions[i].T_Tab_Coord[1].coord==N)&&(T_Pions[i].T_Tab_Coord[2].coord==M)&&(R>0))
      {
         T_Pions[i].nimber=0;
         T_Pions[i].T_Tab_Coord[1].coord=0;
         T_Pions[i].T_Tab_Coord[2].coord=0;
           
         for(j=i;j<R;j++)
         {
            sav=T_Pions[j+1].nimber;
            T_Pions[j+1].nimber=T_Pions[j].nimber;
            T_Pions[j].nimber=sav;
               
               
            sav=T_Pions[j+1].T_Tab_Coord[1].coord;
            T_Pions[j+1].T_Tab_Coord[1].coord=T_Pions[j].T_Tab_Coord[1].coord;
            T_Pions[j].T_Tab_Coord[1].coord=sav;
               
               
            sav=T_Pions[j+1].T_Tab_Coord[2].coord;
            T_Pions[j+1].T_Tab_Coord[2].coord=T_Pions[j].T_Tab_Coord[2].coord;
            T_Pions[j].T_Tab_Coord[2].coord=sav;
         }
      }
   }
   printf("\n");
   Affiche_Grille(T_Pions,N,M,R);
   printf("\n");
}

//Coup du joueur
void Coup_Joueur(T_Grille Grille, T_Tab_Case T_Pions, T_Tab_Case T_Voisines, int R, int N, int M)
{
   int i, ChoixPion, ChoixDep, nbcases;

   printf("A votre tour !\n");
     
     
   nbcases=Tab_Voisines(T_Voisines,T_Pions[R].T_Tab_Coord[1].coord,T_Pions[R].T_Tab_Coord[2].coord,N,M); //on initialise les cases voisines
   printf("Choisir la destination ");
     
   for (i=1;i<=nbcases;i++)
   {
      printf(" %d : (%d,%d) ",i,T_Voisines[i].T_Tab_Coord[1].coord,T_Voisines[i].T_Tab_Coord[2].coord);
   }
   printf("\n---> ");
     
     
   ChoixDep=Lire_Entier(1,nbcases);
     
   //Modification coordonées et nimber suite au déplacement  
   T_Pions[R].nimber=Grille[T_Voisines[ChoixDep].T_Tab_Coord[1].coord][T_Voisines[ChoixDep].T_Tab_Coord[2].coord].nimber;
   T_Pions[R].T_Tab_Coord[1].coord=T_Voisines[ChoixDep].T_Tab_Coord[1].coord;
   T_Pions[R].T_Tab_Coord[2].coord=T_Voisines[ChoixDep].T_Tab_Coord[2].coord;

}


//Coup ordinateur hasard
void Coup_Hasard(T_Grille Grille,T_Tab_Case T_Pions,T_Tab_Case T_Voisines,int pions, int N, int M)
{
   int i=0,rep,rep2;
   
   rep=Hasard(1,pions);

   int nbvoisine=Tab_Voisines(T_Voisines,T_Pions[rep].T_Tab_Coord[1].coord,T_Pions[rep].T_Tab_Coord[2].coord,N,M);

      
   rep2=Hasard(1,nbvoisine);

   //Modification coordonées et nimber suite au déplacement  
   T_Pions[rep].nimber=Grille[ T_Voisines[rep2].T_Tab_Coord[1].coord ] [ T_Voisines[rep2].T_Tab_Coord[2].coord ].nimber;
   T_Pions[rep].T_Tab_Coord[1].coord=T_Voisines[rep2].T_Tab_Coord[1].coord;
   T_Pions[rep].T_Tab_Coord[2].coord=T_Voisines[rep2].T_Tab_Coord[2].coord;
    
   printf("L'ordinateur bouge le pion en (%d,%d)",T_Pions[rep].T_Tab_Coord[1].coord,T_Pions[rep].T_Tab_Coord[2].coord);
}


//Coup ordinateur gagnant
void Coup_Gagnant(T_Grille Grille,T_Tab_Case T_Pions,T_Tab_Case T_Voisines,int pions, int N, int M)
{
   int i,nbvoisine=0;

   if (T_Pions[R].nimber==0)
   {
      Coup_Hasard(Grille,T_Pions,T_Voisines,pions,N,M);
   }
           
   else
   {  
      nbvoisine=Tab_Voisines(T_Voisines,T_Pions[R].T_Tab_Coord[1].coord,T_Pions[1].T_Tab_Coord[2].coord,N,M);
       
        
      for(i=1;i<=nbvoisine;i++)
      {
         if(Grille[ T_Voisines[i].T_Tab_Coord[1].coord ] [ T_Voisines[i].T_Tab_Coord[2].coord ].nimber==0)
         {
               //Modification coordonées et nimber suite au déplacement  
            T_Pions[R].nimber=Grille[T_Voisines[i].T_Tab_Coord[1].coord] [T_Voisines[i].T_Tab_Coord[2].coord].nimber;
            T_Pions[R].T_Tab_Coord[1].coord=T_Voisines[i].T_Tab_Coord[1].coord;
            T_Pions[R].T_Tab_Coord[2].coord=T_Voisines[i].T_Tab_Coord[2].coord;
         }
         
      }
   }
}

//////////////////////
/////Fin fonction/////
//////////////////////

/////////////////////////
//////Début du main//////
/////////////////////////

int main()
{  char rep;
   do{
      int i,fin=0,Has;
      printf("Demarage du -[Jeu de NIM]- \n\n");
      char *str1="Vous avez perdu, dommage !";    //message si perdu
      char *str2="Vous avez gagne, bravo !";     //message si gagne
      char *str3;
      T_Grille Grille;
      T_Tab_Case T_Pions;           
      T_Tab_Case T_Voisines; 
      Lire_Parametres(&N,&M,&R,&Next,&Niveau);   //on lit les paramètres du jeux
      printf("\nC'est parti !\n-------------\n\n");
      Init_Grille(Grille,T_Pions,N,M,R);    //On initialise la grille
      Affiche_Grille(T_Pions,N,M,R);    //On affiche la grille
   
   //On commence la partie jusqu'a ce qu'elle soit gagnée
   
      do
      {
         switch(Next)
         {
            case 1://l'ordi joue
               {
                  Has=Hasard(1,100); //nombre au hasard pour le niveau
                  switch(Niveau)
                  {
                     case 1:
                        {
                           if(Has<=10)
                           {
                              Coup_Gagnant(Grille,T_Pions,T_Voisines,R,N,M);
                              Maj_Grille(T_Pions,N,M,R);
                           }
                           else if(Has>10)
                           {
                              Coup_Hasard(Grille,T_Pions,T_Voisines,R,N,M);
                              Maj_Grille(T_Pions,N,M,R);
                           }
                           break;
                        }
                     case 2:
                        {
                           if(Has<=50)
                           {
                              Coup_Gagnant(Grille,T_Pions,T_Voisines,R,N,M);
                              Maj_Grille(T_Pions,N,M,R);
                           }
                           else if(Has>50)
                           {
                              Coup_Hasard(Grille,T_Pions,T_Voisines,R,N,M);
                              Maj_Grille(T_Pions,N,M,R);
                           }
                           break;
                        }
                     case 3:
                        {
                           if(Has<=90)
                           {
                              Coup_Gagnant(Grille,T_Pions,T_Voisines,R,N,M);
                              Maj_Grille(T_Pions,N,M,R);
                           }
                           else if(Has>90)
                           {
                              Coup_Hasard(Grille,T_Pions,T_Voisines,R,N,M);
                              Maj_Grille(T_Pions,N,M,R);
                           }
                           break;
                        }
                     case 4:
                        {
                           {
                              Coup_Gagnant(Grille,T_Pions,T_Voisines,R,N,M);
                              Maj_Grille(T_Pions,N,M,R);
                           }
                           break;
                        }
                  }
                  Next=2;
               
               
               //Si defaite
                  if((T_Pions[1].T_Tab_Coord[1].coord==0)&&(T_Pions[1].T_Tab_Coord[2].coord==0)&&(R==1))
                  {
                     fin=1;
                     str3=str1;
                  }
               
                  break;
               }
                     
            
            case 2://joueur joue
               {
                  Coup_Joueur(Grille,T_Pions,T_Voisines,R,N,M); 
                  Maj_Grille(T_Pions,N,M,R);
                  Next=1;
               
               //Si victoire
                  if((T_Pions[1].T_Tab_Coord[1].coord==0)&&(T_Pions[1].T_Tab_Coord[2].coord==0)&&(R==1))
                  {
                     fin=1;
                     str3=str2;
                  }
                  break;
               }    
         }
      }
      while (fin!=1);
      printf(" %s \n",str3);
      printf("Partie termine !");
      printf("\n\n Voulez-vous rejouer ? Y/N \n");
      while(getchar()!='\n');
      scanf("%c",&rep);
   }while(rep=='Y'||rep=='y');
   printf("Le jeu est termine ! Merci d'avoir jouer !");
}
   
/////////////////////
/////fin du main/////
/////////////////////
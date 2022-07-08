#include <stdio.h> 
	#include <stdlib.h> 
	// #include "graphe_liste.h" 
    #include "cellule.h"
    #include "fifo.h"
    #include "fifo.c"
    #include "graphe.h"
    #include "graphe.c"
	 
	 
	int N=10; 
	 
	 
	int main(int argc, char *argv[]) 
	{ 
	  pSommet* graphe=NULL; 
	  graphe=CreerGraphe(N); 
	  graphe=CreerArete(graphe,0,1,10);
	  graphe=CreerArete(graphe,1,4,10); 
	  graphe=CreerArete(graphe,1,3,10); 
	  graphe=CreerArete(graphe,1,9,10); 
	  graphe=CreerArete(graphe,1,8,10); 
	  graphe=CreerArete(graphe,3,2,10); 
	  graphe=CreerArete(graphe,2,7,10); 
	  graphe=CreerArete(graphe,7,4,10); 
	 
	 
	  affiche(graphe,N); 
	  //InitialParcourLongueur(graphe,N); 
	  printf("\n"); 
	  InitialParcourLongueur(graphe,N); 
       ParcourLongueur(graphe,N);
	  system("PAUSE"); 
	  return 0; 
	} 
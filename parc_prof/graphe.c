#include <stdio.h>
#include <stdli.h>
#include "graphe.h"





	void InitialParcourProfondeur(pSommet* graphe, int taille){ 
	     /*Initialisation de la couleur des sommets*/ 
	     /*N=Noir, deja vu(déjà traité).  B=Blanc a voir*/ 
	     printf("\n***PARCOURS EN PROFONDEUR***\n"); 
	     int i; 
	     for(i=0;i<taille;i++){ 
	       graphe[i]->couleur='B'; 
	     } 
	     for(i=0;i<taille;i++){ 
	       if(graphe[i]->couleur=='B'){ 
	       printf("%d,",graphe[i]->valeur); 
	       graphe[i]->couleur='N'; 
	       pArc Temparc=graphe[i]->arc; 
	       while(!(Temparc==NULL)){ 
	         ParcourProfondeur(graphe,Temparc->sommet,taille); 
       Temparc=Temparc->arc_suivant; 
	       } 
	       } 
	     } 
	     return; 
	} 
	
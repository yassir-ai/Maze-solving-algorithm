#include <stdio.h> 
#include <stdlib.h> 
	 
	 
	/*taille max de sommet*/ 
	struct Arc { 
	       int sommet; 
	       int valeur; 
	       struct Arc* arc_suivant; 
	}; 
	 
	struct Sommet{ 
	       struct Arc* arc; 
	       int valeur; 
	       char couleur; 
	}; 
	 
 
	typedef struct Arc* pArc; 
	typedef struct Sommet* pSommet; 
	 
	 
	pSommet* CreerGraphe(int taille); 
	pSommet* CreerArete(pSommet* graphe,int s1,int s2,int valeur); 
	void affiche(pSommet* graphe, int taille); 
	 
	void ParcourProfondeur(pSommet* graphe,int s, int taille); 
	void InitialParcourProfondeur(pSommet* graphe,int taille); 
	 


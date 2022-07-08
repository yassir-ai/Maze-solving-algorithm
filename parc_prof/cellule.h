/*cellule.h*/ 

#include<stdio.h>
#include<stdlib.h>
 
	typedef int typage; 
	 
	struct  _cellule { 
	   typage element; 
	   struct  _cellule *suivant; 
	}; 
	 
	typedef struct _cellule* Cellule;
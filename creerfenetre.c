#include <SDL2/SDL.h>
#include <stdio.h>

/************************************/
/*  exemple de création de fenêtres */
/************************************/




int main(int argc, char **argv) {
  (void)argc;
  (void)argv;
  int i ;
  int j ;
  SDL_Window *window_1 = NULL,               // Future fenêtre de gauche
      *window_2 = NULL;                      // Future fenêtre de droite

  /* Initialisation de la SDL  + gestion de l'échec possible */
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    SDL_Log("Error : SDL initialisation - %s\n", SDL_GetError());      // l'initialisation de la SDL a échoué 
    exit(EXIT_FAILURE);
  }

  /* Création de la fenêtre de gauche */
 
 for(j=0 ; j<500;j+=20)
{ for(i=0 ; i<900; i+=20)
{



  window_1 = SDL_CreateWindow(
      "Fenêtre à gauche",                    // codage en utf8, donc accents possibles
      0, j+20,                                  // coin haut gauche en haut gauche de l'écran
      300, 100,                              // largeur = 400, hauteur = 300
      SDL_WINDOW_RESIZABLE);
              // redimensionnable

 
 
 
 
 
 
 
  if (window_1 == NULL) {
    SDL_Log("Error : SDL window 1 creation - %s\n", SDL_GetError());   // échec de la création de la fenêtre
    SDL_Quit();
    exit(EXIT_FAILURE);
  }
  /* Création de la fenêtre de droite */
  
  

  
window_2 = SDL_CreateWindow(
      "Fenêtre à droite",                    // codage en utf8, donc accents possibles
      i+20, 0,                                // à droite de la fenêtre de gauche
      300, 100,                              // largeur = 500, hauteur = 300
      0);
}
}

  if (window_2 == NULL) {
    /* L'init de la SDL : OK
       fenêtre 1 :OK
       fenêtre 2 : échec */
    SDL_Log("Error : SDL window 2 creation - %s\n", SDL_GetError());   // échec de la création de la fenêtre 
    SDL_DestroyWindow(window_1);
    SDL_Quit();
    exit(EXIT_FAILURE);
  }

  /* Normalement, on devrait ici remplir les fenêtres... */
  SDL_Delay(5000);                           // Pause exprimée  en ms

  /* et on referme tout ce qu'on a ouvert en ordre inverse de la création */
  SDL_DestroyWindow(window_2);
  SDL_DestroyWindow(window_1);

  SDL_Quit();
  return 0;
}

#include "prototypes.h"


SDL_Texture *loadImage(char *name)
{

    /* Charge les images avec SDL Image dans une SDL_Surface */

    SDL_Surface *loadedImage = NULL;
    SDL_Texture *texture = NULL;
    loadedImage = IMG_Load(name);

    if (loadedImage != NULL)
    {
        // Conversion de l'image en texture
        texture = SDL_CreateTextureFromSurface(getrenderer(), loadedImage);

        // On se débarrasse du pointeur vers une surface
        SDL_FreeSurface(loadedImage);
        loadedImage = NULL;
    }
    else
        printf("L'image n'a pas pu être chargée! SDL_Error : %s\n", SDL_GetError());

    return texture;

}


void drawImage(SDL_Texture *image, int x, int y)
{

    SDL_Rect dest;

    /* Règle le rectangle à dessiner selon la taille de l'image source */
    dest.x = x;
    dest.y = y;

    /* Dessine l'image entière sur l'écran aux coordonnées x et y */
    SDL_QueryTexture(image, NULL, NULL, &dest.w, &dest.h);
    SDL_RenderCopy(getrenderer(), image, NULL, &dest);

}



void envoiImage(void)
{
    // Affiche l'écran
    SDL_RenderPresent(getrenderer());

    // Délai pour laisser respirer le proc
    SDL_Delay(1);
}

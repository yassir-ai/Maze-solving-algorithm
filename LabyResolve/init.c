#include "prototypes.h"

Systeme sys;
Variables var;
Affichage aff;

SDL_Renderer *renderer;

SDL_Renderer *getrenderer(void)
{
    return renderer;
}

void init(char *title)
{
    /* On crée la fenêtre, représentée par le pointeur jeu.window en utilisant la largeur et la
    hauteur définies dans les defines (defs.h).
    Nouveautés SDL2 : on peut centrer la fenêtre avec SDL_WINDOWPOS_CENTERED, et choisir la taille
    de la fenêtre, pour que la carte graphique l'agrandisse automatiquement. Notez aussi qu'on peut
    maintenant créer plusieurs fenêtres. */

    sys.screen = SDL_CreateWindow(title,
                                  SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED,
                                  sys.ecran_w, sys.ecran_h,
                                  SDL_WINDOW_SHOWN);




    //On crée un renderer pour la SDL et on active la synchro verticale : VSYNC
    renderer = SDL_CreateRenderer(sys.screen, -1, SDL_RENDERER_PRESENTVSYNC);

    // Si on n'y arrive pas, on quitte en enregistrant l'erreur dans stdout.txt
    if (sys.screen == NULL || renderer == NULL)
    {
        printf("Impossible d'initialiser le mode écran à %d x %d: %s\n", sys.ecran_w,
                                                                    sys.ecran_h, SDL_GetError());
        exit(1);
    }

    //Initialisation du chargement des images png avec SDL_Image 2
    int imgFlags = IMG_INIT_PNG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) )
    {
        printf( "SDL_image n'a pu être initialisée! SDL_image Error: %s\n", IMG_GetError() );
        exit(1);
    }

    //On cache le curseur de la souris
    SDL_ShowCursor(SDL_DISABLE);

}

void loadParam(void)
{
    sys.ecran_w = 640;
    sys.ecran_h = 480;
    var.etat = ETAT_RECHERCHE;
}

void clean(SDL_Texture *texture)
{
    if (texture != NULL)
    {
        SDL_DestroyTexture(texture);
        texture = NULL;
    }
}

void cleanup()
{
    cleanImg();

    //On fait le ménage et on remet les pointeurs à NULL
    SDL_DestroyRenderer(renderer);
    renderer = NULL;
    SDL_DestroyWindow(sys.screen);
    sys.screen = NULL;

    //On quitte la SDL
    SDL_Quit();
}

void cleanImg(void)
{
    int i = 0;
    for(i = 0; i < 10; i++)
    {
        clean(aff.img[i]);
    }
}

void initImg()
{
    aff.img[IMG_MUR] = loadImage("img/mur.png");
    aff.img[IMG_SOL] = loadImage("img/sol.png");
    aff.img[IMG_BOT] = loadImage("img/bot.png");
    aff.img[IMG_EXIT] = loadImage("img/exit.png");
}

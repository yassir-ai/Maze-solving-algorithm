#include "prototypes.h"

Variables var;
Affichage aff;

int main(int argc, char *argv[])
{
    unsigned int frameLimit = SDL_GetTicks() + 16;
    int go;

    loadParam();
    srand(time(NULL));

    init("LabyResolve - Oktopuss - 2018 - Press ESC to EXIT");

    loadAll();

    atexit(cleanup);
    go = 1;
    while (go == 1)
    {
        // Fonction principale à laquelle on renvoie l'état du programme.
        event(var.etat);

        // Gestion des 60 fps (1000ms/60 = 16.6 -> 16
        delay(frameLimit);
        frameLimit = SDL_GetTicks() + 16;
    }
    exit(0);
}

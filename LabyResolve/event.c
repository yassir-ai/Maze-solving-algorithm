#include "prototypes.h"

Input input;
Variables var;
Affichage aff;

void event(int etat)
{
    gestionInputs(&input);

    switch(var.etat)
    {
        case ETAT_RECHERCHE:
            gestionGame();
            drawGame();
            break;

        case ETAT_REUSSITE:
            drawReussite();
            break;

        case ETAT_ERROR:
            drawError();
            break;

        default:
            break;
    }

    // Envoi de l'image
    envoiImage();
}

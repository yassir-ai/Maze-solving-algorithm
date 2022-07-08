#include "struct.h"

Affichage aff;
Variables var;

void loadAll(void)
{
    initImg();
    loadMap();
    gestionDebutGame();
}

void loadMap(void)
{
    FILE* file = NULL;
    file = fopen("map/laby.map", "r");
    int x = 0, y = 0, k = 0;

    if (file != NULL)
    {
        for(y = 0; y < Y; y++)
        {
            for(x = 0; x < X; x++)
            {
                fscanf(file, "%d", &var.tilemap[y][x]);
                var.parcours[y][x] = var.tilemap[y][x];
            }
        }

        fclose(file);
    }
    else
    {
        var.etat = ETAT_ERROR;
    }
}

void gestionDebutGame(void)
{
    int posBotX = 0, posBotY = 0;

    posBotX = 1;
    posBotY = 0;

    // Début du Bot
    var.pos[POS_BOT_X] = posBotX * 32;
    var.pos[POS_BOT_Y] = posBotY * 32;

    var.objectif = 0;
    var.marquage = 1;
    var.precedent = GAUCHE;
}

void gestionGame(void)
{
    testVictoire();

    int passage = 0, nbDirections = 0;

    nbDirections = testDirections();

    if(nbDirections > 1)
        var.marquage = 0;

    if(var.marquage == 1)
        marquage();

    if(var.precedent != HAUT)
    {
        passage = deplacement(HAUT);
    }

    if(passage == 0)
    {
        if(var.precedent != BAS)
        {
            passage = deplacement(BAS);
        }
    }

    if(passage == 0)
    {
        if(var.precedent != GAUCHE)
        {
            passage = deplacement(GAUCHE);
        }
    }

    if(passage == 0)
    {
        if(var.precedent != DROITE)
        {
            passage = deplacement(DROITE);
        }
    }

    // si cul de sac
    if(passage == 0)
    {
        var.marquage = 1;
        marquage();
        depl(var.precedent);
    }

}

void testVictoire(void)
{
    int x = 0, y = 0;

    // Récupération position du bot
    x = var.pos[POS_BOT_X] / 32;
    y = var.pos[POS_BOT_Y] / 32;

    if(var.tilemap[y][x] == ARRIVEE)
        var.etat = ETAT_REUSSITE;
}

int testDirections(void)
{
    int test = 0, resultat = 0;

    test = testDirection(HAUT);
    if(test != 0)
        resultat++;

    test = testDirection(BAS);
    if(test != 0)
        resultat++;

    test = testDirection(GAUCHE);
    if(test != 0)
        resultat++;

    test = testDirection(DROITE);
    if(test != 0)
        resultat++;

    return resultat;
}

void marquage(void)
{
    int posBotX = 0, posBotY = 0;
    posBotX = var.pos[POS_BOT_X] / 32;
    posBotY = var.pos[POS_BOT_Y] / 32;
    var.parcours[posBotY][posBotX] = 0;
}

int testDirection(int direction)
{
    int resultat = 0;
    int posBotX = 0, posBotY = 0;
    int x = 0, y = 0;

    // Récupération position du bot
    posBotX = var.pos[POS_BOT_X] / 32;
    posBotY = var.pos[POS_BOT_Y] / 32;

    switch(direction)
    {
        case HAUT:
            x = posBotX;
            y = posBotY - 1;
            break;

        case BAS:
            x = posBotX;
            y = posBotY + 1;
            break;

        case GAUCHE:
            x = posBotX - 1;
            y = posBotY;
            break;

        case DROITE:
            x = posBotX + 1;
            y = posBotY;
            break;
    }

    if((x >= 0) && (y >= 0))
    {
        resultat = var.parcours[y][x];
    }

    return resultat;
}

int deplacement(int direction)
{
    int test = 0, resultat = 0;

    test = testDirection(direction);
    if(test != 0)
    {
        depl(direction);
        resultat = 1;
    }

    return resultat;
}

void depl(int direction)
{
    switch(direction)
    {
        case HAUT:
            var.pos[POS_BOT_Y] -= 32;
            var.precedent = BAS;
            break;

        case BAS:
            var.pos[POS_BOT_Y] += 32;
            var.precedent = HAUT;
            break;

        case GAUCHE:
            var.pos[POS_BOT_X] -= 32;
            var.precedent = DROITE;
            break;

        case DROITE:
            var.pos[POS_BOT_X] += 32;
            var.precedent = GAUCHE;
            break;

    }


    SDL_Delay(100);
}


void delay(unsigned int frameLimit)
{
    // Gestion des 60 fps (images/stories/seconde)
    unsigned int ticks = SDL_GetTicks();

    if (frameLimit < ticks)
    {
        return;
    }

    if (frameLimit > ticks + 16)
    {
        SDL_Delay(16);
    }

    else
    {
        SDL_Delay(frameLimit - ticks);
    }
}

// Fonction permettant de récupérer une ligne dans un fichier externe.
void recupLigne(char *affiche, FILE* file)
{
    int nb;
    char recup[1000] = "";
    fgets(recup, 1000, file);       // On récupère la ligne
    nb = strlen(recup);             // On calcule le nombre de caractères
    nb++;                           // On incrémente pour pouvoir revenir suffisement loin en arrière
    fseek(file, -nb, SEEK_CUR);     // On reviens en arrière en utilisant nb
    nb--;                           // On décrémente nb pour récupérer la valeur initiale
    fgets(recup, nb, file);         // On récupère la ligne avec le nombre exact de caractères
    sprintf(affiche, "%s", recup);  // On colle la ligne
    fgets(recup, 1000, file);       // On récupère la fin de la ligne
}

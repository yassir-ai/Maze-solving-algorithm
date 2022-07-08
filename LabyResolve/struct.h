#ifndef DEF_STRUCTS
#define DEF_STRUCTS

#include "defs.h"

typedef struct Systeme
{
    int init;
    int type_ecran, ecran_w, ecran_h;
    int musiques, sons;

    SDL_Window *screen;
}Systeme;

typedef struct Input
{
    int echap;
} Input;

typedef struct Variables
{
    int etat;
    int tilemap[30][30];
    int parcours[30][30];
    int pos[100];
    int precedent, marquage;
    int objectif;
} Variables;

typedef struct Affichage
{
    char *chaine[1000], *version[10];
    SDL_Texture *img[3000];

} Affichage;

#endif

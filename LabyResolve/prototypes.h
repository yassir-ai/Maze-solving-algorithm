#ifndef PROTOTYPES
#define PROTOTYPES

#include "struct.h"

extern void clean(SDL_Texture *texture);
extern void cleanup(void);

// Draw
extern void drawGame(void);
extern void drawReussite(void);
extern void drawImage(SDL_Texture *image, int x, int y);
extern void drawError(void);

extern void depl(int direction);
extern int deplacement(int direction);

extern void envoiImage(void);

extern void gestionDebutGame(void);
extern void gestionGame(void);

// Input
extern void gestionInputs(Input *input);
extern void getInput(input);

extern void loadAll(void);
extern void loadMap(void);

extern void marquage(void);

extern int testDirection(int direction);
extern int testDirections(void);
extern void testVictoire(void);

// SDL
extern SDL_Texture *loadImage(char *name);
extern SDL_Renderer *getrenderer(void);

// Temps
extern void delay(unsigned int frameLimit);


#endif

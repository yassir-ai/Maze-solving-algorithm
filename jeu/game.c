#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#define S_WIDTH 1024
#define S_HEIGHT 768

void end_sdl(char ok, char const *msg, SDL_Window *window, SDL_Renderer *renderer);
SDL_Texture *load_texture_from_image(char *file_image_name, SDL_Window *window, SDL_Renderer *renderer);
void play_with_texture_1_1(SDL_Texture *my_texture, SDL_Window *window, SDL_Renderer *renderer);
int Game(SDL_Texture *bg_texture, SDL_Texture *my_texture, SDL_Texture *my_texture2, SDL_Rect *Source2, SDL_Rect *destination2,
            SDL_Window *window, SDL_Renderer *renderer, int *intersection, int vie, int temps);
int collision(SDL_Rect *feu, SDL_Rect *joueur);
void affichage_vie(SDL_Renderer *renderer, SDL_Window *window, int vie);
void fin_jeu(SDL_Texture *bg_texture, SDL_Renderer *renderer, SDL_Window *window);


int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Texture *joueur = NULL;
    SDL_Texture *Fond = NULL;

    int intersection = 0;
    int vie = 3;

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        end_sdl(0, "ERROR SDL INIT", window, renderer);

    if (TTF_Init() < 0)
        end_sdl(0, "Couldn't initialize SDL TTF", window, renderer);

    window = SDL_CreateWindow("Game",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, S_WIDTH,
                              S_HEIGHT,
                              SDL_WINDOW_OPENGL);
    if (window == NULL)
        end_sdl(0, "ERROR WINDOW CREATION", window, renderer);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
        end_sdl(0, "ERROR RENDERER CREATION", window, renderer);

    joueur = load_texture_from_image("./joueur.png", window, renderer);
    Fond = load_texture_from_image("./str.jpg", window, renderer);

    SDL_Rect source = {0}, window_dimensions = {0}, destination = {0};
    SDL_GetWindowSize(window, &window_dimensions.w, &window_dimensions.h);
    SDL_QueryTexture(joueur, NULL, NULL, &source.w, &source.h);

    float zoom = 0.3; // Facteur de zoom entre l'image source et l'image affichée

    destination.w = source.w * zoom; // On applique le zoom sur la largeur
    destination.h = source.h * zoom; // On applique le zoom sur la hauteur
    destination.x = 10;
    destination.y = (window_dimensions.h - destination.h) / 2;

    int end = 0;
    int temps = 0;

    while (end == 0 && vie > 0)
    {
        SDL_Texture *texture;
        texture = load_texture_from_image("./feu.png", window, renderer);
        end = Game(Fond, texture, joueur, &source, &destination, window, renderer, &intersection, vie, temps);
        if (intersection == 1)
        {
            vie -= intersection;
        }
        
        temps++;

        SDL_DestroyTexture(texture);
    }

    fin_jeu(Fond,renderer, window);

    SDL_DestroyTexture(joueur);
    SDL_DestroyTexture(Fond);
    TTF_Quit();
    IMG_Quit();
    end_sdl(1, "Normal ending", window, renderer);
    return EXIT_SUCCESS;
}

void fin_jeu(SDL_Texture *bg_texture, SDL_Renderer *renderer, SDL_Window *window)
{
    TTF_Font *font = NULL;                              // la variable 'police de caractère'
    font = TTF_OpenFont("./BebasNeue-Regular.ttf", 90); // La police à charger, la taille désirée
    if (font == NULL) end_sdl(0, "Can't load font", window, renderer);

    TTF_SetFontStyle(font, TTF_STYLE_NORMAL); // en gras

    SDL_Color color = {0, 0, 0, 255};                              // la couleur du texte
    SDL_Surface *text_surface = NULL;                                // la surface  (uniquement transitoire)
    text_surface = TTF_RenderText_Blended(font, "GAME OVER", color); // création du texte dans la surface
    if (text_surface == NULL)
        end_sdl(0, "Can't create text surface", window, renderer);

    SDL_Texture *text_texture = NULL;                                    // la texture qui contient le texte
    text_texture = SDL_CreateTextureFromSurface(renderer, text_surface); // transfert de la surface à la texture
    if (text_texture == NULL)
        end_sdl(0, "Can't create texture from surface", window, renderer);
    SDL_FreeSurface(text_surface); // la texture ne sert plus à rien

    SDL_RenderClear(renderer); //Nettoyage du rendu

    SDL_Rect pos = {0, 0, 0, 0};                                // rectangle où le texte va être prositionné
    SDL_QueryTexture(text_texture, NULL, NULL, &pos.w, &pos.h); // récupération de la taille (w, h) du texte
    pos.x = (S_WIDTH - pos.w) / 2;
    pos.y = (S_HEIGHT - pos.h) / 2;
    play_with_texture_1_1(bg_texture,window,renderer);
    SDL_RenderCopy(renderer, text_texture, NULL, &pos); // Ecriture du texte dans le renderer
    SDL_DestroyTexture(text_texture);                   // On n'a plus besoin de la texture avec le texte

    SDL_RenderPresent(renderer); // Affichage
    SDL_Delay(3000);
}

int Game(SDL_Texture *bg_texture, SDL_Texture *my_texture, SDL_Texture *my_texture2, SDL_Rect *Source2, SDL_Rect *destination2,
     SDL_Window *window, SDL_Renderer *renderer, int *intersection, int vie, int temps)
{

    int end = 0;
    SDL_Rect source = {0}, window_dimensions = {0}, destination = {0};
    srand(time(0));
    SDL_GetWindowSize(window, &window_dimensions.w, &window_dimensions.h);
    SDL_QueryTexture(my_texture, NULL, NULL, &source.w, &source.h);

    float zoom = 0.1; // Facteur de zoom entre l'image source et l'image affichée

    int nb_it = 980;
    //speed_feu = (score / 4 + 5), 
    int speed_joueur = 30;
    int speed_feu = 8 + (temps/2);
    destination.w = source.w * zoom; // On applique le zoom sur la largeur
    destination.h = source.h * zoom; // On applique le zoom sur la hauteur
    destination.y = rand() % (S_HEIGHT - destination.h);
    float h = window_dimensions.w - destination.h; // hauteur du déplacement à effectuer

    SDL_bool program_on = SDL_TRUE;
    int i = 0;
    while (program_on && (i < nb_it) && (end == 0))
    {
        SDL_Event event;

        while (SDL_PollEvent(&event))
        {

            switch (event.type)
            {
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_UP:
                    if (destination2->y > 5)
                    {
                        destination2->y -= speed_joueur;
                    }
                    break;

                case SDLK_DOWN:
                    if ((destination2->y + destination2->h) < S_HEIGHT)
                    {
                        destination2->y += speed_joueur;
                    }
                    break;
                case SDLK_q:
                    end = 1;
                    break;

                default:
                    break;
                }
                break;

            case SDL_QUIT:
                end = 1;
                break;
            default:
                break;
            }
        }

        destination.x = S_WIDTH - i;

        i += speed_feu;

        *intersection = collision(&destination, destination2);

        SDL_RenderClear(renderer); // Effacer l'image précédente
        play_with_texture_1_1(bg_texture, window, renderer);
        affichage_vie(renderer, window, vie);
        SDL_RenderCopy(renderer, my_texture2, Source2, destination2);

        SDL_RenderCopy(renderer, my_texture, &source, &destination); // Préparation de l'affichage
        SDL_RenderPresent(renderer);                                 // Affichage de la nouvelle image
        SDL_Delay(5);
    }
    return end;
}


void affichage_vie(SDL_Renderer *renderer, SDL_Window *window, int vie)
{
    TTF_Font *font = NULL;                              // la variable 'police de caractère'
    font = TTF_OpenFont("./BebasNeue-Regular.ttf", 70); // La police à charger, la taille désirée
    if (font == NULL) end_sdl(0, "Can't load font", window, renderer);

    TTF_SetFontStyle(font, TTF_STYLE_NORMAL); // en gras

    SDL_Color color = {0, 0, 0, 255}; // la couleur du texte
    SDL_Surface *text_surface = NULL;   // la surface  (uniquement transitoire)
    char phrase[20];
    sprintf(phrase, "VIE : %d", vie);
    text_surface = TTF_RenderText_Blended(font, phrase, color); // création du texte dans la surface
    if (text_surface == NULL) end_sdl(0, "Can't create text surface", window, renderer);

    SDL_Texture *text_texture = NULL;                                    // la texture qui contient le texte
    text_texture = SDL_CreateTextureFromSurface(renderer, text_surface); // transfert de la surface à la texture
    if (text_texture == NULL) end_sdl(0, "Can't create texture from surface", window, renderer);
    SDL_FreeSurface(text_surface); // la texture ne sert plus à rien

    SDL_Rect pos = {0, 0, 0, 0};                                // rectangle où le texte va être prositionné
    SDL_QueryTexture(text_texture, NULL, NULL, &pos.w, &pos.h); // récupération de la taille (w, h) du texte
    pos.x = S_WIDTH - pos.w - 30;
    SDL_RenderCopy(renderer, text_texture, NULL, &pos); // Ecriture du texte dans le renderer
    SDL_DestroyTexture(text_texture);                   // On n'a plus besoin de la texture avec le texte
}


int collision(SDL_Rect *feu, SDL_Rect *joueur)
{
    int milieu_feu_y = (feu->y + (feu->h / 2));

    //Condition: le milieu en abcisse du feu doit se positionner dans le joueur, et son extrémité en coordonnées dépasse l'ordonnée du joueur.
    if (((milieu_feu_y > joueur->y) && (milieu_feu_y < (joueur->y + joueur->h))) && (feu->x < (joueur->x+joueur->w)))
    {
        return 1;
    }

    return 0;

}

void end_sdl(char ok, char const *msg, SDL_Window *window, SDL_Renderer *renderer)
{
    char msg_formated[255];
    int l;

    if (!ok)
    {
        strncpy(msg_formated, msg, 250);
        l = strlen(msg_formated);
        strcpy(msg_formated + l, " : %s\n");

        SDL_Log(msg_formated, SDL_GetError());
    }

    if (renderer != NULL)
        SDL_DestroyRenderer(renderer);
    if (window != NULL)
        SDL_DestroyWindow(window);

    SDL_Quit();

    if (!ok)
    {
        exit(EXIT_FAILURE);
    }
}

SDL_Texture *load_texture_from_image(char *file_image_name, SDL_Window *window, SDL_Renderer *renderer)
{
    SDL_Surface *my_image = NULL;   // Variable de passage
    SDL_Texture *my_texture = NULL; // La texture

    my_image = IMG_Load(file_image_name); // Chargement de l'image dans la surface
                                          // image=SDL_LoadBMP(file_image_name); fonction standard de la SDL,
                                          // uniquement possible si l'image est au format bmp */
    if (my_image == NULL)
        end_sdl(0, "Chargement de l'image impossible", window, renderer);

    my_texture = SDL_CreateTextureFromSurface(renderer, my_image); // Chargement de l'image de la surface vers la texture
    SDL_FreeSurface(my_image);                                     // la SDL_Surface ne sert que comme élément transitoire
    if (my_texture == NULL)
        end_sdl(0, "Echec de la transformation de la surface en texture", window, renderer);

    return my_texture;
}

void play_with_texture_1_1(SDL_Texture *my_texture, SDL_Window *window, SDL_Renderer *renderer)
{
    SDL_Rect
        source = {0},            // Rectangle définissant la zone de la texture à récupérer
        window_dimensions = {0}, // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
        destination = {0};       // Rectangle définissant où la zone_source doit être déposée dans le renderer

    SDL_GetWindowSize(
        window, &window_dimensions.w,
        &window_dimensions.h); // Récupération des dimensions de la fenêtre
    SDL_QueryTexture(my_texture, NULL, NULL,
                     &source.w, &source.h); // Récupération des dimensions de l'image

    destination = window_dimensions; // On fixe les dimensions de l'affichage à  celles de la fenêtre

    /* On veut afficher la texture de façon à ce que l'image occupe la totalité de la fenêtre */

    SDL_RenderCopy(renderer, my_texture, &source, &destination); // Création de l'élément à afficher
}
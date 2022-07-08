#include <SDL2/SDL_image.h>              
#include <string.h>                                           
#include <SDL2/SDL.h>
#include "chefoeuvre.h"


#define NOMBRE_VIE 10 

void end_sdl(char ok,char const* msg,SDL_Window* window,SDL_Renderer* renderer) { 
 char msg_formated[255]; 
 int l; 

 if (!ok) { 
 strncpy(msg_formated, msg, 250); 
 l = strlen(msg_formated); 
 strcpy(msg_formated + l, " : %s\n"); 

 SDL_Log(msg_formated, SDL_GetError()); 
 } 

 if (renderer != NULL) SDL_DestroyRenderer(renderer); 
 if (window != NULL) SDL_DestroyWindow(window); 

 SDL_Quit(); 

 if (!ok) { 
 exit(EXIT_FAILURE); 
 } 
} 




//chargement d'une image

SDL_Texture* load_texture_from_image(char  *  file_image_name, SDL_Window *window, SDL_Renderer *renderer )
{

    SDL_Surface *my_image = NULL;           // Variable de passage
    SDL_Texture* my_texture = NULL;         // La texture

    my_image = IMG_Load(file_image_name);   // Chargement de l'image dans la surface
                                            // image=SDL_LoadBMP(file_image_name); fonction standard de la SDL, 
                                            // uniquement possible si l'image est au format bmp */
    if (my_image == NULL) end_sdl(0, "Chargement de l'image impossible", window, renderer);

    my_texture = SDL_CreateTextureFromSurface(renderer, my_image); // Chargement de l'image de la surface vers la texture
    SDL_FreeSurface(my_image);                                     // la SDL_Surface ne sert que comme élément transitoire 
    if (my_texture == NULL) end_sdl(0, "Echec de la transformation de la surface en texture", window, renderer);

    return my_texture;
  }


void play_with_texture_1(SDL_Texture *my_texture, SDL_Window *window,
                         SDL_Renderer *renderer) {
  SDL_Rect 
          source = {0},                         // Rectangle définissant la zone de la texture à récupérer
          window_dimensions = {0},              // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
          destination = {0};                    // Rectangle définissant où la zone_source doit être déposée dans le renderer

  SDL_GetWindowSize(
      window, &window_dimensions.w,
      &window_dimensions.h);                    // Récupération des dimensions de la fenêtre
  SDL_QueryTexture(my_texture, NULL, NULL,
                   &source.w, &source.h);       // Récupération des dimensions de l'image

  destination = window_dimensions;              // On fixe les dimensions de l'affichage à  celles de la fenêtre

  /* On veut afficher la texture de façon à ce que l'image occupe la totalité de la fenêtre */

  SDL_RenderCopy(renderer, my_texture,
                 &source,
                 &destination);                 // Création de l'élément à afficher
  SDL_RenderPresent(renderer);                  // Affichage
  SDL_Delay(10000);                              // Pause en ms

  SDL_RenderClear(renderer);                    // Effacer la fenêtre
}
 void play_with_texture_1_1(SDL_Texture *my_texture, SDL_Window *window, SDL_Renderer *renderer) 
 {
  SDL_Rect 
          source = {0},                         
          window_dimensions = {0},              
          destination = {0};                    

  SDL_GetWindowSize(
      window, &window_dimensions.w,
      &window_dimensions.h);                    
  SDL_QueryTexture(my_texture, NULL, NULL,
                   &source.w, &source.h);       
  destination = window_dimensions;              

  /* On veut afficher la texture de façon à ce que l'image occupe la totalité de la fenêtre */

  SDL_RenderCopy(renderer, my_texture,
                 &source,
                 &destination);                 // Création de l'élément à afficher
                               // Affichage
                                              // Pause en ms

                      // Effacer la fenêtre
}




// void play_with_texture_4(SDL_Texture* my_texture, SDL_Texture* bg_texture,
//                          SDL_Window* window,
//                          SDL_Renderer* renderer) {
//        SDL_Rect 
//              source = {0},                    // Rectangle définissant la zone totale de la planche
//              window_dimensions = {0},         // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
//              destination = {0},             // Rectangle définissant où la zone_source doit être déposée dans le renderer
//              state = {0};    
   
//        SDL_GetWindowSize(window,              // Récupération des dimensions de la fenêtre
//                          &window_dimensions.w,
//                          &window_dimensions.h);
//        SDL_QueryTexture(my_texture,           // Récupération des dimensions de l'image
//                         NULL, NULL,
//                         &source.w, &source.h);
      
      
//        /* Mais pourquoi prendre la totalité de l'image, on peut n'en afficher qu'un morceau, et changer de morceau :-) */

//        int nb_images =8;                     // Il y a 8 vignette dans la ligne de l'image qui nous intéresse
//        float zoom = 2;                        // zoom, car ces images sont un peu petites
//        int offset_x = source.w / nb_images,   // La largeur d'une vignette de l'image, marche car la planche est bien réglée
//          offset_y = source.h / 4;           // La hauteur d'une vignette de l'image, marche car la planche est bien réglée


//         state.x = 0 ;                          // La première vignette est en début de ligne
//         state.y = 3 * offset_y;                // On s'intéresse à la 4ème ligne, le bonhomme qui court
//         state.w = offset_x;                    // Largeur de la vignette
//         state.h = offset_y;                    // Hauteur de la vignette

//        destination.w = offset_x * zoom;      
//        destination.h = offset_y * zoom; 
      

       
//  while (1)
//  {
  
 
//  int x = 0; 
//  destination.x = x; 
//  state.x += offset_x; 
//  state.x %= source.w; 
//  destination.y = 
//  (window_dimensions.h - destination.h)/1.2;
//  SDL_RenderClear(renderer); 
//  play_with_texture_1_1(bg_texture,window,renderer); 
//  SDL_RenderCopy(renderer, my_texture,&state,
//  &destination); 
//  SDL_RenderPresent(renderer); 
//  SDL_Delay(80); 
//  SDL_RenderClear(renderer); 
//   }

// }
void drawrectangle(SDL_Renderer* renderer,int x,int y,int height,int width,int color)
{
    SDL_Rect rectangle;    
                                            

    SDL_SetRenderDrawColor(renderer,                                
                                30+color, 60+color, 100+color,                               // mode Red, Green, Blue (tous dans 0..255)
                                255);      
    //SDL_RenderClear(renderer);                                                         // 0 = transparent ; 255 = opaque
    rectangle.x = x;                                                    // x haut gauche du rectangle
    rectangle.y = y;                                                    // y haut gauche du rectangle
    rectangle.w = width;                                                  // sa largeur (w = width)
    rectangle.h = height;                                                  // sa hauteur (h = height)

    SDL_RenderFillRect(renderer, &rectangle);
    
}
void to_greenrectangle(SDL_Renderer *renderer,int x,int y,int height,int width)
{
   SDL_Rect rectangle;                                             

    SDL_SetRenderDrawColor(renderer,0,0,0,0);  
                                                    
    rectangle.x = x;                                                    
    rectangle.y = y;                                                    
    rectangle.w = width;                                               
    rectangle.h = height;                                               

    SDL_RenderFillRect(renderer, &rectangle);
    //SDL_RenderClear(renderer);
}

 
    

void play_with_texture_bis(SDL_Texture* my_texture, SDL_Texture* bg_texture,
                         SDL_Window* window,
                         SDL_Renderer* renderer) {
       SDL_Rect 
             source = {0},                    // Rectangle définissant la zone totale de la planche
             window_dimensions = {0},         // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
             destination = {0},             // Rectangle définissant où la zone_source doit être déposée dans le renderer
             state = {0};    
   
       SDL_GetWindowSize(window,              // Récupération des dimensions de la fenêtre
                         &window_dimensions.w,
                         &window_dimensions.h);
       SDL_QueryTexture(my_texture,           // Récupération des dimensions de l'image
                        NULL, NULL,
                        &source.w, &source.h);
      //SDL_Texture *texture = load_texture_from_image("balle.png",window, renderer );
      
      int offset1=1100;
      int offset2=510;
      int color=0;
       /* Mais pourquoi prendre la totalité de l'image, on peut n'en afficher qu'un morceau, et changer de morceau :-) */

       int nb_images =8;                     // Il y a 8 vignette dans la ligne de l'image qui nous intéresse
       float zoom = 2;                        // zoom, car ces images sont un peu petites
       int offset_x = source.w / nb_images,   // La largeur d'une vignette de l'image, marche car la planche est bien réglée
         offset_y = source.h / 4;           // La hauteur d'une vignette de l'image, marche car la planche est bien réglée


        state.x = 0 ;                          // La première vignette est en début de ligne
        state.y = 3 * offset_y;                // On s'intéresse à la 4ème ligne, le bonhomme qui court
        state.w = offset_x;                    // Largeur de la vignette
        state.h = offset_y;                    // Hauteur de la vignette

       destination.w = offset_x * zoom;      
       destination.h = offset_y * zoom; 
      

       
 while (1)
 {
  
 
 int x = 0; 
 destination.x = x; 
 state.x += offset_x; 
 state.x %= source.w; 
 destination.y = 
 (window_dimensions.h - destination.h)/1.2;
 SDL_RenderClear(renderer); 
 play_with_texture_1_1(bg_texture,window,renderer);
 //play_with_texture_4(texture,window,renderer); 
 SDL_RenderCopy(renderer, my_texture,&state,
 &destination); 
//  SDL_RenderPresent(renderer); 
//   SDL_Delay(8); 
//   //SDL_RenderClear(renderer);
//  for (int i=0;i<40;i++)
//  {

    
//    drawrectangle(renderer,offset1,offset2,30,40,color);
//    SDL_RenderPresent(renderer);
//    SDL_Delay(50);
//    to_greenrectangle(renderer,offset1,offset2,30,40);
//    SDL_RenderPresent(renderer);
   
//    SDL_Delay(50);
//    offset1=offset1-30;
//    SDL_RenderPresent(renderer); 
//   SDL_Delay(8); 
//   //SDL_RenderClear(renderer);
   
//  }
  //drawrectangle(renderer,offset1,offset2,30,40,color);

 SDL_RenderPresent(renderer); 
 SDL_Delay(8); 
 SDL_RenderClear(renderer); 
  }

}


void play_with_texture_4(SDL_Texture* texture,
                         SDL_Window* window,
                         SDL_Renderer* renderer) {
       SDL_Rect 
             source = {0},                    // Rectangle définissant la zone totale de la planche
             window_dimensions = {0},         // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
             destination = {0},               // Rectangle définissant où la zone_source doit être déposée dans le renderer
             state = {0};                     // Rectangle de la vignette en cours dans la planche 

       SDL_GetWindowSize(window,              // Récupération des dimensions de la fenêtre
                         &window_dimensions.w,
                         &window_dimensions.h);
       SDL_QueryTexture(texture,           // Récupération des dimensions de l'image
                        NULL, NULL,
                        &source.w, &source.h);

       /* Mais pourquoi prendre la totalité de l'image, on peut n'en afficher qu'un morceau, et changer de morceau :-) */

       int nb_images = 12;                     // Il y a 8 vignette dans la ligne de l'image qui nous intéresse
       float zoom = 2;                        // zoom, car ces images sont un peu petites
       int offset_x = source.w / nb_images,   // La largeur d'une vignette de l'image, marche car la planche est bien réglée
           offset_y = source.h / 8;           // La hauteur d'une vignette de l'image, marche car la planche est bien réglée


       state.x = 12 *offset_x ;                // La première vignette est en début de ligne
       state.y = 0 * offset_y;                // On s'intéresse à la 4ème ligne, le bonhomme qui court
       state.w = offset_x;                    // Largeur de la vignette
       state.h = offset_y;                    // Hauteur de la vignette

       destination.w = offset_x * zoom;       // Largeur du sprite à l'écran
       destination.h = offset_y * zoom;       // Hauteur du sprite à l'écran

       destination.y =                        // La course se fait en milieu d'écran (en vertical)
         (window_dimensions.h - destination.h) /2;
       int x=(window_dimensions.w - destination.w);
       int speed =9;
       while(x>(window_dimensions.w - destination.w)/100)
       //for (x =(window_dimensions.w - destination.w); x>(window_dimensions.w - destination.w)/100;x-= speed) 
       {
         printf("ok");
         destination.x = x ;                   // Position en x pour l'affichage du sprite
         state.x -= offset_x;   
         x-=speed;          // On passe à la vignette suivante dans l'image
         state.x %= source.w;                 // La vignette qui suit celle de fin de ligne est
                                              // celle de début de ligne

         SDL_RenderClear(renderer);           // Effacer l'image précédente avant de dessiner la nouvelle
         SDL_RenderCopy(renderer, texture, // Préparation de l'affichage
                        &state,
                        &destination);
                       // SDL_RenderClear(renderer);  
         SDL_RenderPresent(renderer);         // Affichage
         SDL_Delay(80);                       // Pause en ms
       }
       //SDL_RenderClear(renderer);             // Effacer la fenêtre avant de rendre la main
     }

 
    





int main(int argc, char** argv)
 {
 (void)argc;
 (void)argv;

 SDL_Window* window = NULL;
 SDL_Renderer* renderer = NULL;

 SDL_DisplayMode screen;
 if (SDL_Init(SDL_INIT_VIDEO) != 0) end_sdl(0, "ERROR SDL INIT", window, renderer);

 SDL_GetCurrentDisplayMode(0, &screen);
 printf("Résolution écran\n\tw : %d\n\th : %d\n", screen.w,
 screen.h);
 window = SDL_CreateWindow("Premier dessin",
 SDL_WINDOWPOS_CENTERED,
 SDL_WINDOWPOS_CENTERED, screen.w * 0.66,
 screen.h * 0.66,
 SDL_WINDOW_OPENGL);
 if (window == NULL) end_sdl(0, "ERROR WINDOW CREATION", window, renderer);

 /* Création du renderer */
 renderer = SDL_CreateRenderer(
 window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
 if (renderer == NULL) end_sdl(0, "ERROR RENDERER CREATION", window, renderer);


 SDL_Texture *texture = load_texture_from_image("joueur.png",window, renderer );
SDL_Texture * bg_texture = load_texture_from_image("joueur.png",window, renderer );
//play_with_texture_bis( my_texture,bg_texture, window, renderer);
play_with_texture_1( texture, window, renderer);


} 


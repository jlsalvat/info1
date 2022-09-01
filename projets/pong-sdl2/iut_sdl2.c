#include <stdio.h>
#include <stdlib.h>
#include "iut_sdl2.h"

const Uint8 *etatClavier;

static SDL_Window *window = NULL;

Ecran creationEcran(void)
{
    freopen("CON", "w", stdout);
//    freopen("CON", "r", stdin);
//    freopen("CON", "w", stderr);

    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Unable to Init SDL: %s\n", SDL_GetError());
        exit(-1);
    }

    if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
        printf("Unable to Init hinting: %s\n", SDL_GetError());
    }

    int pleinEcran = 1;
    int flag = (pleinEcran) ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0;
    if((window = SDL_CreateWindow(
                     "Pong",
                     SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                     X_SCREEN, Y_SCREEN, SDL_WINDOW_SHOWN | flag)
       ) == NULL) {
        printf("Unable to create SDL Window: %s\n", SDL_GetError());
        exit(-1);
    }

    Ecran ecran;
    if ((ecran = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED)) == NULL) {
        printf("Unable to create renderer\n");
        exit(-1);
    }

    SDL_RenderSetLogicalSize(ecran, X_SCREEN, Y_SCREEN);

    SDL_SetRenderDrawColor(ecran, 0x00, 0x00, 0x00, 0xFF);

    return ecran;
}

Image creationImage(char *fichier)
{
    Image bmp = SDL_LoadBMP(fichier);
    if (!bmp)
    {
        printf("Impossible de charger %s : %s\n", fichier, SDL_GetError());
        exit(-1);
    }
    return bmp;
}

inline void destructionImage(Image image)
{
    SDL_FreeSurface(image);
}

void destructionEcran(Ecran ecran)
{
    SDL_DestroyRenderer(ecran);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void dessineImage(Ecran ecran, int x, int y, Image image)
{
    SDL_Rect dstrect;
    dstrect.x = x;
    dstrect.y = y;
    dstrect.w = image->w;
    dstrect.h = image->h;
    SDL_Texture *texture = SDL_CreateTextureFromSurface(ecran, image);
    SDL_RenderCopy(ecran, texture, NULL, &dstrect);
    SDL_DestroyTexture(texture);
}

void effaceEcran(Ecran ecran)
{
    SDL_SetRenderDrawColor(ecran, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(ecran);
}

void miseAJourEcran(Ecran ecran)
{
    static int tempsPrecedent = 0;

    int tempsActuel = 0, tempsEcart;
    tempsActuel = SDL_GetTicks();
    tempsEcart = tempsActuel - tempsPrecedent;
    if (tempsEcart < 20) SDL_Delay(20-tempsEcart);
    tempsPrecedent = SDL_GetTicks();
    SDL_RenderPresent(ecran);
}

inline int largImage(Image image)
{
    return image->w;
}

inline int hautImage(Image image)
{
    return image->h;
}

void evenements(void)
{
    SDL_PumpEvents();
    etatClavier = SDL_GetKeyboardState(NULL);
}

#ifndef IUT_SDL2_H_INCLUDED
#define IUT_SDL2_H_INCLUDED

#include <SDL2/SDL.h>

#define X_SCREEN        640
#define Y_SCREEN        480

typedef SDL_Surface* Image;
typedef SDL_Renderer* Ecran;

extern const Uint8 *etatClavier;

Ecran creationEcran(void);
Image creationImage(char *fichier);
void dessineImage(Ecran ecran, int x, int y, Image image);
void effaceEcran(Ecran ecran);
void miseAJourEcran(Ecran ecran);
int largImage(Image image);
int hautImage(Image image);
void destructionImage(Image image);
void destructionEcran(Ecran ecran);
void evenements(void);

#endif // IUT_SDL_H_INCLUDED

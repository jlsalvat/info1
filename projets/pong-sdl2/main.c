#include <stdio.h>
#include "iut_sdl2.h"

int main ( int argc, char** argv )
{
    int fin = 0;
    int xCentre, yCentre;
    int xBalle, yBalle;
    int vxBalle = 1, vyBalle = 1;
    int xRaquette = 10, yRaquette = 200, vitesseRaq = 10;

    // cr�ation de l'�cran graphique
    Ecran ecran = creationEcran();
    // cr�ation de l'image de la balle en m�moire
    Image balle = creationImage("balle.bmp");
    // cr�ation de l'image de la raquette en m�moire
    Image raquette = creationImage("raquette.bmp");

    // calcul de la position pour placer la balle au centre de l'�cran
    xCentre = (X_SCREEN - largImage(balle)) / 2;
    yCentre = (Y_SCREEN - hautImage(balle)) / 2;
    xBalle = xCentre;
    yBalle = yCentre;

    // tant que fin n'est pas vrai
    while (!fin)
    {
        // mise � jour des �v�nements (clavier et souris)
        evenements();

        // si on appuie sur la touche "Echap" on termine le programme
        fin = etatClavier[SDL_SCANCODE_ESCAPE];

        // d�placements
        if (etatClavier[SDL_SCANCODE_LSHIFT] || etatClavier[SDL_SCANCODE_RSHIFT])
        {
            vitesseRaq = 1;
        }
        else
        {
            vitesseRaq = 10;
        }
        if (etatClavier[SDL_SCANCODE_UP])
        {
            yRaquette -= vitesseRaq;
        }
        if (etatClavier[SDL_SCANCODE_DOWN])
        {
            yRaquette += vitesseRaq;
        }

        if (etatClavier[SDL_SCANCODE_C])
        {
            xBalle = xCentre;
            yBalle = yCentre;
        }

        xBalle += vxBalle;
        yBalle += vyBalle;

        // effacement de l'�cran
        effaceEcran(ecran);

        // on peut commencer � dessiner ici

        // dessin de la balle
        dessineImage(ecran, xBalle, yBalle, balle);
        // dessin d'une raquette
        dessineImage(ecran, xRaquette, yRaquette, raquette);

        // on doit arr�ter de dessiner ici

        // mise � jour de l'affichage
        miseAJourEcran(ecran);
    }

    // vide des images en m�moire
    destructionImage(balle);
    destructionImage(raquette);

    // ferme la fen�tre
    destructionEcran(ecran);

    return 0;
}



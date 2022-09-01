#include <stdio.h>
#include "iut_sdl2.h"

int main ( int argc, char** argv )
{
    int fin = 0;
    int xCentre, yCentre;
    int xBalle, yBalle;
    int vxBalle = 1, vyBalle = 1;
    int xRaquette = 10, yRaquette = 200, vitesseRaq = 10;

    // création de l'écran graphique
    Ecran ecran = creationEcran();
    // création de l'image de la balle en mémoire
    Image balle = creationImage("balle.bmp");
    // création de l'image de la raquette en mémoire
    Image raquette = creationImage("raquette.bmp");

    // calcul de la position pour placer la balle au centre de l'écran
    xCentre = (X_SCREEN - largImage(balle)) / 2;
    yCentre = (Y_SCREEN - hautImage(balle)) / 2;
    xBalle = xCentre;
    yBalle = yCentre;

    // tant que fin n'est pas vrai
    while (!fin)
    {
        // mise à jour des événements (clavier et souris)
        evenements();

        // si on appuie sur la touche "Echap" on termine le programme
        fin = etatClavier[SDL_SCANCODE_ESCAPE];

        // déplacements
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

        // effacement de l'écran
        effaceEcran(ecran);

        // on peut commencer à dessiner ici

        // dessin de la balle
        dessineImage(ecran, xBalle, yBalle, balle);
        // dessin d'une raquette
        dessineImage(ecran, xRaquette, yRaquette, raquette);

        // on doit arrêter de dessiner ici

        // mise à jour de l'affichage
        miseAJourEcran(ecran);
    }

    // vide des images en mémoire
    destructionImage(balle);
    destructionImage(raquette);

    // ferme la fenêtre
    destructionEcran(ecran);

    return 0;
}



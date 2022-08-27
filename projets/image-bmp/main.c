#include <stdlib.h>
#include <stdio.h>
#include "bmp.h"

#define LARGEUR 10
#define HAUTEUR 7
int main()
{
    //création de fichier bmp avec un motif
    unsigned char R[HAUTEUR][LARGEUR];
    unsigned char G[HAUTEUR][LARGEUR];
    unsigned char B[HAUTEUR][LARGEUR];
    Creer_fichier_bmp("shape.bmp",LARGEUR,HAUTEUR);
    for(int i=0; i<HAUTEUR; i++)
    {
        for(int j=0; j<LARGEUR; j++)
        {
            R[i][j]=0;
            G[i][j]=0;
            B[i][j]=127;
        }
    }
    Enregistrer_fichier_bmp(R,G,B);

    //copie de fichier binaire
    Copier_fichier_bmp("tweet_back.bmp","tweet.bmp");

    //ouvrir un fichier bmp et le modifier
    int largeur,hauteur;
    Ouvrir_fichier_bmp("tweet.bmp", &largeur, &hauteur);
    //création des 3 tableaux R,G,B, seule solution possible pour les 3 matrices
    unsigned char *R1= (unsigned char *) malloc(largeur*hauteur);
    unsigned char G1[largeur*hauteur]; //VLA
    unsigned char *B1=(unsigned char *) malloc(largeur*hauteur);
    //mise à jour des 3 matrices RGB
    Read_RGB_bmp(R1,G1,B1);
    //inversion de l'image
    for(int i=0; i<hauteur; i++)
    {
        for(int j=0; j<largeur; j++)
        {
            R1[i*largeur+j]=255-R1[i*largeur+j];
            G1[i*largeur+j]=255-*(G1+i*largeur+j);
            B1[i*largeur+j]=255-*(B1+i*largeur+j);
        }
    }
    //enregistrement de l'image
    Enregistrer_fichier_bmp(R1,G1,B1);

    return 0;
}

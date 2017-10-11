/** @file
 * Filtres de seuillage
 **/

#include <cmath>
#include "image.h"
#include "sobel.h"
#include <iostream>
#include "ppm.h"

/** P6 PROJET Renormalize une image en teintes de gris en les ramenant dans l'intervalle [0,255]
 @param img une image en teintes de gris
 @return une image en teintes de gris
**/
ImageGris renormalise(ImageGris img) {
    //ifstream lire(img); pas la peine car il y a pas de fichier exterieur à lire
    ImageGris sortie;
    sortie = ImageGris(img.size());
	for (int i=0; i< img.size(); i++){
        sortie[i]= vector<double>(img[0].size()); //sortie[i]= vector<double>(img.size()[0]); |20|error: invalid types ‘size_t[int]’ for array subscript|
	}//allocation fini

    //string p;
    //p = img[0][0];
    //   sortie.push_back(p);//sortie est un vector<vector<double>> qui contient un string P au début ?
    //nbLigne = (int(img[0][1]));//sortie.push_back(nbLigne);
    //nbColonne = img [1][1]; //sortie.push_back(nbColonne);
    int intervalle=0;
    int nbLigne=img.size();
    int nbColonne=img[0].size();
    for (int i=0; i<nbLigne; i++){
        for (int j=0; j<nbColonne; j++)
            if (img[i][j]>intervalle)
            intervalle = img[i][j];
    }
    for (int i=0; i<nbLigne; i++){
        for (int j=0; j<nbColonne; j++){
        sortie[i][j]=  img[i][j]*255/intervalle;
        }
    }
    return sortie;
}

/** P6 PROJET filtre de seuillage
 *@param img une image en teintes de gris
 *@param seuil un entier dans l'intervalle [0,255]
 *@return une image en noir et blanc obternue en remplaçant la teinte de chaque pixel
 *@- du blanc si teinte < seuil
 *@- du noir si teinte > seuil
 **/
ImageGris seuillage(ImageGris img, int seuil) {
	const int PIXEL_BLANC = 255 ;
	const int PIXEL_NOIR = 0 ;

	ImageGris sortie=img;// J'ai le droit de faire cela ou il faut allouer de la mémoire ?

	int nLine = img.size();//sortie est un vector<vector<double>> qui contient un string P au début ?
	int nCol = img[0].size();

	for (int i=0 ; i < nLine ; i++){
		for (int j=0; j < nCol ; j++){
			sortie[i][j] = (img[i][j] >= seuil) ? PIXEL_NOIR : PIXEL_BLANC ;
		}
	}
return sortie;
}

/** P6 PROJET filtre de double seuillage
 *@param imgIntensite image d'intensité
 *@param imgContour image codant un ensemble de pixels selectionnés
 *@param seuil un entier dans l'intervalle [0,255]
 *@return une copie d'imgIntensite modifiée de sorte que:
 *@- si teinte > seuil et voisin d'un pixel de imgContour, alors pixel noir
 *@- sinon pixel blanc
 **/


//** EstVoisin revoie la position d' Pixel s'il est voisin du pixel Contour qui nous intéresse
////*@param i ligne du pixel Contour
////*@param j Colonne du pixel Contour
////*@param imgContour une imageGris dont on veut déterminer ses voisins
////**/

ImageGris doubleSeuillage(ImageGris imgIntensite, ImageGris imgContour, int seuil) {
    ImageGris sortie=imgIntensite;

    int nbLigne=imgIntensite.size();
    int nbColonne=imgIntensite[0].size();
    const int PIXEL_BLANC = 255 ;
	const int PIXEL_NOIR = 0 ;
	float SommePixelsContour=1;

    for(int i = 0; i<nbLigne-1; i++){
     for(int j = 0; j< nbColonne-1; j++){
        if ((i=0) or (j=0)) {
        sortie[i][j]=PIXEL_BLANC;
        }
        else {
      SommePixelsContour= imgContour[i-1][j-1] +imgContour[i-1][j]+imgContour[i-1][j+1];
      SommePixelsContour+=imgContour[i][j-1]+imgContour[i][j+1];
      SommePixelsContour+=imgContour[i+1][j-1]+imgContour[i+1][j]+imgContour[i+1][j+1];

        if(imgIntensite[i][j]>=seuil && (SommePixelsContour!= 8*PIXEL_BLANC)){
             sortie[i][j]=PIXEL_NOIR;
        }
        else {sortie[i][j]=PIXEL_BLANC;}
        }
	}
	return sortie;

}}

//** P6 PROJET filtre de double seuillage itératif
// *@param img une image *.ppm en teintes de gris
// *@param seuilFort un entier dans l'intervalle [0,255]
// *@param seuilfaible un entier dans l'intervalle [0,255]
// *@param nbAmeliorations un entier non négatif : le nombre d'itérations
// *@return le double seuillage de img
// **/
//
ImageGris doubleSeuillage(ImageGris img, int seuilFort, int seuilFaible, int nbAmeliorations) {
    if (nbAmeliorations<=0)
      throw runtime_error("le nombre d'Ameliorations doit etre positif:");
     if ((seuilFort<0 or seuilFort>255) or (seuilFaible<0 or seuilFaible>255))
      throw runtime_error("Les seuils doivent etre entre 0 et 255 compris:");

    ImageGris imgContour = seuillage(img, seuilFort);

    for(int i=0; i< nbAmeliorations; i++){
        imgContour = doubleSeuillage (img, imgContour, seuilFaible);
    }

    for(int i = 1; i<img.size()- 1; i++){
        for(int j = 1; j< img[i].size()-1; j++){
             if(img[i][j]>= seuilFort){img[i][j]=0;}
            else if(img[i][j]>= seuilFaible && (imgContour[i-1][j-1] +imgContour[i-1][j]+imgContour[i-1][j+1]
               +imgContour[i][j-1]+imgContour[i][j+1]
                +imgContour[i+1][j-1]+imgContour[i+1][j]+imgContour[i+1][j+1]!= 8*255))
                {img[i][j]= 0;}
            else img[i][j]=255;
        }
	}
	return img;
    //throw runtime_error("Fonction doubleSeuillage seconde non implanté");
}

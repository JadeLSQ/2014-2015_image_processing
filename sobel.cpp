/** @file
 * Filtres de Sobel
 **/

#include <cmath>
#include "sobel.h"
#include<iostream>

/** filtre de Sobel horizontal
 *@param img une image en teintes de gris
 *@return une image en teintes de gris de l'intensite horizontal de img
 **/
ImageGris intensiteH(ImageGris img) {
	ImageGris sortie;
	sortie = ImageGris(img.size());// Allouer toutes les cases

    int nLine = img.size();
	int nCol = img[0].size();
	for (int i=0; i < nLine; i++){
        sortie[i]= vector<double>(nCol);
	}
	for (int i=1 ; i < img.size()-1 ; i++){
        for (int j=1 ; j < nCol-1 ; j++){
			sortie[i][j] = (img[i-1][j-1]+2*img[i][j-1]+img[i+1][j-1]);
			sortie[i][j] -=img[i-1][j+1]+2*img[i][j+1]+img[i+1][j+1];
			sortie[i][j] = sortie[i][j];
		}
	}

    return sortie;
}
/**
 *@param
 *@return
 **/
ImageGris intensiteV(ImageGris img) {
    ImageGris sortie;// Allouer toutes les cases
	sortie = ImageGris(img.size());
    int nLine = img.size();
	int nCol = img[0].size();
	for (int i=0; i < nLine; i++){
        sortie[i]= vector<double>(nCol);
	}

	for (int i=1 ; i < nLine-1 ; i++){
        for (int j=1 ; j < nCol-1 ; j++){
			sortie[i][j] = (img[i-1][j-1]+2*img[i-1][j]+img[i-1][j+1]);
			sortie[i][j] -=img[i+1][j-1]+2*img[i+1][j]+img[i+1][j+1] ;
			sortie[i][j] = sortie[i][j];
		}
	}
    return sortie;
}
/**
 *@param
 *@return
 **/
ImageGris intensite(ImageGris img) {
    ImageGris  imgH ;
	ImageGris  imgV ;
	ImageGris sortie;
	int nLine ;
	int nCol ;
	int i,j ;

	imgH=intensiteH(img) ;
	imgV=intensiteV(img) ;

	nLine = img.size() ;
    nCol = img[0].size() ;

	sortie = img ;

	for (i=0 ; i < nCol ; i++){
	   for (j=0 ; j < nLine ; j++){
	     sortie[i][j] = sqrt(pow(imgH[i][j],2)+pow(imgV[i][j],2)) ;
		 //sortie[i][j] = sqrt(sortie[i][j]) ;
	   }
	}
	return sortie;
}

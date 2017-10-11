/** @file
 * Lecture et écriture d'images au format PPM
 **/

#include <iostream>
#include <fstream>
#include "image.h"
#include "ppm.h"
#include "gris.h"

Image lirePPM(string source) {
    ifstream  lire(source);
    if (not lire)
      throw runtime_error("Fichier non trouvé:" + source );

    int nbColonne=0;
    int nbLigne=0;
    int intervalle=0;
    double chaquePixel=0;

    Image resultat;
    string P;
    Couleur color;
    lire >> P >> nbColonne >> nbLigne >> intervalle;
    for (int i=0;i<nbColonne; i=i++) {
        for (int j=0;j<nbLigne; j=j+3){
            lire >> color.r >> color.g >> color.b;
            resultat[i][j] = color;
        }
    }
    return resultat;
}

void ecrirePPM(Image img, string cible) {
   ofstream docEcrit(cible);
   docEcrit << "P3 " << img[0].size()<<" "<< img.size()<<" "<< 255 << endl;
   for(int i=0; i<img.size(); i++){
        for(int j=0; j<img[0].size(); j++){
        docEcrit << ((int)img[i][j].r) << " ";
        docEcrit << ((int)img[i][j].g) << " ";
        docEcrit << ((int)img[i][j].b) << " ";
        }
    docEcrit.close();
   }
}

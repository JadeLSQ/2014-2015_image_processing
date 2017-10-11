/** @file
 * Lecture et écriture d'images en niveau de gris au format PGM
 **/

#include <iostream>
#include <fstream>
#include "image.h"
#include "pgm.h"
/**Lecture d'images en niveau de gris au format PGM
 *@param source le nom d'un fichier PGM
 *@return resultat
 les parametres locaux:
 *@param nbColonne
 *@param nbLigne
 *@param P le type de fichier P*M
 *@param chaquePixel niveau du gris de chaque pixel que contient le fichier
 **/


ImageGris lirePGM(string source) {
    // Remplacer la ligne suivante par le code adéquat
    ifstream  lire(source);
    if (not lire)
      throw runtime_error("Fichier non trouvé:" + source );
    int nbColonne=0;
    int nbLigne=0;
    int intervalle=0;
    double chaquePixel=0;

    ImageGris resultat; //typedef vector<vector<double>> ImageGris;
    string p; // commentaire a supprimer dans la deuxieme lignes de chaque img ppm sinon marche pas
    lire >> p >> nbColonne >> nbLigne>> intervalle;
    resultat= ImageGris(nbLigne);
    for (int i=0;i<nbLigne; i++){
       resultat[i]= vector<double>(nbColonne);
        for (int j=0;j<nbColonne; j++){
            lire >> chaquePixel;
            resultat[i][j] = chaquePixel; //lire >> Couleur.r >> Couleur.g >> Couleur.b si c'etait PPM;
        }
    }
    return resultat;
    lire.close();
}

/**Ecrit une image en teintes de gris dans un fichier PGM qui s'appelle cible qui prend les valeurs de img
 *@param img une image en teintes de gris
 **/

void ecrirePGM(ImageGris img, string cible) { // img
    ofstream docEcrit(cible);
    docEcrit << "P2 " << img[0].size()<<" "<< img.size()<<" "<< 255 << endl;
    for(int i=0; i<img.size(); i++){
        for(int j=0; j<img[0].size(); j++)
        docEcrit << ((int)img[i][j]) << " ";
    }
    docEcrit.close();
}

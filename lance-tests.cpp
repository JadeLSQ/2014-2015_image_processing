/** @file
 * Programme lançant tous les tests du projet
 **/

#include <cstdlib>
#include <cmath>
#include <iostream>
#include "image.h"
#include "pgm.h"
#include "ppm.h"
#include "gris.h"
#include "sobel.h"
#include "seuillage.h"
#include "superpixel.h"
#include "tests.h"

using namespace std;

/** Fonction principale **/
int main() {
//    cout << "Tests de lecture et écriture d'image en teintes de gris PGM" << endl;
//    testLireEcrirePGM();
//    cout << endl; //test ok
//
//    cout << "Tests du filtre Sobel" << endl;
//    testSobel();
//    cout << endl; //test ok

//    cout << "Tests des filtres de seuillage" << endl;
//    testSeuillage();
//    cout << endl;
//
//    cout << "Tests des filtres de double seuillage" << endl;
//    testDoubleSeuillage();
//    cout << endl;
//
//    cout << "Tests de lecture et écriture d'image PPM" << endl;
//    testLireEcrirePPM();
//    cout << endl; //test ok
//
//    cout << "Tests de conversion gris <-> couleur" << endl;
//    testCouleurAuGris();
//    cout << endl; //test ok
//
//    cout << "Tests de la fonction Kmoyenne" << endl;
//    testKmoyenne();
//    cout << endl;

    cout << "Tests des filtres Super Pixel" << endl;
    testSuperPixel();
    //cout << plusProcheVoisin( Point( {1,0,1}),EnsPoint( { Point({2,3,6}), Point({1,0,0}), Point({-1,2,0})})) <<endl;
    cout << endl;

    cout << "Fin des tests!" << endl;
}

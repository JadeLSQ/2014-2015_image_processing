/** @file
 * Fonctions de test
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

/** Infrastructure minimale de test **/
#define ASSERT(test) if (!(test)) cout << "Test failed in file " << __FILE__ << " line " << __LINE__ << ": " #test << endl

/** Une image 4x4 pour faire des tests **/
Image imgTest = {
    { Couleur({0,0,0}), Couleur({255,255,255}), Couleur({255,0,0}), Couleur({255,255,0}) },
    { Couleur({0,0,255}), Couleur({0,255,0}), Couleur({0,255,255}), Couleur({120,120,120}) },
    { Couleur({42,174,86}), Couleur({141,194,57}), Couleur({68,107,43}), Couleur({73, 98, 40}) },
    { Couleur({60, 196, 74}), Couleur({141,194,57}), Couleur({61,102,43}), Couleur({214,38,102}) }
};

/** Une image 4x4 en teintes de gris pour faire des tests **/
ImageGris imgGrisTest = {
    {0, 255, 54.213, 236.589},
    {18.411, 182.376, 200.787, 120},
    {139.583, 172.841, 94.0878, 88.4974},
    {158.278, 172.841, 89.0236, 80.0384}
};


/** Teste si deux images en teintes de gris sont égales modulo imprécision numérique
 * En cas de différence un message est affiché
 * @param a une image en teintes de gris
 * @param b une image en teintes de gris
 * @param precision un flottant positif: la précision souhaitée; typiquement 0.001
 * return vrai si les images sont égales et faux sinon
 **/
bool ImageGrisEgal(ImageGris a, ImageGris b, float precision) {
    if (a.size() != b.size())  {
        cout << "Nombre de lignes différent" << endl;
        return false;
    }
    for (int i=0; i<a[0].size(); i++)
        if (a[0].size() != b[i].size()) {
            cout << "Nombre de colonnes différent" << endl;
            return false;
        }
    for (int i=0; i<a.size(); i++)
        for (int j=0; j<a[0].size(); j++)
            if (abs(a[i][j] - b[i][j]) > precision) {
                cout << "Valeur differentes en position " << i << "," << j
		     << ": " << a[i][j] << " au lieu de " << b[i][j] << endl;
                return false;
            }
    return true;
}

void testLireEcrirePGM(){
    string cible = "io/test.pgm";
    ecrirePGM(imgGrisTest, cible);
    // Comme on tronque en entiers, la précision peut différer de 1
    ASSERT( ImageGrisEgal(lirePGM(cible), imgGrisTest, 1) );
}

void testLireEcrirePPM(){
    cout << "Vérifier que les images obtenues dans 'io_couleur/' sont semblables à celles fournies dans 'io_couleur/correction/'" << endl;

    ecrirePPM(lirePPM("images/ppm/Baboon.512.ppm"),  "io_couleur/Baboon.512.ppm");
    ecrirePPM(lirePPM("images/ppm/Billes.256.ppm"),  "io_couleur/Billes.256.ppm");
    ecrirePPM(lirePPM("images/ppm/Embryos.512.ppm"), "io_couleur/Embryos.512.ppm");
    ecrirePPM(lirePPM("images/ppm/House.256.ppm"),   "io_couleur/House.256.ppm");
    ecrirePPM(lirePPM("images/ppm/Lena.512.ppm"),    "io_couleur/Lena.512.ppm");
}

void testCouleurAuGris() {
    ASSERT( ImageGrisEgal(CouleurAuGris(imgTest),imgGrisTest,0.001));
}

void testSobel() {
    ASSERT( ImageGrisEgal(intensiteH(imgGrisTest),
			  ImageGris( {
			      {0, 0, 0, 0},
			      {0, -373.47, 227.507, 0},
			      {0, -22.1312, 323.866, 0},
			      {0, 0, 0, 0}
			  }),
			  0.001) );
    ASSERT( ImageGrisEgal(intensiteV(imgGrisTest),
			  ImageGris( {
			      {0, 0, 0, 0},
			      {0, -15.1398, 150.501, 0},
			      {0, -9.0336, 273.023, 0},
			      {0, 0, 0, 0}
			  }),
			  0.001) );
    ASSERT( ImageGrisEgal(intensite(imgGrisTest),
			  ImageGris( {
			      {0, 0, 0, 0},
			      {0, 373.777, 272.782, 0},
			      {0, 23.9039, 423.593, 0},
			      {0, 0, 0, 0}
			  }),
			  0.001) );

    cout << "Vérifier que les images obtenues dans 'sobel/' sont semblables à celles fournies dans 'sobel/correction/'" << endl;
    ecrirePGM(intensite(lirePGM("images/pgm/Baboon.512.pgm" )), "sobel/Baboon.512.pgm");
    ecrirePGM(intensite(lirePGM("images/pgm/Billes.256.pgm" )), "sobel/Billes.256.pgm");
    ecrirePGM(intensite(lirePGM("images/pgm/Embryos.512.pgm")), "sobel/Embryos.512.pgm");
    ecrirePGM(intensite(lirePGM("images/pgm/House.256.pgm"  )), "sobel/House.256.pgm");
    ecrirePGM(intensite(lirePGM("images/pgm/Lena.512.pgm"   )), "sobel/Lena.512.pgm");
}

void testSeuillage() {
    ASSERT( ImageGrisEgal(seuillage( imgGrisTest, 80),
			  ImageGris( {
			      {255, 0, 255, 0},
			      {255, 0, 0, 0},
			      {0, 0, 0, 0},
			      {0, 0, 0, 0}
			  }),
			  0.001) );
    ASSERT( ImageGrisEgal(seuillage( intensite(imgGrisTest), 80),
			  ImageGris( {
			      {255, 255, 255, 255},
			      {255, 0, 0, 255},
			      {255, 255, 0, 255},
			      {255, 255, 255, 255}
			  }),
			  0.001) );
    ASSERT( ImageGrisEgal(doubleSeuillage(intensite(imgGrisTest), 220, 80, 4 ),
                          ImageGris( {
                              {255, 255, 255, 255},
                              {255, 0, 0, 255},
                              {255, 255, 0, 255},
                              {255, 255, 255, 255}
                          }),
                          0.001) );


    cout << "Vérifier que les images obtenues dans 'seuillage/' sont semblables à celles fournies dans 'seuillage/correction/'" << endl;
    ecrirePGM(seuillage(intensite(lirePGM("images/pgm/Billes.256.pgm")), 80), "seuillage/Billes.256.pgm");
    ecrirePGM(seuillage(intensite(lirePGM("images/pgm/Lena.512.pgm"  )), 80), "seuillage/Lena.512.pgm");
    cout << "\tProposer des seuils pour Embryos.512.ppm et House.256.ppm" << endl;
    ecrirePGM(seuillage(intensite(lirePGM("images/pgm/House.256.pgm")), 80), "seuillage/House.256.pgm");
    ecrirePGM(seuillage(intensite(lirePGM("images/pgm/Embryos.512.pgm"  )), 80), "seuillage/Embryos.512.pgm");
}

void testDoubleSeuillage(){
    cout << "Vérifier que les images obtenues dans 'seuillage_double/' sont semblables à celles fournies dans 'seuillage_double/correction/'" << endl;
    ecrirePGM(doubleSeuillage(intensite(lirePGM("images/pgm/Billes.256.pgm")), 500, 80, 100), "seuillage_double/Billes.256.pgm");
    ecrirePGM(doubleSeuillage(intensite(lirePGM("images/pgm/Lena.512.pgm"  )), 500, 80, 100), "seuillage_double/Lena.512.pgm");
    cout << "\tProposer des seuils pour Embryos.512.ppm et House.256.ppm" << endl;
    ecrirePGM(doubleSeuillage(intensite(lirePGM("images/pgm/House.256.pgm")), 500, 80, 100), "seuillage_double/House.256.pgm");
    ecrirePGM(doubleSeuillage(intensite(lirePGM("images/pgm/Embryos.512.pgm"  )), 500, 80, 100), "seuillage_double/Embryos.512.pgm");
}

void testSuperPixel() {
    ASSERT( distancePoints( Point( {2,0,1}), Point( {2,0,1})) == 0);
    ASSERT( distancePoints( Point( {1,0,1}), Point( {1,0,0})) == 1);
    ASSERT( plusProcheVoisin( Point( {1,0,1}),
                              EnsPoint( { Point({2,3,6}), Point({1,0,0}), Point({-1,2,0})}))== 1);
    ASSERT( ImageGrisEgal(CouleurAuGris(superPixel( imgTest, 2, 60, 15 )),
			  ImageGris( {
			      {71.971, 71.971, 71.971, 71.971},
			      {71.971, 71.971, 71.971, 71.971},
			      {71.971, 71.971, 71.971, 71.971},
			      {71.971, 71.971, 71.971, 71.971}
			      }),
			  0.001) );
    //cout << "Vérifier que les images obtenues dans 'superpixel/' sont semblables à celles fournies dans 'superpixel/correction/'" << endl;
    //ecrirePPM(superPixel(lirePPM("images/Billes.256.ppm"), 1, 30, 25),  "superpixel/Billes.256.ppm");
    //ecrirePPM(superPixel(lirePPM("images/Baboon.512.ppm"), 2, 60, 15),  "superpixel/Baboon.512.ppm");
    //ecrirePPM(superPixel(lirePPM("images/Lena.512.ppm"  ), 2, 60, 15),  "superpixel/Lena.512.ppm");

    cout << "\tProposer des paramètres pour Embryos.512.ppm et House.256.ppm" << endl;

}


void testKmoyenne(){
    EnsPoint P;
    for(int i=0;i<100;i++){
        double xbiais=0.;
        double ybiais=0.;
        if(i%3==1){
            xbiais = 100.;
            ybiais = 0.;
        }
        if(i%3==2){
            xbiais = 0.;
            ybiais = 100.;
        }
        Point p;
        p.push_back(xbiais + 1.*(rand()%10)-20.);
        p.push_back(ybiais + 1.*(rand()%10)-20.);
        P.push_back(p);
    }

    EnsPoint C = {
        {75.,50.}, {50., 75.}, {25., 25.}};

    EnsPoint Cout = Kmoyenne(P,C,100);
    EnsPoint CRef = FAST_Kmoyenne(P,C,100);

    for(int i=0; i<2; i++)
	for(int j=0; j<2; j++)
	    ASSERT( abs( Cout[i][j] - CRef[i][j] ) <= 0.5 );
}

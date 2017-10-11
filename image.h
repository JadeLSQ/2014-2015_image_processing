/** @file
 * Structures de données pour représenter des images
 **/

#ifndef _IMAGE_H
#define _IMAGE_H

#include <vector>
#include <stdexcept>
using namespace std;

/** Structure de donnée pour représenter un pixel en couleur **/
struct Couleur {
    /** Intensité de rouge **/
    double r;
    /** Intensité de vert **/
    double g;
    /** Intensité de bleu **/
    double b;
};

/** Structure de donnée pour représenter une image **/
typedef vector<vector<Couleur> > Image;

/** Structure de donnée pour représenter une image en teintes de gris **/
typedef vector<vector<double> > ImageGris;

#endif

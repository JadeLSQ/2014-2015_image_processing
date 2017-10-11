/** @file
 * Filtre Super Pixel
 **/

#include "image.h"

/** Structure de donnée pour représenter un point dans l'espace spacio colorimétrique **/
typedef vector<double> Point;

/** Structure de donnée pour représenter un ensemble de points dans l'espace spacio colorimétrique **/
typedef vector<Point> EnsPoint;


/** Renvoie la distance entre deux points
 * @param p un point
 * @param c un point
 * @return la distance entre p et c
 **/
double distancePoints(Point p, Point c);

/** Renvoie la distance Euclidienne d'un point à un ensemble de points
 * @param p un point
 * @param C un ensemble de points
 * @return la distance
 **/
double distanceAEnsemble(Point p, EnsPoint C);

/** Renvoie le plus proche voisin d'un point p dans un ensemble C
 * @param p un point
 * @param C un ensemble de points
 * @return l'index du plus proche voisin
 **/
int plusProcheVoisin(Point p, EnsPoint C);

/** Renvoie les points p de P tels que C[k] est le plus proche voisin de p dans C
 * @param P un ensemble de points
 * @param C un ensemble de points
 * @param k un entier
 * @return un sous ensemble des points de P
 **/
EnsPoint sousEnsemble(EnsPoint P, EnsPoint C,int k);

/** Renvoie le barycentre d'unn ensemble de points
 * @param Q un ensemble de points
 * @return c le barycentre de Q
 **/
Point barycentre(EnsPoint Q);

/** Renvoie la K-moyenne de deux ensembles de points
 * @param P un ensemble de points
 * @param C un ensemble de points
 * @param nbAmeliorations un entier le nombre de fois où l'amélioration va être effectuée
 * @return C un ensemble de points les positions finales de points pilotes
 **/
EnsPoint Kmoyenne(EnsPoint P, EnsPoint C, int nbAmeliorations);

/** Implantation optimisée de K-moyenne
 * @param P un ensemble de points
 * @param C un ensemble de points
 * @param nbAmeliorations un entier le nombre de fois où l'amélioration va être effectuée
 * @return C un ensemble de points les positions finales de points pilotes
 **/
EnsPoint FAST_Kmoyenne(EnsPoint P, EnsPoint C, int nbAmeliorations);

/** Renvoie un ensemble de points dans l'espace spatio colorimétrique regulièrement espacé dans une image
 * @param img une image
 * @param lambda un double
 * @param mu un entier
 * @return un ensemble de points dans l'espace spatio colorimétrique
 **/
EnsPoint pivotSuperPixel (Image img, double lambda, int mu);

/** Renvoie les superpixels d'une image dans l'espace spatio colorimétrique
 * @param img une image en teintes de gris
 * @param lambda un double
 * @param mu un entier
 * @param nbAmeliorations un entier
 * @return un ensemble de points, les superpixels
 **/
EnsPoint superPixels(Image img, double lambda, int mu, int nbAmeliorations);

/** Filtre SuperPixel
 * @param img une image
 * @param lambda un double
 * @param mu un entier
 * @param nbAmeliorations
 * @return l'image associée aux superpixels d'une image
 **/
Image superPixel(Image img, double lambda, int mu, int nbAmeliorations);

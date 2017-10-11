/** @file
 * Lecture et écriture de fichiers au format PGM
 **/

#include <string>
#include "image.h"

/** Construire une image en teintes de gris depuis un fichier PGM
 * @param source le nom d'un fichier PGM
 * @return une image en teintes de gris
 **/
ImageGris lirePGM(string source);

/** Ecrit une image en teintes de gris dans un fichier PGM
 * @param img une image en teintes de gris
 * @param cible le nom d'un fichier PGM
 **/
void  ecrirePGM(ImageGris img, string cible);

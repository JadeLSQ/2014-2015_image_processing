/** @file
 * Filtres de Sobel
 **/

#include "image.h"

/** filtre de Sobel horizontal
 * @param img une image en teintes de gris
 * @return une image en teintes de gris de l'intensité horizontale de img
 **/
ImageGris intensiteH(ImageGris img);

/** filtre de Sobel vertical
 * @param img une image en teintes de gris
 * @return une image en teintes de gris de l'intensité verticale de img
 **/
ImageGris intensiteV(ImageGris img);

/** filtre de Sobel
 * @param img une image en teintes de gris
 * @return une image en teintes de gris de l'intensité de img
 **/
ImageGris intensite(ImageGris img);

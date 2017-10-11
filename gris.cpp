/** @file
 * Filtres de conversion couleur <-> teintes de gris
 **/

#include "gris.h"
#include "image.h"

/** Transforme une image couleur en une image en teintes de gris
 *@param img une image
 *@return une image en teintes de gris
 **/

ImageGris CouleurAuGris(Image img) { //vector<vector<couleur>> Image
   ImageGris sortie;
   sortie = ImageGris(img.size());//correction size s'utilise avec () |15|error: no matching function for call to ‘std::vector<std::vector<double, std::allocator<double> >, std::allocator<std::vector<double, std::allocator<double> > > >::vector(<unresolved overloaded function type>)’|
   float c=0;
     for (int i=0; i<img.size(); i++){
       sortie[i]= vector<double>(img[0].size());//|18|error: no matching function for call to ‘std::vector<std::vector<double, std::allocator<double> >, std::allocator<std::vector<double, std::allocator<double> > > >::vector(<unresolved overloaded function type>)’|
       for (int j=0; j<img[0].size(); j++){
       c=((img[i][j].r)*0.2126+(img[i][j].g)*0.7152+(img[i][j].b)*0.0722)/(0.2126+0.7152+0.0722);
       sortie[i][j]=c;
       //sortie[i].push_back(c);
       }
     }
   return sortie;
}

/**Transforme une image en teintes de gris en couleurs (mais grise)
 *@param img une image en teintes de gris
 *@return une image
 **/
Image GrisACouleur(ImageGris img) {
   Image sortie;
   Couleur pixelcolor;
   pixelcolor.r=0;
   pixelcolor.g=0;
   pixelcolor.b=0;
   double nLigne,nCol;
   nLigne=img.size();
   nCol=img[0].size();
   sortie = Image(nLigne);//allocation
     for (int i=0; i<nLigne; i++){
       sortie[i]= vector<Couleur>(nCol);
       for (int j=0; j<nCol; j+=3){
       pixelcolor.r=img[i][j]*3;
       pixelcolor.g=img[i][j]*3;
       pixelcolor.b=img[i][j]*3;
       sortie[i].push_back(pixelcolor);
       }
     }
   return sortie;
}

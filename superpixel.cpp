/** @file
 * Filtre Super Pixel
 **/

#include <cmath>
#include "superpixel.h"


double distancePoints(Point p, Point c) {
 double distance =0 ;
    if (p.size() != c.size())
    throw runtime_error("la taille des deux vectors points est differente");
 for (int i=0; i<p.size(); i++){
    distance += pow((p[i]-c[i]),2);
    distance = sqrt (distance) ;
 }
    return distance;
}

double distanceAEnsemble(Point p, EnsPoint C) {
    double dMin =0 ;
	double distance ;

  if (C.size()==0)
   throw runtime_error("l'Ensemble C est vide, veuillez rentrer un ensemble non vide a nouveau");

  for (int i=0; i < C.size() ; i++){
    distance =  distancePoints(p,C[i]) ;
    dMin= (distance > dMin)? dMin : distance ;
  }
  return dMin ;
}

int plusProcheVoisin(Point p, EnsPoint C) {
    double dMin = distancePoints(p,C[0]) ;
	double distance ;
	distance =0;
	int index;

  if (C.size()==0)
   throw runtime_error("l'Ensemble C est vide, veuillez rentrer un ensemble non vide a nouveau");
  for (int i=1; i < C.size() ; i++){
    distance =  distancePoints(p,C[i]) ;
    if (distance < dMin) {
        dMin = distance;
        index=i;
    }
   }
//  double dMin ;
//  dMin = distanceAEnsemble (p, C);
//  vector<int> iMax;
//
//  int index;
//  vector <double> Ensdist;
//
//  for (int i=0 ; i<C.size() ; i++){
//     if (distancePoints(p, C[i]) <= dMin ){
//     iMax.push_back(i);
//     Ensdist.push_back(distancePoints(p, C[i]));
//     }
//  }
//  for (int k=0 ; k<Ensdist.size() ; k++){
//    if (dMin > Ensdist[k]) index = iMax[k];
//     //index=.push_back(i);
//  }
  return index;
}

/** revoie les points de p de P tels que  C[k] est le plus proche voisin de p dans C
 *
 **/
EnsPoint sousEnsemble(EnsPoint P,EnsPoint C,int k) {
   EnsPoint sortie;
  for (int i=0 ; i<P.size(); i++){
     if (k==plusProcheVoisin(P[i],C)) //plusProcheVoisin(Point p,EnsPoint C)
        sortie.push_back(P[i]) ;
  }
  return sortie;
}

Point barycentre(EnsPoint Q) {
  Point sortie;
  sortie = Q[0] ;

  for (int i=0; i< Q.size(); i++){
    for (int j=0 ; j< sortie.size(); j++)
       sortie[j]+=Q[i][j] ;
  }
  for (int i=0; i< sortie.size(); i++)
     sortie[i] /= Q.size();

  return sortie;
}

EnsPoint Kmoyenne(EnsPoint P,EnsPoint C, int nbAmeliorations) {
    // Remplacer la ligne suivante par le code adéquat
    throw runtime_error("Fonction Kmoyenne non implanté");
}

EnsPoint FAST_Kmoyenne(EnsPoint P,EnsPoint C, int nbAmeliorations) {
    vector<int> label;
    label.resize(P.size());
    for(int n=0; n<nbAmeliorations; n++) {
        vector<int> clusterSize;
        clusterSize.resize(C.size(),0);
        for (int p=((int)P.size())-1; p>=0; p--) {
            double di = 0;
            int nn=0;
            for(int d=((int)P[0].size())-1; d>=0; d--)
                di+=(P[p][d]-C[0][d])*(P[p][d]-C[0][d]);
            for(int c=((int)C.size())-1; c>=1; c--) {
                double dt=0;
                for(int d=((int)P[0].size())-1; d>=0; d--)
                    dt+=(P[p][d]-C[c][d])*(P[p][d]-C[c][d]);
                if(dt<di) {
                    di=dt;
                    nn=c;
                }
            }
            label[p]=nn;
            clusterSize[nn]++;
        }
        for (int p=((int)P.size())-1; p>=0; p--)
            for(int d=((int)P[0].size())-1; d>=0; d--)
                C[label[p]][d]+=P[p][d];
        for(int c=((int)C.size())-1; c>=0; c--)
            if(clusterSize[c]!=0)
                for(int d=((int)P[0].size())-1; d>=0; d--)
                    C[c][d] = C[c][d]/(clusterSize[c]+1);
    }
    return C;
}

EnsPoint pivotSuperPixel(Image img, double lambda, int mu) {
    // Remplacer la ligne suivante par le code adéquat
    throw runtime_error("Fonction pivotSuperPixel non implanté");
}

EnsPoint superPixels(Image img,double lambda, int mu, int nbAmeliorations) {
    // Remplacer la ligne suivante par le code adéquat
    throw runtime_error("Fonction superPixels non implanté");
}

Image superPixel(Image img, double lambda, int mu, int nbAmeliorations) {
    // Remplacer la ligne suivante par le code adéquat
    throw runtime_error("Fonction superPixel non implanté");
}

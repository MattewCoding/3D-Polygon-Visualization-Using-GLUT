#ifndef SURFACE_H_INCLUDED
#define SURFACE_H_INCLUDED

#include "geometry.h"
typedef struct{
    int nbSom;
    int nbFacettes;
    int **facettes;
    Point *sommets;
} Surface;

#endif // SURFACE_H_INCLUDED

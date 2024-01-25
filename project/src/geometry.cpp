#include <stdio.h>
#include <stdlib.h>

#include "geometry.h"
#include "math_geometry.h"

// Discretisation du tableau de a à b en m pas
void discr(int m, double a, double b, double *T){
    float pas = (b-a)/(m-1);
    T[0] = a;
    for(int i=1; i<=m; i++){
        T[i] = T[i-1] + pas;
    }
}

Point Q(int r, int i, double t, Point *p){
    if(r == 0){
        return p[i];
    } return sumPoint(muxScal(1-t, Q(r-1, i, t, p)), muxScal(t, Q(r-1, i+1, t, p)));
}


#include <stdio.h>
#include <math.h>
#include "geometry.h"
#include "math_geometry.h"
#include "surface.h"
Point sumPoint(Point p, Point q){
    Point res;
    res.x = p.x + q.x;
    res.y = p.y + q.y;
    res.z = 1.0;
    res.cH = 1.0;
    return res;
}

Point muxScal(double d, Point p){
    p.x *= d; p.y *= d; return p;
}

int signeVal(float val){
    if(val < 0.0) return -1;
    if(val > 0.0) return 1;
    return 0;
}

float auxF(float omega, float m){
    return signeVal(sin(omega)) * (float)pow(fabs(sin(omega)), m);
}

float auxG(float omega, float m){
    return signeVal(cos(omega)) * (float)pow(fabs(cos(omega)), m);
}

// Pour l'étirement
Point surfaceNoAspRatio(Point p, double radX, double radY, double radZ, double teta, double phi, int option){
    return surface(p, radX, radY, radZ, teta, phi, option, 1.0);
}

// Pour le tore
Point surfaceAspRatio(Point p, double radius, double teta, double phi, int option, float asp_ratio){
    return surface(p, radius, radius, radius, teta, phi, option, asp_ratio);
}

Point surfaceCircle(Point p, double radius, double teta, double phi, int option){
    return surface(p, radius, radius, radius, teta, phi, option, 1.0);
}

// Rappel : teta va de [0;pi] et phi [0 ; 2*pi]
Point surface(Point p, double radX, double radY, double radZ, double teta, double phi, int option, float asp_ratio){
    // p here is the center point as defined in main.cpp
    switch(option){
        case 0: // Tore
            // Dans ce cas, nous avons besoin que teta soit compris entre [0;2*pi]
            p.x += (radX + asp_ratio*radX*cos(teta*2)) * cos(phi);
            p.y += (radY + asp_ratio*radY*cos(teta*2)) * sin(phi);
            p.z += asp_ratio*radZ * sin(teta*2);
            break;
        case 1: // Sphere
            p.x += radX*sin(teta)*cos(phi);
            p.y += radY*sin(teta)*sin(phi);
            p.z += radZ*cos(teta);
            break;
        case 2: // Cylindre
            p.x += radX*cos(phi);
            p.y += teta - M_PI/2;
            p.z += radZ*sin(phi);
            break;
        case 3: // Superquadratique
            p.x += auxG(teta-M_PI/2, 2/radX) * auxG(phi-M_PI, 2/radX);
            p.y += auxG(teta-M_PI/2, 2/radY) * auxF(phi-M_PI, 2/radY);
            p.z += auxF(teta-M_PI/2, 2/radZ);
            break;
    }

    p.cH = 1.0;
    return p;
}

Surface transf(Surface s, int dx, int dy, int dz, float rotaXY, float rotaYZ, float rotaZX, float scaleX, float scaleY, float scaleZ, Point center){
    int nbSom = s.nbSom;
    Point *sommet = s.sommets;
    Point pt;
    double matxTrans[4][4] = { {scaleX*cos(rotaXY)*cos(rotaZX), -sin(rotaXY)                              , sin(rotaZX)                              , (double)dx/10},
                                                 {sin(rotaXY)                               , scaleY*cos(rotaXY)*cos(rotaYZ), -sin(rotaYZ)                             , (double)dy/10},
                                                 {-sin(rotaZX)                              , sin(rotaYZ)                               , scaleZ*cos(rotaYZ)*cos(rotaZX), (double)dz/10},
                                                 {0                                             , 0                                             , 0                                             , 1                     },
                                               };
    for(int i = 0; i<nbSom; i++){
        pt = sommet[i];
        GLfloat x = pt.x - center.x;
        GLfloat y = pt.y - center.y;
        GLfloat z = pt.z - center.z;

        pt.x = x*matxTrans[0][0] +  y*matxTrans[0][1] + z*matxTrans[0][2] + matxTrans[0][3] + center.x;
        pt.y = x*matxTrans[1][0] +  y*matxTrans[1][1] + z*matxTrans[1][2] + matxTrans[1][3] + center.y;
        pt.z = x*matxTrans[2][0] +  y*matxTrans[2][1] + z*matxTrans[2][2] + matxTrans[2][3] + center.z;
        pt.cH = x*matxTrans[3][0] +  y*matxTrans[3][1] + z*matxTrans[3][2] + matxTrans[3][3];
        sommet[i] = pt;
    }
    s.sommets = sommet;
    return s;
}

Surface spinAround(Surface s, float degree, Point center){
    return transf(s, 0, 0, 0,0.0, 0.0, (float)degree*M_PI/180.0, 1.0, 1.0, 1.0, center);
}

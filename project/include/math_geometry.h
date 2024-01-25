#ifndef MATH_GEOMETRY_H_INCLUDED
#define MATH_GEOMETRY_H_INCLUDED

#include "surface.h"
Point sumPoint(Point p, Point q);
Point muxScal(double d, Point p);

int signeVal(float val);
float auxF(float omega, float m);
float auxG(float omega, float m);
Point surfaceNoAspRatio(Point p, double radX, double radY, double radZ, double teta, double phi, int option);
Point surfaceAspRatio(Point p, double radius, double teta, double phi, int option, float asp_ratio);
Point surfaceCircle(Point p, double radius, double teta, double phi, int option);
Point surface(Point p, double radX, double radY, double radZ, double teta, double phi, int option, float asp_ratio);

Surface transf(Surface s, int dx, int dy, int dz, float rotaXY, float rotaYZ, float rotaZX, float scaleX, float scaleY, float scaleZ, Point center);
Surface spinAround(Surface s, float degree, Point center);

#endif // MATH_GEOMETRY_H_INCLUDED

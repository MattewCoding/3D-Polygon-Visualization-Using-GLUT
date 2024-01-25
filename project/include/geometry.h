#ifndef GEOMETRY_H_INCLUDED
#define GEOMETRY_H_INCLUDED

#ifndef GLUT_LIBRARY
    #define GLUT_LIBRARY
    #include <GL/glu.h>
    #include <GL/glut.h>
#endif // GLUT_LIBRARY

#define MAX_POINTS_ON_FRAME 100
/* Point drawing */
typedef struct {
    GLfloat x;
    GLfloat y;
    GLfloat z;
    GLfloat cH;
} Point;

void discr(int m, double a, double b, double *T);
Point Q(int r, int i, double t, Point *p);
void casteljau(Point *p, int n, int m);

void draw_pixel(float x ,float y, float z);
#endif // GEOMETRY_H_INCLUDED


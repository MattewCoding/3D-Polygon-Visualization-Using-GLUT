#include <stdio.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <time.h>
#include <stdlib.h>
#include <math.h>
#include "surface.h"
#include "geometry.h"
#include "math_geometry.h"

#if defined(_WIN32) || defined(WIN32)
    #include <windows.h>
#endif

#define HEIGHT 750
#define WIDTH 750
#define MAX_POINTS_ON_FRAME 100
#define ALLOC_MEM(type, taille) ((type*)malloc(sizeof(type) * taille))

/* Variables globales */
char title[] = "Drawing Board"; // Fenetre

int nbRegXYCircle, nbStepsZ; // Creation
double radius;
double superQ[3];

Surface s; // Polygone
Point circleCenter;
float asp_ratio;
int step;

int optionFigure; // Type
int trigs, isRotate;

void draw_shape(Point* sommets, int* ptsDeFace){
    int fSize =  ptsDeFace[0]+1;

    Point pt1 = sommets[ptsDeFace[1]];
    double z = pt1.z;

    // This part is a purely aesthetic choice
    // More distant faces = more transparent and thinner => illusion of perspective
    double colorGZBlue = 0.15 + (z/2.0)*(0.55-0.15);
    double colorBZBlue = 0.25 + (z/2.0)*(0.85-0.25);
    glColor3f(0.0, colorGZBlue, colorBZBlue);

    if(trigs){
        glBegin(GL_POLYGON);
            glVertex3f(sommets[ptsDeFace[2]].x, sommets[ptsDeFace[2]].y, sommets[ptsDeFace[2]].z);
            glVertex3f(sommets[ptsDeFace[3]].x, sommets[ptsDeFace[3]].y, sommets[ptsDeFace[3]].z);
        if(fSize == 4){
                glVertex3f(sommets[ptsDeFace[1]].x, sommets[ptsDeFace[1]].y, sommets[ptsDeFace[1]].z);
            glEnd();
        } else {
                glVertex3f(sommets[ptsDeFace[4]].x, sommets[ptsDeFace[4]].y, sommets[ptsDeFace[4]].z);
            glEnd();

            colorGZBlue = 0.2 + (z/2.0)*(0.6-0.2);
            colorBZBlue = 0.3 + (z/2.0)*(0.9-0.3);
            glColor3f(0.0, colorGZBlue, colorBZBlue);
            glBegin(GL_POLYGON);
                glVertex3f(sommets[ptsDeFace[2]].x, sommets[ptsDeFace[2]].y, sommets[ptsDeFace[2]].z);
                glVertex3f(sommets[ptsDeFace[4]].x, sommets[ptsDeFace[4]].y, sommets[ptsDeFace[4]].z);
                glVertex3f(sommets[ptsDeFace[1]].x, sommets[ptsDeFace[1]].y, sommets[ptsDeFace[1]].z);
            glEnd();
        }
    } else{
        glBegin(GL_POLYGON);
            for(int j=1; j<fSize; j++){
                int ptIndexLocation = ptsDeFace[j];
                glVertex3f(sommets[ptIndexLocation].x, sommets[ptIndexLocation].y, sommets[ptIndexLocation].z);
            }
        glEnd();
    }
}

/* Définition et allocation */
int** allocMemMatEnt(int nbRows, int nbCols){
    int** matrix = ALLOC_MEM(int*, nbRows); // Une face de la sphère

    for(int i=0; i<nbRows; i++){
        matrix[i] = ALLOC_MEM(int, nbCols); // Les points de la sphère
    }
    return matrix;
}

Surface allocMemS_Surf(int nbRegXYCircle, int nbStepsZ){
    Surface s;

    if(optionFigure == 0){
        s.nbSom = (nbRegXYCircle-1) * (nbStepsZ-1);
        s.nbFacettes = (nbRegXYCircle-1) * (nbStepsZ-1);
    } else {
        s.nbSom = (nbRegXYCircle-1) * (nbStepsZ-2) + 1 + 1;
        s.nbFacettes = (nbRegXYCircle-1) * (nbStepsZ-1);
    }
    s.sommets = ALLOC_MEM(Point, s.nbSom);
    s.facettes = allocMemMatEnt(s.nbFacettes, 5);
    return s;
}

/* Affichage */
void affFacettes(int nbRegXYCircle, int nbStepsZ, Surface s){
    int n = s.nbFacettes;
    int **facettes = s.facettes;
    for(int i=0; i<n; i++){
        int fSize =  facettes[i][0]+1;

        if(i < 10) printf(" %d: ", i);
        else printf("%d: ", i);

        for(int j=1; j<fSize; j++){
            int face = facettes[i][j];

            if(face < 10) printf(" %d ", face);
            else printf("%d ", face);
        }
        printf("\n");
    }
}

void affDouble(double* tab, int n){
    for(int i=0; i<n; i++){
        printf("%f, ", tab[i]);
    }
    printf("\n");
}

void affSurface(int nbRegXYCircle, int nbStepsZ, Surface s){
    int n = s.nbSom;
    Point *tab = s.sommets;
    for(int i=0; i<n; i++){
        printf("%d: %f, %f, %f", i, tab[i].x, tab[i].y, tab[i].z);
        printf("\n");
    }
}

/* Création et génération */
void espaceParam(double a, double b, double c, double d, int nbStepsZ, int nbRegXYCircle, double *tetaDiscr, double *phiDiscr){
    discr(nbStepsZ,a,b,tetaDiscr);
    discr(nbRegXYCircle,c,d,phiDiscr);
}

void generSommetsTore(int nbStepsZ, int nbRegXYCircle, double *tetaDiscr, double *phiDiscr, Point *sommets) {
    int nbS = 0;

    for (int m = 0; m < nbStepsZ - 1; m++) {
        double teta = tetaDiscr[m];

        for (int p = 0; p < nbRegXYCircle - 1; p++) {
            double phi = phiDiscr[p];
            sommets[nbS++] = surfaceAspRatio(circleCenter, radius, teta, phi, optionFigure, asp_ratio);
        }
    }
}

void generSommets(int nbStepsZ, int nbRegXYCircle, double *tetaDiscr, double *phiDiscr, Point *sommets){
    int nbS = 0;
    double teta = tetaDiscr[0], phi = phiDiscr[0];
    switch (optionFigure){
        case 1: sommets[nbS] = surfaceCircle(circleCenter, radius, teta, phi, optionFigure); break; // Devant du cercle
        case 2: sommets[nbS] = surfaceCircle(circleCenter, 0, tetaDiscr[1], phi, optionFigure); break;
        case 3: sommets[nbS] = surfaceNoAspRatio(circleCenter, superQ[0], superQ[1], superQ[2], teta, phi, optionFigure); break; // Arrière du superquad
    }

    nbS++;
    for(int m = 1; m<=nbStepsZ-2; m++){
        teta = tetaDiscr[m];
        for(int p = 0; p<=nbRegXYCircle-2; p++){
            phi = phiDiscr[p];
            switch (optionFigure){
                case 3: sommets[nbS] = surfaceNoAspRatio(circleCenter, superQ[0], superQ[1], superQ[2], teta, phi, optionFigure); break;
                // case 2: case 1:
                default: sommets[nbS] = surfaceCircle(circleCenter, radius, teta, phi, optionFigure);
            }
            nbS++;
        }
    }
    phi = phiDiscr[0];
    teta = tetaDiscr[nbStepsZ - 1];
    switch (optionFigure){
        case 1: sommets[nbS] = surfaceCircle(circleCenter, radius, teta, phi, optionFigure); break; // Arrière du cercle
        case 2: sommets[nbS] = surfaceCircle(circleCenter, 0, tetaDiscr[nbStepsZ - 2], phi, optionFigure); break;
        case 3: sommets[nbS] = surfaceNoAspRatio(circleCenter, superQ[0], superQ[1], superQ[2], teta, phi, optionFigure); break; // Devant du superquad
    }
}

void generFacettes(int nbStepsZ, int nbRegXYCircle, int **facettes){
    int nf = 0;

    for(int m=1; m<=nbRegXYCircle-2; m++){
        facettes[nf][0] = 3;
        facettes[nf][1] = 0;
        facettes[nf][2] = m;
        facettes[nf][3] = m+1;
        facettes[nf][4] = -1; // Ce facette n'a pas de 4ème point
        nf++;
    }
    facettes[nf][0] = 3;
    facettes[nf][1] = 0;
    facettes[nf][2] = nbRegXYCircle-1;
    facettes[nf][3] = 1;
    facettes[nf][4] = -1; // Ce facette n'a pas de 4ème point
    nf++;

    for(int p=1; p<=nbStepsZ-3; p++){
        for(int m=1; m<=nbRegXYCircle-2; m++){
            facettes[nf][0] = 4;
            facettes[nf][1] = (p-1)*(nbRegXYCircle-1) + m;
            facettes[nf][2] = (p-1)*(nbRegXYCircle-1) + m+1;
            facettes[nf][3] = p*(nbRegXYCircle-1) + m+1;
            facettes[nf][4] = p*(nbRegXYCircle-1) + m;
            nf++;
        }
        facettes[nf][0] = 4;
        facettes[nf][1] = p*(nbRegXYCircle-1);
        facettes[nf][2] = (p - 1)*(nbRegXYCircle-1) + 1;
        facettes[nf][3] = p*(nbRegXYCircle-1) + 1;
        facettes[nf][4] = (p + 1)*(nbRegXYCircle-1);
        nf++;
    }

    for(int m=1; m<=nbRegXYCircle-2; m++){
        facettes[nf][0] = 3;
        facettes[nf][1] = (nbStepsZ-3)*(nbRegXYCircle-1) + m;
        facettes[nf][2] = (nbStepsZ-3)*(nbRegXYCircle-1) + m+1;
        facettes[nf][3] = (nbStepsZ-2)*(nbRegXYCircle-1) + 1;
        facettes[nf][4] = -1; // Ce facette n'a pas de 4ème point
        nf++;
    }
    facettes[nf][0] = 3;
    facettes[nf][1] = (nbStepsZ-2)*(nbRegXYCircle-1);
    facettes[nf][2] = (nbStepsZ-3)*(nbRegXYCircle-1) + 1;
    facettes[nf][3] = (nbStepsZ-2)*(nbRegXYCircle-1) + 1;
}

void generFacettesTore(int nbStepsZ, int nbRegXYCircle, int **facettes){
    int nf = 0;
    for(int p=1; p<=nbStepsZ-2; p++){
        for(int m=0; m<=nbRegXYCircle-3; m++){
            facettes[nf][0] = 4;
            facettes[nf][1] = (p-1)*(nbRegXYCircle-1) + m;
            facettes[nf][2] = (p-1)*(nbRegXYCircle-1) + m+1;
            facettes[nf][3] = p*(nbRegXYCircle-1) + m+1;
            facettes[nf][4] = p*(nbRegXYCircle-1) + m;
            nf++;
        }
        facettes[nf][0] = 4;
        facettes[nf][1] = p*(nbRegXYCircle-1) - 1; // first time worth 1 * (6-1) - 1
        facettes[nf][2] = (p - 1)*(nbRegXYCircle-1) ;
        facettes[nf][3] = p*(nbRegXYCircle-1);
        facettes[nf][4] = (p + 1)*(nbRegXYCircle-1) - 1;
        nf++;
    }

    for(int m=0; m<=nbRegXYCircle-3; m++){
        facettes[nf][0] = 4;
        facettes[nf][1] = (nbStepsZ-2)*(nbRegXYCircle-1) + m;
        facettes[nf][2] = (nbStepsZ-2)*(nbRegXYCircle-1) + m+1;
        facettes[nf][3] = m+1;
        facettes[nf][4] = m;
        nf++;
    }
    facettes[nf][0] = 4;
    facettes[nf][1] = (nbStepsZ-2)*(nbRegXYCircle-1) + nbRegXYCircle-2;
    facettes[nf][2] = (nbStepsZ-2)*(nbRegXYCircle-1) + 0;
    facettes[nf][3] = 0*(nbRegXYCircle-1);
    facettes[nf][4] = 1*(nbRegXYCircle-1) - 1;
}

/* Dessinage */
void drawFacettes(int nbRegXYCircle, int nbStepsZ, Surface s){
    int n = s.nbFacettes;
    int **facettes = s.facettes;
    Point* pts = s.sommets;
    for(int i=0; i<n; i++){
        draw_shape(pts, facettes[i]);
    }
}

void initSphere() {
    nbStepsZ = 20;
    nbRegXYCircle = 20;
    double *tetaDiscr = ALLOC_MEM(double, nbStepsZ + 1);
    double *phiDiscr = ALLOC_MEM(double, nbRegXYCircle + 1);
    espaceParam(0, M_PI, 0, 2.0 * M_PI, nbStepsZ, nbRegXYCircle, tetaDiscr, phiDiscr);

    s = allocMemS_Surf(nbRegXYCircle, nbStepsZ);

    if (optionFigure == 0) {
        generSommetsTore(nbStepsZ, nbRegXYCircle, tetaDiscr, phiDiscr, s.sommets);
        generFacettesTore(nbStepsZ, nbRegXYCircle, s.facettes);
    } else {
        generSommets(nbStepsZ, nbRegXYCircle, tetaDiscr, phiDiscr, s.sommets);
        generFacettes(nbStepsZ, nbRegXYCircle, s.facettes);
    }

    free(tetaDiscr);
    free(phiDiscr);
    tetaDiscr = phiDiscr = NULL;
}


/* Fonctions d'entrée */
void updateCenter(float x, float y, float z){
    circleCenter.x += x;
    circleCenter.y += y;
    circleCenter.z += z;
}

float posCheck(float val, float defaultVal){
    if(val > 1e-6) return val;
    return defaultVal;
}

void keyboard_press(unsigned char key , int x , int y ){
    int dx = (key == 'd') - (key == 'q'); // La touche appuyée ne peut pas être à la fois d et q, donc dx est soit 1 soit -1
    int dy = (key == 'z') - (key == 's'); // La touche appuyée ne peut pas être à la fois z ou s, donc dy soit 1 soit -1
    int dz = (key == 'a') - (key == 'e');

    float dxy = (key == 'w') - (key == 'x'); // Rotation à gauche ou à droite autour du plan XY
    float dyz = (key == 'v') - (key == 'c'); // Rotation vers l'avant ou vers l'arrière autour du plan YZ
    float dxz = (key == 'n') - (key == 'b'); // Rotation à gauche ou à droite sur le plan XZ

    int stretchX = (key == 'r') - (key == 'f');
    int stretchY = (key == 't') - (key == 'g');
    int stretchZ = (key == 'y') - (key == 'h');

    int changeDonutRad = (key == 'u') - (key == 'j');
    int changeShape = (key == 'p') - (key == 'o');

    trigs = key == 'm' ? !trigs : trigs;
    isRotate = key == 'l' ? !isRotate : isRotate;

    float slX = (float)stretchX, slY = (float)stretchY, slZ = (float)stretchZ;

    // Vérifier que la forme n'est pas trop grande ou trop petite trop rapidement
    slX = posCheck(1+slX*step*0.01, 0.1);
    slY = posCheck(1+slY*step*0.01, 0.1);
    slZ = posCheck(1+slZ*step*0.01, 0.1);

    // Changing the "radiuses" of the superquad actually changes its shape
    if(optionFigure == 3 && (stretchX || stretchY || stretchZ)){
        superQ[0] = posCheck(superQ[0] + slX - 1, 0.01);
        superQ[1] = posCheck(superQ[1] + slY - 1, 0.01);
        superQ[2] = posCheck(superQ[2] + slZ - 1, 0.01);
        initSphere();
    }

    if(optionFigure == 0 && changeDonutRad){
        asp_ratio = posCheck(asp_ratio + (float)changeDonutRad/10, 0.1);
        initSphere();
    }

    if(circleCenter.z > 1.5 && dz > 0.1/(step*20)){
        dz = 0;
    }

    if(changeShape){
        optionFigure = (optionFigure+changeShape + 4)%4;
        initSphere();
    }

    s = transf(s, dx*step, dy*step, dz*step, dxy/10*step, dyz/10*step, dxz/10*step, slX, slY, slZ, circleCenter);

    // S'il on deplace le cercle, on veux que la rotation fonctionne par rapport au centre du cercle, pas du centre de la fenêtre
    updateCenter((double)(dx*step)/10, (double)(dy*step)/10, (double)(dz*step)/10);

    if (key == '+' || key == '-') {
        step += (key == '+') - (key == '-' && step > 1);
        printf("Pas actuelle: %d\n", step);
    }
    glutPostRedisplay();
}

/* Initialize OpenGL Graphics */
void initGL() {
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
   glClearDepth(1.0f);
   glEnable(GL_DEPTH_TEST);
   glDepthFunc(GL_LEQUAL);
   glShadeModel(GL_SMOOTH);
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -7.0f);

    glPointSize(2.0);
    glColor3f(1.0, 1.0, 1.0);

    if(isRotate){
        s = spinAround(s, 0.5, circleCenter);
    }

    drawFacettes(nbRegXYCircle, nbStepsZ, s);
    glutSwapBuffers();
}

void reshape(GLsizei width, GLsizei height) {
   if (height == 0) height = 1;
   GLfloat aspect = (GLfloat)width / (GLfloat)height;

   glViewport(0, 0, width, height);

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}

void timer(int value) {
    glutPostRedisplay();
    glutTimerFunc(10, timer, 0); // Mis à jour chaque 10 millisécondes
}

int main(int argc, char** argv) {
    printf("Liste des commandes:\n") ;

    printf(" Generale:\n");
    printf("  - P: Forme suivante\n");
    printf("  - O: Forme precedente \n");
    printf("  - M: Basculer entre la maille carree et la maille triangulaire\n");
    printf("  - L: Des/activer la rotation\n\n");

    printf(" Deplacements:\n");
    printf("  - Z: Vers le haut\n");
    printf("  - Q: Vers la gauche\n");
    printf("  - S: Vers le bas\n");
    printf("  - D: Vers la droite\n");
    printf("  - A: Dans axe Z vers l'avant\n");
    printf("  - E: Dans axe Z vers l'arriere\n\n");

    printf(" Rotation:\n");
    printf("  - W: Rotation vers la gauche sur le plan XY \n");
    printf("  - X: Rotation vers la droite sur le plan XY\n");
    printf("  - C: Rotation vers l'avant sur le plan YZ \n");
    printf("  - V: Rotation vers l'arriere sur le plan YZ\n");
    printf("  - B: Rotation vers la gauche sur le plan XZ\n");
    printf("  - N: Rotation vers la droite sur le plan XZ\n\n");

    printf(" Mise a l'echelle (ou, pour la superquadrique, modification des exposants de son equation):\n") ;
    printf("  - R : Augmenter l'echelle du polygone sur l'axe X\n") ;
    printf("  - F : Diminuer l'echelle du polygone sur l'axe X\n") ;
    printf("  - T : Augmenter l'echelle des polygones sur l'axe des Y\n") ;
    printf("  - G : Diminuer l'echelle des polygones sur l'axe des Y\n") ;
    printf("  - Y : Augmenter l'echelle des polygones sur l'axe Z\n") ;
    printf("  - H : Diminuer l'echelle du polygone sur l'axe Z\n\n") ;

    printf(" Tore:\n");
    printf("  - U: Augmenter le rapport \n");
    printf("  - J: Diminuer le rapport \n");

    srand(time(NULL));

    step = 1;
    radius = 1.0;
    superQ[0] = superQ[1] = superQ[2] = radius;
    isRotate = 0;

    circleCenter.x = 0.0;
    circleCenter.y = 0.0;
    circleCenter.z = 1.0;
    circleCenter.cH = 1.0;
    optionFigure = 1;
    asp_ratio = 0.5;
    trigs=0;

    initSphere();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(HEIGHT, WIDTH);
    glutInitWindowPosition(250, 250);
    glutCreateWindow(title);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard_press);

    glutTimerFunc(0, timer, 0);  // Start the timer with 0 milliseconds delay

    initGL();
    glutMainLoop();
    return 0;
}

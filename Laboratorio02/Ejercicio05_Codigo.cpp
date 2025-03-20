#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <GL/glut.h>
#include <string.h>

void init(void);
void display(void);
void reshape(int,int);
void apmedio(int, int, int, int);
void ingresoDatos(void);
int px0,py0,px1,py1;

using namespace std;

void ejes2D(void)
{
    int dim = 9;
    glColor3f(0,0,1);
    glLineWidth(2);
    glBegin(GL_LINES);
    glVertex2f(-dim,0);
    glVertex2f(dim,0);
    glVertex2f(0,-dim);
    glVertex2f(0,dim);
    glEnd();

    // x
    glColor3f(0,0,1);
    glRasterPos2f(dim + 0.2, -0.1);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'x');
    // y
    glColor3f(0,0,1);
    glRasterPos2f(0, dim+0.3);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'y');

     // -x
    glColor3f(0,0,1);
    glRasterPos2f(-dim - 0.8, -0.1);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '-');
    glRasterPos2f(-dim - 0.4, -0.1);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'x');
     // -y
    glColor3f(0,0,1);
    glRasterPos2f(-0.32, -dim - 0.4);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '-');
    glRasterPos2f(0, -dim - 0.4);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'y');

    //Flechas

    // Eje X
    glBegin(GL_TRIANGLES);
    glVertex2f(dim,0);
    glVertex2f(dim-0.7,0.27);
    glVertex2f(dim-0.7,-0.27);
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex2f(-dim,0);
    glVertex2f(-dim + 0.7,0.27);
    glVertex2f(-dim + 0.7,-0.27);
    glEnd();

    // Eje Y
    glBegin(GL_TRIANGLES);
    glVertex2f(0,dim);
    glVertex2f(-0.27,dim-0.7);
    glVertex2f(0.27,dim-0.7);
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex2f(0,-dim);
    glVertex2f(-0.27,-dim + 0.7);
    glVertex2f(0.27,-dim + 0.7);
    glEnd();
}

void puntos(int x, int y) {
    glColor3f(0,0,0);
    glPointSize(3);
    glBegin(GL_POINTS);
    for (int i=-y; i<=y; i++) {
        for (int j=-x; j<=x; j++) {
            glVertex2f(j,i);
        }
    }
    glEnd();
}

void apmedio(int x0, int y0, int x1, int y1) {
    int dx, dy, dE, dNE, d, x, y;
    bool b1=false,b2=false;
    int coordenadas_x[100], coordenadas_y[100];
    int n_coordenadas=0;
    dx = x1-x0;
    dy = y1-y0;

    float m = float(dy)/float(dx);

    cout<<"\n Pendiente(m): "<<m<<endl;
    cout<<"\n\n Entrada: ("<<x0<<","<<y0<<"); ("<<x1<<","<<y1<<")"<<endl;

    // REFLEXIONES

    // coordenadas iniciales a la derecha de las coordenadas finales
    if (x0 > x1) {
        int aux_x = x0, aux_y = y0;
        x0 = x1; y0 = y1;
        x1 = aux_x; y1 = aux_y;
    }
    // pendiente negativa
    if (m < 0) {
        y0 *= -1;
        y1 *= -1;
        b1 = true;
    }
    dx = x1-x0;
    dy = y1-y0;
    m = float(dy)/float(dx);

    // pendiente mayor que 1
    if (m > 1) {
        int aux_0 = x0, aux_1 = x1;
        x0 = y0; x1 = y1;
        y0 = aux_0; y1 = aux_1;
        b2 = true;
    }

    // Puntos después de reflexiones

    cout<<" Reflexion: ("<<x0<<","<<y0<<"); ("<<x1<<","<<y1<<")"<<endl;

    dx = x1-x0;
    dy = y1-y0;
    d = 2*dy - dx;
    dE = 2*dy;
    dNE = 2*(dy-dx);
    x = x0;
    y = y0;

    // Recta roja
    glColor3f(1,0,0);
    glBegin(GL_LINES);
    glVertex2f(x0,y0);
    glVertex2f(x1,y1);
    glEnd();

    glBegin(GL_POINTS);
    glVertex2f(x,y);

    coordenadas_x[0] = x;
    coordenadas_y[0] = y;
    n_coordenadas++;

    while (x<x1) {
        if(d<=0){
            d += dE;
            x++;
        } else {
            d += dNE;
            x++;
            y++;
        }

        coordenadas_x[n_coordenadas] = x;
        coordenadas_y[n_coordenadas] = y;
        n_coordenadas++;
        glVertex2f(x,y);
    }

    glEnd();

    // Graficando recta real
    glColor3f(0,1,0);
    glBegin(GL_POINTS);
    for (int i=0; i<n_coordenadas; i++) {
        if (b2 == true) {
            int aux = coordenadas_x[i];
            coordenadas_x[i] = coordenadas_y[i];
            coordenadas_y[i] = aux;
        }
        if (b1 == true) {
            coordenadas_y[i] *= -1;
        }
        glVertex2f(coordenadas_x[i],coordenadas_y[i]);
    }
    glEnd();
}

void ingresoDatos(void){
    cout<<"\n Ingrese el valor de px0= ";
    cin>>px0;
    cout<<"\n Ingrese el valor de py0= ";
    cin>>py0;
    cout<<"\n Ingrese el valor de px1= ";
    cin>>px1;
    cout<<"\n Ingrese el valor de py1= ";
    cin>>py1;
}

int main(int argc, char** argv)
{
    ingresoDatos();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(1000,1000);
    glutCreateWindow(argv[0]);

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}

void init(void)
{
    glClearColor(1.0,1.0,1.0,0.0);
    glShadeModel(GL_FLAT);
}

void display(void)
{
    glPushMatrix();
    glClear(GL_COLOR_BUFFER_BIT);
    puntos(9,9);
    ejes2D();
    glPointSize(8);

    glColor3f(0,1,0);
    glBegin(GL_LINES);
    glVertex2f(px0,py0);
    glVertex2f(px1,py1);
    glEnd();

    glColor3f(1,0,0);
    apmedio(px0,py0,px1,py1);

    glPopMatrix();
    glFlush();
}

void reshape(int w, int h)
{
    glViewport(0,0,(GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10.0,10.0,-10.0,10,-10.0,10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

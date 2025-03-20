#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <GL/glut.h>

using namespace std;

void init(void)
{
    glClearColor(1.0,1.0,1.0,0.0);
    glShadeModel(GL_FLAT);
}

void reshape(int w, int h)
{
    glViewport(0,0,(GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-100.0,100.0,-100.0,100,-10.0,10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void recta_punto_medio(int x0, int y0, int x1, int y1) {
    int dx, dy, dE, dNE, d, x, y;
    bool b1=false,b2=false;
    dx = x1-x0;
    dy = y1-y0;
    float m = float(dy)/float(dx);

    // REFLEXIONES
    // coordenadas iniciales a la derecha de las coordenadas finales
    if (x0 > x1) {
        int aux_x = x0, aux_y = y0;
        x0 = x1; y0 = y1;
        x1 = aux_x; y1 = aux_y;
        dx = x1-x0;
        dy = y1-y0;
        m = float(dy)/float(dx);
    }
    // pendiente negativa
    if (m < 0) {
        y0 *= -1;
        y1 *= -1;
        b1 = true;
        dx = x1-x0;
        dy = y1-y0;
        m = float(dy)/float(dx);
    }

    // pendiente mayor que 1
    if (m > 1) {
        int aux_0 = x0, aux_1 = x1;
        x0 = y0; x1 = y1;
        y0 = aux_0; y1 = aux_1;
        b2 = true;
        dx = x1-x0;
        dy = y1-y0;
    }

    d = 2*dy - dx;
    dE = 2*dy;
    dNE = 2*(dy-dx);
    x = x0;
    y = y0;
    bool esPrimeraCoordenada = true;
    glColor3f(0,0,1);
    glPointSize(3);
    glBegin(GL_POINTS);
    while (x < x1) {
        if (esPrimeraCoordenada == false) {
            if (d <= 0) {
                d += dE;
                x++;
            } else {
                d += dNE;
                x++; y++;
            }
        } else {
            esPrimeraCoordenada=false;
        }
        // Reflexiones
        if (b1 == true && b2 == true) {
            glVertex2f(y, x*-1);
        } else if (b1 == true) {
            glVertex2f(x, y*-1);
        } else if (b2 == true) {
            glVertex2f(y, x);
        } else {
            glVertex2f(x,y);
        }
    }
    glEnd();
}

void triangulo (int L) {

    int x1 = -L/2;
    int y1 = -L*sqrt(3)/6;
    int x2 = 0;
    int y2 = L*sqrt(3)/3;
    int x3 = L/2;
    int y3 = -L*sqrt(3)/6;

    recta_punto_medio(x1,y1,x2,y2);
    recta_punto_medio(x2,y2,x3,y3);
    recta_punto_medio(x3,y3,x1,y1);
}

void circunferencia_punto_medio(int R, int h, int k) {
    int x=0;
    int y=R, d=1-R;
    glColor3f(1,0,0);
    glPointSize(3);
    glBegin(GL_POINTS);
    while (x < y) {
        if (d < 0) {
            d += 2*x + 3;
        } else {
            d += 2*(x-y)+5;
            y--;
        }
        x++;
        glVertex2f(x+h,y+k);
        glVertex2f(-x+h,y+k);
        glVertex2f(-y+h,x+k);
        glVertex2f(-y+h,-x+k);
        glVertex2f(-x+h,-y+k);
        glVertex2f(x+h,-y+k);
        glVertex2f(y+h,-x+k);
        glVertex2f(y+h,x+k);

    }
    glEnd();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Valor de L
    int L = 130;

    float R = (L * sqrt(3))/3;
    float r = (L * (sqrt(3)-1))/4;

    // 1 Circunferencia grande
    circunferencia_punto_medio(R, 0, 0);

    // 3 Circunferencias pequeñas
    circunferencia_punto_medio(r, -r, -r*sqrt(3)/3);
    circunferencia_punto_medio(r, 0, 2*r*sqrt(3)/3);
    circunferencia_punto_medio(r, r, -r*sqrt(3)/3);

    // Triángulo
    triangulo(L);

    glFlush();
}

int main(int argc, char** argv)
{
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

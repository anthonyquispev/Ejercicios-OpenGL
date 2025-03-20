#include <iostream>
#include <math.h>
#include <windows.h>
#include <GL/glut.h>

#include <stdio.h>
#include <stdlib.h>

int L=50;
void init(void);
void display(void);
void reshape(int, int);

void circunferencia_punto_medio(int,int,int);
void circunferencia_punto_medio2(int,int,int);
void circunferencia_punto_medio3(int,int,int);
void circunferencia_punto_medioA(int,int,int);
void circunferencia_punto_medioB(int,int,int);
int px0,py0,px1,py1;

using namespace std;

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(50,50);
    glutCreateWindow("Mi figura");

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
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0,0,1);
    glPointSize(2);

    int L = 95;

    // -- SELECCIONE LA FIGURA --

    // Figura 1 (yin yang)

    circunferencia_punto_medio(L, 0, 0);
    circunferencia_punto_medio(L/8,0,L/2);
    circunferencia_punto_medio(L/8,0,-L/2);
    circunferencia_punto_medio2(L/2, 0, L/2);
    circunferencia_punto_medio3(L/2, 0, -L/2);


    // Figura 2
    /*
    circunferencia_punto_medioA(L/2,L/2,0);
    circunferencia_punto_medioA(L/4,3*L/4,0);
    circunferencia_punto_medioA(L/4,-L/4,0);
    circunferencia_punto_medioB(L/2,-L/2,0);
    circunferencia_punto_medioB(L/4,-3*L/4,0);
    circunferencia_punto_medioB(L/4,L/4,0);
    */

    glFlush();
}

void reshape(int w, int h)
{
    glViewport(0,0,(GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-100.0, 100.0, -100.0, 100, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void circunferencia_punto_medio(int R,int h,int k)
{
    int x=0;
    int y=R,d=1-R;
    glBegin(GL_POINTS);
    while (x<y){
        if (d<0)
            d+=2*x+3;
        else{
            d+=2*(x-y)+5;
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

void circunferencia_punto_medio2(int R,int h,int k)
{
    int x=0;
    int y=R,d=1-R;
    glBegin(GL_POINTS);
    while (x<y){
        if (d<0)
            d+=2*x+3;
        else{
            d+=2*(x-y)+5;
            y--;
            }
            x++;
            glVertex2f(x+h,y+k);
            glVertex2f(x+h,-y+k);
            glVertex2f(y+h,-x+k);
            glVertex2f(y+h,x+k);
        }
    glEnd();
}

void circunferencia_punto_medio3(int R,int h,int k)
{
    int x=0;
    int y=R,d=1-R;
    glBegin(GL_POINTS);
    while (x<y){
        if (d<0)
            d+=2*x+3;
        else{
            d+=2*(x-y)+5;
            y--;
            }
            x++;
            glVertex2f(-x+h,y+k);
            glVertex2f(-y+h,x+k);
            glVertex2f(-y+h,-x+k);
            glVertex2f(-x+h,-y+k);
        }
    glEnd();
}

void circunferencia_punto_medioA(int R,int h,int k)
{
    int x=0;
    int y=R,d=1-R;
    glBegin(GL_POINTS);
    while (x<y){
        if (d<0)
            d+=2*x+3;
        else{
            d+=2*(x-y)+5;
            y--;
            }
            x++;
            glVertex2f(x+h,y+k);
            glVertex2f(-x+h,y+k);
            glVertex2f(-y+h,x+k);
            glVertex2f(y+h,x+k);
        }
    glEnd();
}

void circunferencia_punto_medioB(int R,int h,int k)
{
    int x=0;
    int y=R,d=1-R;
    glBegin(GL_POINTS);
    while (x<y){
        if (d<0)
            d+=2*x+3;
        else{
            d+=2*(x-y)+5;
            y--;
            }
            x++;
            glVertex2f(-y+h,-x+k);
            glVertex2f(-x+h,-y+k);
            glVertex2f(x+h,-y+k);
            glVertex2f(y+h,-x+k);
        }
    glEnd();
}

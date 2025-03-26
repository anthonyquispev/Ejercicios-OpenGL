#include <stdlib.h>
#include<conio.h>
#include<stdio.h>
#include<windows.h>
#include <math.h>
#include <gl/glut.h>
#include<iostream>

using namespace std;

void dibujarEjes(void);
void init(void);
void display(void);
void reshape(int,int);
void keyboard(unsigned char, int, int);
void graficaCurvaBezier(void);
float CoeficienteNewton(int,int);
float factorial(int);
float CurvaBezier(float,int);
void graficaPuntosBezier(void);

float dim=400;

static float pcontrol[100][2];

int indice=0;

int N=7,paso=0;

void control_de_Mouse(int boton, int estado, int x, int y );

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(dim,dim);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Gráfico de una curva de Bezier 2D");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    glutMouseFunc(control_de_Mouse);
    glutMainLoop();
    return 0;
}

void control_de_Mouse(int boton, int estado, int x, int y )
{
     if (boton==GLUT_LEFT_BUTTON && estado==GLUT_DOWN)
    {
        // Valor de x
        x-=200;
        x/=10;

        // Valor de y
        y = (y-200) * (-1);
        y/=10;

        cout<<"Indice:"<<indice<<endl;
        cout<<"Coordenadas"<<endl;
        cout<<"Valor de x:"<<x<<endl;
        cout<<"Valor de y:"<<y<<endl;
        cout<<"---------------"<<endl;

        pcontrol[indice][0] = x;
        pcontrol[indice][1] = y;
        indice++;
        glutPostRedisplay();
    }
}

void dibujarEjes(void)
{
    glBegin(GL_LINES);
    glVertex2f(-20,0);
    glVertex2f(20,0);
    glVertex2f(0,-20);
    glVertex2f(0,20);
    glEnd();
}

void init(void)
{
    glClearColor(0.0,0.5,0.5,.0);
    glShadeModel(GL_FLAT);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    // Salva el estado actual de la matriz
    glPushMatrix();
    glColor3f(1.0,0.0,0.0);
    dibujarEjes();
    glColor3f(0.0,0.0,1.0);
    if (paso==1)
    {
        glPointSize(5);
        graficaPuntosBezier();
        glPointSize(1);
        glColor3f(0.0,1.0,0.0);
        graficaCurvaBezier();
    }
    glPopMatrix();
    // Recupera el estado del matriz
    glFlush();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 'b': paso=1;

        // se grafica la curva de Bezier
        glutPostRedisplay();
        break;
        case 'n': paso=0;

        // No se grafica la curva de Bezier
        glutPostRedisplay();
        break;

        // Borrar puntos
        case 'z':
            if (indice > 0) indice--;
            glutPostRedisplay();
            break;

        case 27: exit(0);
        break;
    }
}

void reshape(int w, int h)
{
    glViewport(0,0,(GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-20.0,20.0,-20.0,20,-1.0,1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void graficaPuntosBezier(void)
{
    float x,y;
    glColor3f(0,0,0);
    glBegin(GL_POINTS);
    for(int i=0;i<indice;i++)
    {
        x=pcontrol[i][0];
        y=pcontrol[i][1];
        glVertex2f(x,y);
    }
    glEnd();
}

void graficaCurvaBezier(void)
{
    float x,y;
    glLineWidth(1.0);
    glBegin(GL_LINE_STRIP);
    for(float u=0.0;u<=1;u+=0.01)
    {
        x=CurvaBezier(u,0);
        y=CurvaBezier(u,1);
        glVertex2f(x,y);
    }
    glEnd();
}

float CoeficienteNewton(int n,int k)
{
    return factorial(n)/(factorial(k)*factorial(n-k));
}

float factorial(int n)
{
    float p=1;
    for(int i=1;i<=n;i++)
        p=p*(float)i;
    return p;
}

float CurvaBezier(float u,int coordenada)
{
    float suma=0.0;
    for(int i=0;i<indice;i++)
    {
        suma=suma+pcontrol[i][coordenada]*CoeficienteNewton(indice-1,i)*pow(u,indice-1-
        i)*pow(1.0-u,i);
    }
    return suma;
}

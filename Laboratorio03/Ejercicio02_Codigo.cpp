#include<iostream>
#include <stdlib.h>
#include<conio.h>
#include<windows.h>
#include <gl/glut.h>
using namespace std;

static GLfloat theta[] = {0.0,0.0,0.0};

static GLint eje = 2;

static GLfloat angulo = 0.005;

void cuadrado(float arista) {
    glColor3f(1,0,0);
    glutWireCube(arista);
}

void dibujarCuadrados() {
    int nCuadrados=25;
    float aristaActual=0.1;
    float incrementoArista=0.1;
    for (int i=0; i<nCuadrados; i++) {
        cuadrado(aristaActual);
        aristaActual+=incrementoArista;
        glRotatef(theta[0],1.0,0.0,0.0);
        glRotatef(theta[1],0.0,1.0,0.0);
        glRotatef(theta[2],0.0,0.0,1.0);
    }
}

void figura(void)
{
    dibujarCuadrados();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // composición de rotaciones

    glRotatef(theta[0],1.0,0.0,0.0);
    glRotatef(theta[1],0.0,1.0,0.0);
    glRotatef(theta[2],0.0,0.0,1.0);

    figura();
    glFlush();
    glutSwapBuffers();
}

void girar_objeto_geometrico ()
{
    theta[eje] += angulo;
    if(theta[eje]>360)
        theta[eje] -= 360.0;
    display();
}

void teclado(unsigned char tecla,int x,int y)
{
    switch(tecla){
        case 'a' : eje = 0; break; //Giro en eje x
        case 's' : eje = 1; break; //Giro en eje y
        case 'd' : eje = 2; break; //Giro en eje z
        case 'f' : exit(0) ; break;
    }
}

void myReshape(int w, int h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if(w <=h)
        glOrtho(-2.0,2.0,-2.0*(GLfloat)h/(GLfloat)w, 2.0*(GLfloat)h/(GLfloat)w, -10.0, 10.0);
    else
        glOrtho(-2.0*(GLfloat)w/(GLfloat)h, 2.0*(GLfloat)w/(GLfloat)h, -2.0,2.0,-10.0,10.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600,600);
    glutCreateWindow("Mi objeto");
    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
    glutIdleFunc(girar_objeto_geometrico);
    glutKeyboardFunc(teclado);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
}

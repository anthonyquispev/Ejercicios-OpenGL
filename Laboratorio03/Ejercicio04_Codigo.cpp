#include<iostream>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
#include <gl/glut.h>
using namespace std;
static GLfloat theta[] = {0.0,0.0,0.0};

// Figura
float x=0,y=0;
float dx=0.002, dy=0.002;
float ladoCuadrado=3.3;
float ladoCubo=0.2;

// Extremo: izquierdo->0 ; derecho->1
bool extremo = 1;

// Desplazamiento
bool desplazamiento = 1;

float angulo=30;
static GLint eje = 2;

void cubo(float lado) {
    glLineWidth(1.4);
    glColor3f(1,0,1);
    glutWireCube(lado);
}

void cuadrado (float lado) {
    glLineWidth(1.4);
    glColor3f(1,0,0);
    glBegin(GL_LINE_LOOP);
        glVertex2f(-lado/2,-lado/2);
        glVertex2f(-lado/2,lado/2);
        glVertex2f(lado/2,lado/2);
        glVertex2f(lado/2,-lado/2);
    glEnd();
}

void figura(float posx, float posy)
{
    // Cuadrado
    cuadrado(ladoCuadrado);

    // Cubo
    glTranslatef(x,0,0);
    glTranslatef(0,y,0);
    cubo(ladoCubo);
}

void inicio(void)
{
    glClearColor(0,0,0,0);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // composicion de rotaciones
    glRotatef(theta[0],1.0,0.0,0.0);
    glRotatef(theta[1],0.0,1.0,0.0);
    glRotatef(theta[2],0.0,0.0,1.0);

    figura(0,1.2);

    glFlush();
    glutSwapBuffers();
}

void girar_objeto_geometrico (void)
{
    if (desplazamiento) {
        // Movimiento horizontal
        if (x>=((ladoCuadrado/2)-(ladoCubo/2)) || x<=-((ladoCuadrado/2)-(ladoCubo/2))) {
            dx=-dx;
        }
        x+=dx;
    } else {
        // Movimiento vertical
        if (y>=((ladoCuadrado/2)-(ladoCubo/2)) || y<=-((ladoCuadrado/2)-(ladoCubo/2))) {
            dy=-dy;
        }
        y+=dy;
    }

    display();
}

void teclado(unsigned char tecla,int x,int y)
{
    switch(tecla){
        case 'q' :
            eje = 0; theta[eje] += angulo;
            break;
        case 'a' :
            eje = 0; theta[eje] -= angulo;
            break;

        case 'w' :
            eje = 1; theta[eje] += angulo;
            break;
        case 's' :
            eje = 1; theta[eje] -= angulo;
            break;

        case 'e' :
            eje = 2; theta[eje] += angulo;
            break;
        case 'd' :
            eje = 2; theta[eje] -= angulo;
            break;

        // Desplazamiento horizontal
        case 'j' :
            desplazamiento=1;
            if(dx>0)dx=-dx;
            break;
        case 'l' :
            desplazamiento=1;
            if(dx<0)dx=-dx;
            break;
        // Desplazamiento vertical
        case 'i' :
            desplazamiento=0;
            if(dy<0)dy=-dy;
            break;
        case 'k' :
            desplazamiento=0;
            if(dy>0)dy=-dy;
            break;

        case 'f' :
            exit(0);
            break;
    }
    if(theta[eje]>360)
        theta[eje] -= 360.0;
    else if(theta[eje]<-360)
        theta[eje] += 360.0;
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
    inicio();
    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
    glutIdleFunc(girar_objeto_geometrico);
    glutKeyboardFunc(teclado);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    return 0;
}

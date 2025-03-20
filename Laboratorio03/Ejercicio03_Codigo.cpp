#include<iostream>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
#include <gl/glut.h>
using namespace std;
static GLfloat theta[] = {0.0,0.0,0.0};

// Péndulo
float anguloInicial = 40;
float angulo=-anguloInicial,dangulo=0.1;
float rango = anguloInicial, dRango=1;

// Extremo: izquierdo->0 ; derecho->1
bool extremo = 1;

float angulo2=30;
static GLint eje = 2;

void cubo(float lado) {
    glLineWidth(1.3);
    glColor3f(1,0,0);
    glutWireCube(lado);
}

void cuerda(float L) {
    glColor3f(1,1,1);
    glLineWidth(1.3);
    glBegin(GL_LINES);
        glVertex3f(0,0,0);
        glVertex3f(0,-L,0);
    glEnd();
}

void esfera(float radio) {
    glColor3f(1,0,0);
    glutSolidSphere(radio,30,30);
}

void pendulo(float posx, float posy)
{
    float longitud_cuerda=1.0, radio_esfera=0.15, lado_cubo=0.2;
    glTranslatef(posx,posy,0);

    // Cubo
    cubo(lado_cubo);

    // Rotación en Z
    glRotatef(angulo,0.0,0.0,1.0);

    // Cuerda
    glDisable(GL_CULL_FACE);

    glDisable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glDisable(GL_LIGHT0);
    glDisable(GL_NORMALIZE);
    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_LIGHTING);


    cuerda(1.2);
    glTranslatef(0,-longitud_cuerda-radio_esfera,0);

    // Esfera
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    esfera(0.15);
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

    // Péndulo
    pendulo(0,1.2);

    glFlush();
    glutSwapBuffers();
}

void girar_objeto_geometrico (void)
{
    if (extremo == 1 && angulo>rango) {
        dangulo=-dangulo;
        rango-=dRango;
        extremo=0;
    }
    if (extremo ==0 && angulo<-rango) {
        dangulo=-dangulo;
        rango-=dRango;
        extremo=1;
    }
    if (rango != 0) {
        angulo=angulo+dangulo;
    }
    display();
}

void teclado(unsigned char tecla,int x,int y)
{
    switch(tecla){
        case 'q' :
            eje = 0; theta[eje] += angulo2;
            break;
        case 'a' :
            eje = 0; theta[eje] -= angulo2;
            break;

        case 'w' :
            eje = 1; theta[eje] += angulo2;
            break;
        case 's' :
            eje = 1; theta[eje] -= angulo2;
            break;

        case 'e' :
            eje = 2; theta[eje] += angulo2;
            break;
        case 'd' :
            eje = 2; theta[eje] -= angulo2;
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

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };
const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500,500);
    glutCreateWindow("Péndulo");
    inicio();
    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
    glutIdleFunc(girar_objeto_geometrico);
    glutKeyboardFunc(teclado);
    glEnable(GL_DEPTH_TEST);

    glClearColor(0,0,0,0);

    // Adic.
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    glutMainLoop();
    return 0;
}

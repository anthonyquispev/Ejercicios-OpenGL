#include<iostream>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
#include <gl/glut.h>

using namespace std;
static GLfloat theta[] = {0.0,0.0,0.0};

float anguloRotacion=30;
static GLint eje = 2;

void inicio(void);
void display(void);
void myReshape(int, int);
void cubo1();
void cubo2();
void cubo3();
void girar_figura_geometrica(void);
void teclado(unsigned char, int, int);

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500,500);
    glutCreateWindow("Mi objeto");
    inicio();
    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
    glutIdleFunc(girar_figura_geometrica);
    glutKeyboardFunc(teclado);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    return 0;
}

void inicio(void)
{
    glClearColor(0,0,0,0);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // composición de rotaciones
    glRotatef(theta[0],1.0,0.0,0.0);
    glRotatef(theta[1],0.0,1.0,0.0);
    glRotatef(theta[2],0.0,0.0,1.0);

    // --SELECCIONAR CUBO--

    //cubo1();
    //cubo2();
    cubo3();

    glFlush();
    glutSwapBuffers();
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

void cubo1()
{
    // LADO FRONTAL
    glBegin(GL_POLYGON);
    glColor3f( 1.0, 0.65, 0.0);
    glVertex3f(  0.5, -0.5, 0.5 );
    glVertex3f(  0.5,  0.5, 0.5 );
    glVertex3f( -0.5,  0.5, 0.5 );
    glVertex3f( -0.5, -0.5, 0.5 );
    glEnd();

    // LADO TRASERO
    glBegin(GL_POLYGON);
    glColor3f(1.0,1.0,1.0);
    glVertex3f(0.5, -0.5, -0.5 );
    glVertex3f(0.5, 0.5, -0.5 );
    glVertex3f(-0.5, 0.5, -0.5 );
    glVertex3f(-0.5, -0.5, -0.5 );
    glEnd();

    // LADO DERECHO
    glBegin(GL_POLYGON);
    glColor3f(  1.0,  1.0,  0.0 );
    glVertex3f( 0.5, -0.5, -0.5 );
    glVertex3f( 0.5,  0.5, -0.5 );
    glVertex3f( 0.5,  0.5,  0.5 );
    glVertex3f( 0.5, -0.5,  0.5 );
    glEnd();

    // LADO IZQUIERDO
    glBegin(GL_POLYGON);
    glColor3f(   0.0,  1.0,  0.0 );
    glVertex3f( -0.5, -0.5,  0.5 );
    glVertex3f( -0.5,  0.5,  0.5 );
    glVertex3f( -0.5,  0.5, -0.5 );
    glVertex3f( -0.5, -0.5, -0.5 );
    glEnd();

    // LADO SUPERIOR
    glBegin(GL_POLYGON);
    glColor3f(   0.0,  0.0,  1.0 );
    glVertex3f(  0.5,  0.5,  0.5 );
    glVertex3f(  0.5,  0.5, -0.5 );
    glVertex3f( -0.5,  0.5, -0.5 );
    glVertex3f( -0.5,  0.5,  0.5 );
    glEnd();

    // LADO INFERIOR
    glBegin(GL_POLYGON);
    glColor3f(   1.0,  0.0,  0.0 );
    glVertex3f(  0.5, -0.5, -0.5 );
    glVertex3f(  0.5, -0.5,  0.5 );
    glVertex3f( -0.5, -0.5,  0.5 );
    glVertex3f( -0.5, -0.5, -0.5 );
    glEnd();
}

void dibujarCubo2(float x, float y, float z) {
    glPushMatrix();
    glTranslatef(x, y, z); // Mueve el cubo a la posición correcta

    // **Dibujar cubo sólido (coloreado)**
    glColor3f(1.0, 0.65, 0.0); // Naranja
    glutSolidCube(0.3);

    // **Dibujar contorno del cubo (wireframe)**
    glColor3f(0, 0, 0); // Negro
    glutWireCube(0.31);

    glPopMatrix();
}

void cubo2()
{
    // Dibujar los 27 cubos
    for (int x = -1; x <= 1; x++) {
        for (int y = -1; y <= 1; y++) {
            for (int z = -1; z <= 1; z++) {
                dibujarCubo2(x * 0.35, y * 0.35, z * 0.35);
            }
        }
    }
}

void cubo3()
{
    //-- LADO FRONTAL --
    glBegin(GL_POLYGON);
    glColor3f( 1.0, 0.65, 0.0);
    glVertex3f(1,-1,1 );
    glVertex3f(1,1,1 );
    glVertex3f(-1,1,1 );
    glVertex3f(-1,-1,1 );
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f( 0.0,  0.0, 0.0 );
    glVertex3f(-0.34,1,1 + 0.1 );
    glVertex3f(-0.34,-1,1 + 0.1 );
    glVertex3f(-0.32,-1,1 + 0.1 );
    glVertex3f(-0.32,1,1 + 0.1 );
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f( 0.0,  0.0, 0.0 );
    glVertex3f(0.32,1,1 + 0.1 );
    glVertex3f(0.32,-1, 1 + 0.1 );
    glVertex3f(0.34,-1,1 + 0.1 );
    glVertex3f(0.34,1,1 + 0.1 );
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f( 0.0,  0.0, 0.0 );
    glVertex3f(-1,0.34,1 + 0.1 );
    glVertex3f(-1,0.32,1 + 0.1 );
    glVertex3f(1,0.32,1 + 0.1 );
    glVertex3f(1,0.34,1 + 0.1 );
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f( 0.0,  0.0, 0.0 );
    glVertex3f(-1,-0.32,1 + 0.1 );
    glVertex3f(-1,-0.34,1 + 0.1 );
    glVertex3f(1,-0.34,1 + 0.1 );
    glVertex3f(1,-0.32,1 + 0.1 );
    glEnd();

    //-- LADO TRASERO --
    glBegin(GL_POLYGON);
    glColor3f(1.0,1.0,1.0);
    glVertex3f(1, -1, -1 );
    glVertex3f(1, 1, -1 );
    glVertex3f(-1, 1, -1 );
    glVertex3f(-1, -1, -1 );
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f( 0.0,  0.0, 0.0 );
    glVertex3f(-0.34,1,-1 - 0.1 );
    glVertex3f(-0.34,-1,-1 - 0.1 );
    glVertex3f(-0.32,-1,-1 - 0.1 );
    glVertex3f(-0.32,1,-1 - 0.1 );
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f( 0.0,  0.0, 0.0 );
    glVertex3f(0.32,1,-1 - 0.1 );
    glVertex3f(0.32,-1,-1 - 0.1 );
    glVertex3f(0.34,-1,-1 - 0.1 );
    glVertex3f(0.34,1,-1 - 0.1 );
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f( 0.0,  0.0, 0.0 );
    glVertex3f(-1,0.34,-1 - 0.1 );
    glVertex3f(-1,0.32,-1 - 0.1 );
    glVertex3f(1,0.32,-1 - 0.1 );
    glVertex3f(1,0.34,-1 - 0.1 );
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f( 0.0,  0.0, 0.0 );
    glVertex3f(-1,-0.32,-1 - 0.1 );
    glVertex3f(-1,-0.34,-1 - 0.1 );
    glVertex3f(1,-0.34,-1 - 0.1 );
    glVertex3f(1,-0.32,-1 - 0.1 );
    glEnd();

    //-- LADO DERECHO --
    glBegin(GL_POLYGON);
    glColor3f(  1.0,  1.0,  0.0 );
    glVertex3f( 1, -1, -1 );
    glVertex3f( 1,  1, -1 );
    glVertex3f( 1,  1,  1 );
    glVertex3f( 1, -1,  1 );
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f( 0.0,  0.0, 0.0 );
    glVertex3f(1 + 0.1,0.34,1 );
    glVertex3f(1 + 0.1,0.32,1 );
    glVertex3f(1 + 0.1,0.32,-1 );
    glVertex3f(1 + 0.1,0.34,-1 );
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f( 0.0,  0.0, 0.0 );
    glVertex3f(1 + 0.1,-0.32,1 );
    glVertex3f(1 + 0.1,-0.34,1 );
    glVertex3f(1 + 0.1,-0.34,-1 );
    glVertex3f(1 + 0.1,-0.32,-1 );
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f( 0.0,  0.0, 0.0 );
    glVertex3f(1 + 0.1,1,0.34 );
    glVertex3f(1 + 0.1,-1,0.34 );
    glVertex3f(1 + 0.1,-1,0.32 );
    glVertex3f(1 + 0.1,1,0.32 );
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f( 0.0,  0.0, 0.0 );
    glVertex3f(1 + 0.1,1,-0.32 );
    glVertex3f(1 + 0.1,-1,-0.32 );
    glVertex3f(1 + 0.1,-1,-0.34 );
    glVertex3f(1 + 0.1,1,-0.34 );
    glEnd();

    //-- LADO IZQUIERDO --
    glBegin(GL_POLYGON);
    glColor3f(   0.0,  1.0,  0.0 );
    glVertex3f( -1, -1,  1 );
    glVertex3f( -1,  1,  1 );
    glVertex3f( -1,  1, -1 );
    glVertex3f( -1, -1, -1 );
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f( 0.0,  0.0, 0.0 );
    glVertex3f(-1 - 0.1,0.34,1 );
    glVertex3f(-1 - 0.1,0.32,1 );
    glVertex3f(-1 - 0.1,0.32,-1 );
    glVertex3f(-1 - 0.1,0.34,-1 );
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f( 0.0,  0.0, 0.0 );
    glVertex3f(-1 - 0.1,-0.32,1 );
    glVertex3f(-1 - 0.1,-0.34,1 );
    glVertex3f(-1 - 0.1,-0.34,-1 );
    glVertex3f(-1 - 0.1,-0.32,-1 );
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f( 0.0,  0.0, 0.0 );
    glVertex3f(-1 - 0.1,1,0.34 );
    glVertex3f(-1 - 0.1,-1,0.34 );
    glVertex3f(-1 - 0.1,-1,0.32 );
    glVertex3f(-1 - 0.1,1,0.32 );
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f( 0.0,  0.0, 0.0 );
    glVertex3f(-1 - 0.1,1,-0.32 );
    glVertex3f(-1 - 0.1,-1,-0.32 );
    glVertex3f(-1 - 0.1,-1,-0.34 );
    glVertex3f(-1 - 0.1,1,-0.34 );
    glEnd();

    //-- LADO SUPERIOR --
    glBegin(GL_POLYGON);
    glColor3f(   0.0,  0.0,  1.0 );
    glVertex3f(  1,  1,  1 );
    glVertex3f(  1,  1, -1 );
    glVertex3f( -1,  1, -1 );
    glVertex3f( -1,  1,  1 );
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f( 0.0,  0.0, 0.0 );
    glVertex3f(-0.32,1 + 0.1 ,1 );
    glVertex3f(-0.34,1 + 0.1 ,1 );
    glVertex3f(-0.34,1 + 0.1 ,-1 );
    glVertex3f(-0.32,1 + 0.1 ,-1 );
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f( 0.0,  0.0, 0.0 );
    glVertex3f(0.34,1 + 0.1 ,1 );
    glVertex3f(0.32,1 + 0.1 ,1 );
    glVertex3f(0.32,1 + 0.1 ,-1 );
    glVertex3f(0.34,1 + 0.1 ,-1 );
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f( 0.0,  0.0, 0.0 );
    glVertex3f(1,1 + 0.1 ,0.34 );
    glVertex3f(1,1 + 0.1 ,0.32 );
    glVertex3f(-1,1 + 0.1 ,0.32 );
    glVertex3f(-1,1 + 0.1 ,0.34 );
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f( 0.0,  0.0, 0.0 );
    glVertex3f(1,1 + 0.1 ,-0.34 );
    glVertex3f(1,1 + 0.1 ,-0.32 );
    glVertex3f(-1,1 + 0.1 ,-0.32 );
    glVertex3f(-1,1 + 0.1 ,-0.34 );
    glEnd();

    //-- LADO INFERIOR --
    glBegin(GL_POLYGON);
    glColor3f(   1.0,  0.0,  0.0 );
    glVertex3f(  1, -1, -1 );
    glVertex3f(  1, -1,  1 );
    glVertex3f( -1, -1,  1 );
    glVertex3f( -1, -1, -1 );
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f( 0.0,  0.0, 0.0 );
    glVertex3f(-0.32,-1 - 0.1 ,1 );
    glVertex3f(-0.34,-1 - 0.1 ,1 );
    glVertex3f(-0.34,-1 - 0.1 ,-1 );
    glVertex3f(-0.32,-1 - 0.1 ,-1 );
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f( 0.0,  0.0, 0.0 );
    glVertex3f(0.34,-1 - 0.1 ,1 );
    glVertex3f(0.32,-1 - 0.1 ,1 );
    glVertex3f(0.32,-1 - 0.1 ,-1 );
    glVertex3f(0.34,-1 - 0.1 ,-1 );
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f( 0.0,  0.0, 0.0 );
    glVertex3f(1,-1 - 0.1 ,0.34 );
    glVertex3f(1,-1 - 0.1 ,0.32 );
    glVertex3f(-1,-1 - 0.1 ,0.32 );
    glVertex3f(-1,-1 - 0.1 ,0.34 );
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f( 0.0,  0.0, 0.0 );
    glVertex3f(1,-1 - 0.1 ,-0.34 );
    glVertex3f(1,-1 - 0.1 ,-0.32 );
    glVertex3f(-1,-1 - 0.1 ,-0.32 );
    glVertex3f(-1,-1 - 0.1 ,-0.34 );
    glEnd();
}

void girar_figura_geometrica (void)
{
    display();
}

void teclado(unsigned char tecla,int x,int y)
{
    switch(tecla)
    {
        case 'q' :
            eje = 0; theta[eje] += anguloRotacion;
            break;
        case 'a' :
            eje = 0; theta[eje] -= anguloRotacion;
            break;

        case 'w' :
            eje = 1; theta[eje] += anguloRotacion;
            break;
        case 's' :
            eje = 1; theta[eje] -= anguloRotacion;
            break;

        case 'e' :
            eje = 2; theta[eje] += anguloRotacion;
            break;
        case 'd' :
            eje = 2; theta[eje] -= anguloRotacion;
            break;

        case 'f' :
            exit(0);
            break;
    }
    // Se resetea el ángulo cuando es mayor a 360 o menor a -360
    if(theta[eje]>360)
        theta[eje] -= 360.0;
    else if(theta[eje]<-360)
        theta[eje] += 360.0;
}

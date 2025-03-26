#include <iostream>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
#include <math.h>
#include <gl/glut.h>

using namespace std;

void ejes(int);
GLdouble angulo=0, incremento_angulo=0.1;
GLdouble const radio=0.5;
GLfloat px0=0,py0=0,pz0=5;
GLfloat px1=0,py1=0,pz1=4;

static GLfloat theta[] = {0.0,0.0,0.0};
float angulo2=30;
static GLint eje = 2;

// Cilindro Alámbrico
float Npara = 9, Ncortes = 9;
float alturaCilindro = 1.5, radioCilindro = 1.0;

void iniciar(void)
{
     glClearColor(0,0,0,0);
     glShadeModel (GL_FLAT);
}

void Mi_Cilindro_Wire(int Npara, int Ncortes)
{
    int nladosPoligono = Ncortes;
    int nAnillos = Npara;
    glColor3f (0.0, 1.0, 0.0);
    glLineWidth(1.3);

    //---ANILLOS---
    // plano XZ
    float ang,x,z;
    float y=0.0;
    float inc_y = float(alturaCilindro / (nAnillos-1));

        glColor3f (0.0, 0.0, 1.0);
        for (int i=0; i<nAnillos; i++){
            glBegin(GL_LINE_LOOP);
            for (ang = 0.0f; ang < 2 * M_PI; ang += 2*M_PI/nladosPoligono)
            {
                x = radioCilindro * sin(ang);
                z = radioCilindro * cos(ang);
                glVertex3f(x,y,z);
            }
            glEnd();
            y+=inc_y;
        }

    //---BARRAS---
    glColor3f (1.0, 1.0, 1.0);
    for (ang = 0.0f; ang < 2 * M_PI; ang += 2*M_PI/Ncortes)
    {
        glBegin(GL_LINES);
        x = radioCilindro * sin(ang);
        z = radioCilindro * cos(ang);
        glVertex3f(x,0.0,z);
        glVertex3f(x,alturaCilindro,z);
        glEnd();
    }
}

void display(void)
{
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
     glPushMatrix();
     glLoadIdentity();

     gluLookAt(px0,py0,pz0,px1,py1,pz1,0,1,0);
     glColor3f (1.0, 0.0, 0.0);
     ejes(2);
     glRotatef(theta[0],1.0,0.0,0.0);
     glRotatef(theta[1],0.0,1.0,0.0);
     glRotatef(theta[2],0.0,0.0,1.0);

    Mi_Cilindro_Wire(Npara,Ncortes);

     glFlush();
     glPopMatrix();
     glutSwapBuffers();
}

void CubeSpin()
{
     display();
}

void rotacamara()
{
    px1=px0+radio*sin(angulo);
    pz1=pz0-radio*cos(angulo);
}

void avanza()
{
    px0=px1;pz0=pz1;
    px1=px0+radio*sin(angulo);
    pz1=pz0-radio*cos(angulo);
}

void retro()
{
    px1=px0;pz1=pz0;
    px0=px0-radio*sin(angulo);
    pz0=pz0+radio*cos(angulo);
}

void rotacamara2(){
    py1=py0+radio*sin(angulo);
    pz1=pz0-radio*cos(angulo);
}

void specialKeyInput(int key, int x, int y){
    if(key == GLUT_KEY_DOWN){
        angulo=angulo+incremento_angulo; rotacamara2();
    }
    if(key == GLUT_KEY_LEFT){
    }
    if(key == GLUT_KEY_RIGHT){
    }
    if(key == GLUT_KEY_UP){
        angulo=angulo-incremento_angulo; rotacamara2();
    }
}

void teclado(unsigned char tecla,int x,int y)
{
    switch(tecla){
        case 'i' : avanza();break;
        case 'm' : retro(); break;
        case 'j' : angulo=angulo+incremento_angulo;rotacamara(); break;
        case 'k' : angulo=angulo-incremento_angulo;rotacamara(); break;
        case 'q' :
            eje = 0; theta[eje] += angulo2; break;
        case 'a' :
            eje = 0; theta[eje] -= angulo2; break;
        case 'w' :
            eje = 1; theta[eje] += angulo2; break;
        case 's' :
            eje = 1; theta[eje] -= angulo2; break;
        case 'e' :
            eje = 2; theta[eje] += angulo2; break;
        case 'd' :
            eje = 2; theta[eje] -= angulo2; break;
        case 'f' : exit(0); break;
    }
        if(theta[eje]>360)
        theta[eje] -= 360.0;
    else if(theta[eje]<-360)
        theta[eje] += 360.0;
}

void ejes(int longitud)
{
     glBegin(GL_LINES);
     glVertex3d(0,0,longitud);
     glVertex3d(0,0,0);
     glEnd();
     glBegin(GL_LINES);
     glVertex3d(0,0,0);
     glVertex3d(0,longitud,0);
     glEnd();
     glBegin(GL_LINES);
     glVertex3d(0,0,0);
     glVertex3d(longitud,0,0);
     glEnd();
}

void myReshape(int w, int h)
{
     glViewport (0, 0, (GLsizei) w, (GLsizei) h);
     glMatrixMode (GL_PROJECTION);
     glLoadIdentity ();
     gluPerspective(60.0, (GLfloat) w/(GLfloat) h,0.1, 30.0);
     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();
}

int main(int argc, char **argv)
{
     glutInit(&argc, argv);
     glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
     glutInitWindowSize(500,500);
     glutCreateWindow("Mi objeto");
     iniciar();
     glutReshapeFunc(myReshape);
     glutDisplayFunc(display);
     glutIdleFunc(CubeSpin);
     glutKeyboardFunc(teclado);
     glutSpecialFunc(specialKeyInput);
     glEnable(GL_DEPTH_TEST);
     glutMainLoop();
     return 0;
}

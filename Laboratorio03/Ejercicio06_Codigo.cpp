#include <iostream>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
#include <math.h>
#include <gl/glut.h>
using namespace std;
static GLfloat theta[] = {0.0,0.0,0.0};
static GLint eje = 2;
float angulo=30;
// Figura
float radioTierra=10.0, radioLuna=9.0;

// Coordenadas Elipse
float puntosElipse_X[500], puntosElipse_Y[500], c_x[1000], c_y[1000];
int n1=0,n2=0;
int indice=0;

bool b=0;
int cont1=0, cont2=2.2;

void luna() {
    glColor3f(1,0,0);
    glutSolidSphere(radioLuna,30,30);
}

void tierra() {
    glColor3f(1,1,0);
    glutSolidSphere(radioTierra,30,30);
}

void orbita() {
    glColor3f(1,1,1);
    glPointSize(2);
    glBegin(GL_POINTS);
    for (int i=0; i<n2; i++) {
        glVertex2f(c_x[i],c_y[i]);
    }
    glEnd();
}

// Puntos por los que debe pasar la luna
void elipse(int rx, int ry, int xc, int yc,float puntosElipse_X[],float puntosElipse_Y[], int &n1) {
    int x, y, p, px, py;
    int ty2 = 2 * pow(ry,2);
    int tx2 = 2 * pow(rx,2);
    x = 0;
    y = ry;

    // REGIÓN 1
    puntosElipse_X[n1] = x+xc;
    puntosElipse_Y[n1] = y+yc;
    n1++;

    p = (int)round(pow(ry,2) - pow(rx,2)*ry + 0.25*pow(rx,2));
    px = 0;
    py = tx2*y;
    while (px < py) {
        x++;
        px += ty2;
        if (p < 0)
            p += pow(ry,2) + px;
        else {
            y--;
            py -= tx2;
            p += pow(ry,2) + px - py;
        }
        puntosElipse_X[n1] = x+xc;
        puntosElipse_Y[n1] = y+yc;
        n1++;
    }

    // REGIÓN 2
    p = (int)round(pow(ry,2)*(x+0.5)*(x+0.5) + pow(rx,2)*(y-1)*(y-1) - pow(rx,2)*pow(ry,2));
    px = 0;
    py = tx2*y;
    while (y > 0) {
        y--;
        py -= tx2;
        if (p > 0)
            p += pow(rx,2) - py;
        else {
            x++;
            px += ty2;
            p += pow(rx,2) + py + px;
        }
        puntosElipse_X[n1] = x+xc;
        puntosElipse_Y[n1] = y+yc;
        n1++;
    }
    glEnd();
}

void obtenerCoordenadas(float c_x[],float c_y[],float puntosElipse_X[],float puntosElipse_Y[],int &n1,int &n2) {
    for (int i=0; i<n1; i++) {
        c_x[n2] = puntosElipse_X[i];
        c_y[n2] = puntosElipse_Y[i];
        n2++;
    }

    for (int i=n1-1; i>=0; i--) {
        c_x[n2] = puntosElipse_X[i];
        c_y[n2] = -puntosElipse_Y[i];
        n2++;
    }

    for (int i=0; i<n1; i++) {
        c_x[n2] = -puntosElipse_X[i];
        c_y[n2] = -puntosElipse_Y[i];
        n2++;
    }

    for (int i=n1-1; i>=0; i--) {
        c_x[n2] = -puntosElipse_X[i];
        c_y[n2] = puntosElipse_Y[i];
        n2++;
    }
}

void figura(void)
{
    // Tierra
    tierra();
    orbita();
    // Luna
    glTranslatef(c_x[indice],c_y[indice],0);
    luna();

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

    // Dibujar figura
    figura();

    glFlush();
    glutSwapBuffers();
}

void girar_objeto_geometrico (void)
{
    if(cont1==cont2) {
        indice++;
        cont1=0;
    } else {
        cont1++;
    }

    if (indice == n2) {
        indice=0;
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
    float num = 100.0;
    if(w <=h)
        glOrtho(-num,num,-num*(GLfloat)h/(GLfloat)w, num*(GLfloat)h/(GLfloat)w, -10.0, 10.0);
    else
        glOrtho(-num*(GLfloat)w/(GLfloat)h, num*(GLfloat)w/(GLfloat)h, -num,num,-10.0,10.0);
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
    glutInitWindowSize(960,550);
    glutCreateWindow("MI objeto");
    elipse(160,70,0,0,puntosElipse_X,puntosElipse_Y,n1);

    obtenerCoordenadas(c_x,c_y,puntosElipse_X,puntosElipse_Y,n1,n2);
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

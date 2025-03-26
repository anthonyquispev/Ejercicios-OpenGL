#include <iostream>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
#include <math.h>
#include <gl/glut.h>

using namespace std;

// Variables para la cámara
GLdouble anguloCam=0, incremento_angulo_cam=0.1;
GLdouble const radio=0.5;
GLfloat px0=0,py0=0,pz0=5;
GLfloat px1=0,py1=0,pz1=4;

// Variables para las rotaciones
static GLfloat theta[] = {0.0,-30.0,0.0};
float anguloRotacionFigura=30;
static GLint eje = 2;

// Variables para el cilindro
float cortesHorizontales = 100, cortesVerticales = 100;
float R1=0.6, R2=0.3;

// Variables para las poleas
float anguloRotacionPolea1 = 0.0;
float anguloRotacionPolea2 = 0.0;
float anguloIncremento = 15.0;// Ángulo para el giro de la polea deseada
// Dependiendo de la tecla presionada (A,S,D o F) una polea va a girar en sentido horario o antihorario,
// y la otra polea girará en el sentido opuesto
// Pero el ángulo de giro siempre es el mismo para la polea indicada (15 grados en este caso),
// y la fórmula se aplica para el ángulo de giro de la otra polea

void iniciar(void);
void display(void);
void myReshape(int, int);
void ejes3D(int, int, int);
void figura(void);
void girar_figura_geometrica(void);
void avanza(void);
void retro(void);
void rotacamara_x_z(void);
void rotacamara_y_z(void);

void teclado(unsigned char, int, int);
void CilindroSolido(float, float, int, int);

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500,500);
    glutCreateWindow("Práctica calificada Computación Visual");
    iniciar();
    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
    glutIdleFunc(girar_figura_geometrica);
    glutKeyboardFunc(teclado);
    glEnable(GL_DEPTH_TEST);

     glutMainLoop();
     return 0;
}

void iniciar(void)
{
     glClearColor(0,0,0,0);
     glShadeModel (GL_FLAT);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glLoadIdentity();
     // La cámara se desplaza sobre el plano xz
    gluLookAt(px0,py0,pz0,px1,py1,pz1,0,1,0);
    glColor3f (1.0, 0.0, 0.0);

    glRotatef(theta[0],1.0,0.0,0.0);
    glRotatef(theta[1],0.0,1.0,0.0);
    glRotatef(theta[2],0.0,0.0,1.0);

    ejes3D(2, 2,2);
     // Figura
    figura();

    glFlush();
    glPopMatrix();
    glutSwapBuffers();
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

void ejes3D(int x, int y, int z)
{
    glLineWidth(1);
    glBegin(GL_LINES);

    // Eje x
    glColor3f(1,0,0);
    glVertex3f(-x,0,0);
    glVertex3f(x,0,0);
    // Eje y
    glColor3f(0,1,0);
    glVertex3f(0,-y,0);
    glVertex3f(0,y,0);
    // Eje z
    glColor3f(0,0,1);
    glVertex3f(0,0,-z);
    glVertex3f(0,0,z);

    glEnd();

    glColor3f(1,0,0);
    glRasterPos2f(0, 0);

    // Escribir x
    glColor3f(1,0,0);
    glRasterPos2f(x + 0.1, 0.0);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'x');

    // Escribir y
    glColor3f(0,1,0);
    glRasterPos2f(0, y+0.1);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'y');

    // Escribir z
    glColor3f(0,0,1);
    glRasterPos3f(0.0,0.0,z+0.1);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'z');

     // Escribir -x
    glColor3f(1,0,0);
    glRasterPos2f(-x - 0.2, 0.0);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '-');
    glRasterPos2f(-x - 0.1, 0.0);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'x');
     // Escribir -y
    glColor3f(0,1,0);
    glRasterPos2f(-0.2, -y - 0.2);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '-');
    glRasterPos2f(0, -y - 0.2);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'y');
     // Escribir -z
    glColor3f(0,0,1);
    glRasterPos3f(0.0, 0.0,-z-0.3);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '-');
    glRasterPos3f(0.0, 0.0, -z-0.1);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'z');

    // DIBUJAR FLECHAS

    // Eje X
    glColor3f(1,0,0);
    glBegin(GL_TRIANGLES);
    glVertex2f(x,0);
    glVertex2f(x-0.2,0.1);
    glVertex2f(x-0.2,-0.1);
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex2f(-x,0);
    glVertex2f(-x + 0.2,0.1);
    glVertex2f(-x + 0.2,-0.1);
    glEnd();

    // Eje Y
    glColor3f(0,1,0);
    glBegin(GL_TRIANGLES);
    glVertex2f(0,y);
    glVertex2f(-0.1,y-0.2);
    glVertex2f(0.1,y-0.2);
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex2f(0,-y);
    glVertex2f(-0.1,-y + 0.2);
    glVertex2f(0.1,-y + 0.2);
    glEnd();

    // Eje Z
    glColor3f(0,0,1);
    glBegin(GL_TRIANGLES);
    glVertex3f(0,0,z);
    glVertex3f(0.0,0.1,z-0.2);
    glVertex3f(0.0,-0.1,z-0.2);
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex3f(0,0,-z);
    glVertex3f(0.0,0.1,-z+0.2);
    glVertex3f(0.0,-0.1,-z+0.2);
    glEnd();
}


void figura(void)
{
    //Construcción de las poleas

    //**Se dibujaron cubos para poder distinguir el giro de las poleas**

    // Polea 1
    glPushMatrix();
    glRotatef(90.0,1.0,0.0,0.0);
    glRotatef(anguloRotacionPolea1,0.0,1.0,0.0);
    CilindroSolido(0.6,R1,cortesHorizontales,cortesVerticales);
    glTranslatef(0.0,0.6,0.0);
    glColor3f (0.0, 0.0, 0.0);
    glutWireCube(0.2);
    glPopMatrix();

    // Polea 2
    glPushMatrix();
    glRotatef(90.0,1.0,0.0,0.0);
    glTranslatef(R1+R2,0.0,0.0);
    glRotatef(anguloRotacionPolea2,0.0,1.0,0.0);
    CilindroSolido(0.6,R2,cortesHorizontales,cortesVerticales);
    glTranslatef(0.0,0.6,0.0);
    glColor3f (0.0, 0.0, 0.0);
    glutWireCube(0.1);
    glPopMatrix();
}

void girar_figura_geometrica()
{
     display();
}

void rotacamara_x_z()
{
    px1=px0+radio*sin(anguloCam);
    pz1=pz0-radio*cos(anguloCam);
}
void avanza()
{
    px0=px1;pz0=pz1;
    px1=px0+radio*sin(anguloCam);
    pz1=pz0-radio*cos(anguloCam);
}
void retro()
{
    px1=px0;pz1=pz0;
    px0=px0-radio*sin(anguloCam);
    pz0=pz0+radio*cos(anguloCam);
}

void rotacamara_y_z(){
    py1=py0+radio*sin(anguloCam);
    pz1=pz0-radio*cos(anguloCam);
}

void teclado(unsigned char tecla,int x,int y)
{
    switch(tecla){
        // ROTACIÓN ALREDEDOR DEL EJE Y

        case 'Q' : // Horaria
            eje = 1; theta[eje] -= anguloRotacionFigura; break;
        case 'W' : //Antihoraria
            eje = 1; theta[eje] += anguloRotacionFigura; break;

        // ROTACIÓN DE LA POLEA 1 (Polea grande)

        case 'A' : //Antihoraria
            anguloRotacionPolea1+=anguloIncremento;
            anguloRotacionPolea2-= (R1/R2)*anguloIncremento;
            break;

        case 'S' : // Horaria
            anguloRotacionPolea1-=anguloIncremento;
            anguloRotacionPolea2+= (R1/R2)*anguloIncremento;
            break;

        // ROTACIÓN DE LA POLEA 2 (Polea pequeña)

        case 'D' : //Antihoraria
            anguloRotacionPolea2 -= anguloIncremento;
            anguloRotacionPolea1 += (R2/R1)*anguloIncremento;
            break;

        case 'F' : // Horaria
            anguloRotacionPolea2 += anguloIncremento;
            anguloRotacionPolea1 -= (R2/R1)*anguloIncremento;
            break;

        // DESPLAZAMIENTO DEL OBSERVADOR
        case 'I' : // Hacia adelante
            avanza(); break;

        case 'M' : // Hacia atrás
            retro(); break;

        case 'J' : // Girar hacia la izquierda
            anguloCam+=incremento_angulo_cam;
            rotacamara_x_z(); break;

        case 'K' : // Girar hacia la derecha
            anguloCam-=incremento_angulo_cam;
            rotacamara_x_z(); break;

        case 'H' : // Girar hacia arriba
            anguloCam-=incremento_angulo_cam;
            rotacamara_y_z(); break;

        case 'N' : // Girar hacia abajo
            anguloCam+=incremento_angulo_cam;
            rotacamara_y_z(); break;

        //Salir
        case 'f' : exit(0); break;
    }

    // Se resetea el ángulo cuando es mayor a 360 o menor a -360
    if(theta[eje]>360)
        theta[eje] -= 360.0;
    else if(theta[eje]<-360)
        theta[eje] += 360.0;

    if (anguloRotacionPolea1>360)
        anguloRotacionPolea1 -= 360;
    else if(anguloRotacionPolea1<-360)
        anguloRotacionPolea1 += 360;

    if (anguloRotacionPolea2>360)
        anguloRotacionPolea2 -= 360;
    else if(anguloRotacionPolea2<-360)
        anguloRotacionPolea2 += 360;
    cout<<"\nAngulo de rotacion Polea 1: "<<anguloRotacionPolea1<<endl;
    cout<<"Angulo de rotacion Polea 2: "<<anguloRotacionPolea2<<endl;
}

void CilindroSolido(float alturaCilindro, float radioCilindro, int cortesHorizontales, int cortesVerticales)
{
    int nladosPoligono = cortesVerticales;
    int nAnillos = cortesHorizontales;

    float ang,x,z;
    float y=0.0;
    float inc_y = float(alturaCilindro / (nAnillos-1));

    // Se dibujan los polígonos que conformarán el cilindro
    for (int i=0; i<nAnillos; i++){

        // Si es la primera o la última circunferencia, entonces solo se dibuja una circunferencia cerrada
        if (i==0 || i==nAnillos-1) {
            glColor3f (0.0, 0.0, 0.0);
            glLineWidth(2.0);
            glBegin(GL_LINE_LOOP);
            for (ang = 0.0f; ang < 2 * M_PI; ang += 2*M_PI/nladosPoligono)
            {
                x = radioCilindro * sin(ang);
                z = radioCilindro * cos(ang);
                glVertex3f(x,y,z);
            }
            glEnd();

        }
        // Dibujar las circunferencias
        else {
            glColor3f (0.0, 0.9, 0.9);
            glBegin(GL_POLYGON);
            for (ang = 0.0f; ang < 2 * M_PI; ang += 2*M_PI/nladosPoligono)
            {
                x = radioCilindro * sin(ang);
                z = radioCilindro * cos(ang);
                glVertex3f(x,y,z);
            }
            glEnd();
        }
        y+=inc_y;
    }
}

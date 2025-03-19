#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <GL/glut.h>

int nCoordenadas = 11;

void ejes2D(void);
void circunferencia2(int,int,float,int);
void init(void);
void display(void);
void reshape(int,int);

void teclado(unsigned char tecla, int x, int y) {
    switch(tecla) {
        case 'w':
            nCoordenadas += 1;
            break;
        case 's':
            if (nCoordenadas>1)
                nCoordenadas -= 1;
            break;
    }
    glutPostRedisplay();
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowSize(1000,1000);
    glutCreateWindow(argv[0]);

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(teclado);
    glutMainLoop();
    return 0;
}

void init(void)
{
    glClearColor(0,0,0,0);
    glShadeModel(GL_FLAT);
}
void reshape(int w, int h)
{
    glViewport(0,0,(GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10.0,10.0,-10.0,10,-10.0,10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void circunferencia2(int h,int k,float radio, int nCoordenadas)
{
    float ang,  x, y;
    for (ang = 0.0f; ang < 2 * M_PI; ang += 2*M_PI/nCoordenadas)
    {
        x = h+radio * cos(ang);
        y = k+radio * sin(ang);
        glVertex2f(x,y);
    }
}

void display(void)
{

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0,0,1);
    glPointSize(5);
    glLineWidth(5);

    // x
    glColor3f(0,0,1);
    glRasterPos2f(8.2, -0.1);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'x');

    // y
    glColor3f(0,0,1);
    glRasterPos2f(0, 8.3);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'y');

     // -x
    glColor3f(0,0,1);
    glRasterPos2f(-8.8, -0.1);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '-');
    glRasterPos2f(-8.4, -0.1);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'x');
     // -y
    glColor3f(0,0,1);
    glRasterPos2f(-0.32, -8.4);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '-');
    glRasterPos2f(0, -8.4);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'y');

    //Flechas
    // Eje X
    glBegin(GL_TRIANGLES);
    glVertex2f(8,0);
    glVertex2f(7.3,0.27);
    glVertex2f(7.3,-0.27);
    glEnd();


    glBegin(GL_TRIANGLES);
    glVertex2f(-8,0);
    glVertex2f(-7.3,0.27);
    glVertex2f(-7.3,-0.27);
    glEnd();

    // Eje Y
    glBegin(GL_TRIANGLES);
    glVertex2f(0,8);
    glVertex2f(-0.27,7.3);
    glVertex2f(0.27,7.3);
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex2f(0,-8);
    glVertex2f(-0.27,-7.3);
    glVertex2f(0.27,-7.3);
    glEnd();

    // Ejes coord.
    ejes2D();

    /////////////////////////
    glPushMatrix();
    glColor3f(1,0,0);
    glPointSize(3);
    glBegin(GL_POINTS);
    circunferencia2(-5,3,2,nCoordenadas);
    glEnd();
    glPopMatrix();

    /////////////////////////
    glPushMatrix();
    glColor3f(1,0,0);
    glLineWidth(1);
    glBegin(GL_LINE_LOOP);
    circunferencia2(0,3,2,nCoordenadas);
    glEnd();
    glPopMatrix();
    ////////////////////////
    glPushMatrix();
    glColor3f(0,1,0);
    glLineWidth(5);
    glBegin(GL_LINE_LOOP);
    circunferencia2(5,3,2,nCoordenadas);
    glEnd();
    glPopMatrix();
    /////////////////////
    glPushMatrix();
    glColor3f(0,0,1);
    glLineWidth(1);
    glBegin(GL_POLYGON);
    circunferencia2(-5,-3,2,nCoordenadas);
    glEnd();
    glPopMatrix();
    ////////////////////
    GLint factor = 4;
    GLushort patron = 0xAAAA;

    glPushMatrix();
    glEnable(GL_LINE_STIPPLE);
    glColor3f(0,0,1);
    glLineWidth(2);
    glLineStipple(factor,patron);
    glBegin(GL_LINE_LOOP);
    circunferencia2(0,-3,2,nCoordenadas);
    glEnd();
    glDisable(GL_LINE_STIPPLE);
    glPopMatrix();
    //////////////////
    glPushMatrix();
    glEnable(GL_LINE_STIPPLE);
    glColor3f(0,0,1);
    glLineWidth(2);
    glLineStipple(factor,patron);
    glBegin(GL_LINE_LOOP);
    circunferencia2(5,-3,2,nCoordenadas);
    glEnd();
    glDisable(GL_LINE_STIPPLE);
    glPopMatrix();
    //////////////////////
    glPushMatrix();
    glColor3f(0,1,0);
    glBegin(GL_POLYGON);
    circunferencia2(5,-3,1.99,nCoordenadas);
    glEnd();
    glPopMatrix();

    glFlush();
}

void ejes2D(void)
{
    glLineWidth(2);
    glBegin(GL_LINES);
    glVertex2f(-8,0);
    glVertex2f(8,0);
    glVertex2f(0,-8);
    glVertex2f(0,8);
    glEnd();
}

#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <GL/glut.h>

void ejes2D(void);
void cardioide1(void);
void cardioide2(void);
void cardioide3(void);
void cardioide4(void);
void disco(void);

void init(void);
void display(void);
void reshape(int,int);

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(1000,1000);
    glutCreateWindow(argv[0]);

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
void reshape(int w, int h)
{
    glViewport(0,0,(GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10.0,10.0,-10.0,10,-10.0,10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0,0,1);
    disco();

    // -- SELECCIONAR FIGURA --

    cardioide1();
    //cardioide2();
    //cardioide3();
    //cardioide4();

    glFlush();
}

void cardioide1(void)
{
    float ang,radio,  x, y;
    int N=150;
    glLineWidth(2);
    glColor3f(0,0,1);
    glBegin(GL_LINE_STRIP);
    for (ang = 0.0f; ang < 2 * M_PI; ang += 2*M_PI/N)
    {
        radio=2 + 4*sin(ang);
        x = radio * cos(ang);
        y = radio * sin(ang);
        glVertex2f(x,y);
    }
    glEnd();
}

void cardioide2(void)
{
    float ang,radio,  x, y;
    int N=150;
    glLineWidth(2);
    glColor3f(0,0,1);
    glBegin(GL_LINE_STRIP);
    for (ang = 0.0f; ang < 2 * M_PI; ang += 2*M_PI/N)
    {
        radio=3*cos(2*ang);
        x = radio * cos(ang);
        y = radio * sin(ang);
        glVertex2f(x,y);
    }
    glEnd();
}

void cardioide3(void)
{
    float ang,radio,  x, y;
    int N=150;
    glLineWidth(2);
    glColor3f(0,0,1);
    glBegin(GL_LINE_STRIP);
    for (ang = 0.0f; ang < 2 * M_PI; ang += 2*M_PI/N)
    {
        radio=3 - 3*sin(ang);
        x = radio * cos(ang);
        y = radio * sin(ang);
        glVertex2f(x,y);
    }
    glEnd();
}

void cardioide4(void)
{
    float ang,radio,  x, y;
    int N=150;
    glLineWidth(2);
    glColor3f(0,0,1);
    glBegin(GL_LINE_STRIP);
    for (ang = 0.0f; ang < 2 * M_PI; ang += 2*M_PI/N)
    {
        radio=ang;
        x = radio * cos(ang);
        y = radio * sin(ang);
        glVertex2f(x,y);
    }
    glEnd();
}

void disco(void) {
    glLineWidth(1);
    glColor3f(1,0,0);
    GLUquadricObj *pt;
    pt = gluNewQuadric();
    gluQuadricDrawStyle(pt,GLU_LINE);
    gluDisk(pt,0,6,20,7);
}

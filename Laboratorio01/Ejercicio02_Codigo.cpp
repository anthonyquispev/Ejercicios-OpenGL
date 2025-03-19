#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <GL/glut.h>
#endif

void init(void);
void display(void);
void reshape(int,int);

int numero_coordenadas = 15;

int main(int argc, char** argv) {

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);

    glutInitWindowSize(500,500);

    glutInitWindowPosition(500, 500);

    glutCreateWindow("Mi objeto");
    init();

    glutDisplayFunc(display);

    glutReshapeFunc(reshape);

    glutMainLoop();

    return 0;
}

void init(void) {
    glClearColor(0.0,0.0,0.0,0.0);

    glShadeModel(GL_FLAT);
}

void display(void) {
    GLfloat ang, radio=8.0f, x, y;
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();

    glColor3f(0,0,1);
    glPointSize(5);
    glLineWidth(5);

    glBegin(GL_POLYGON);
    for (ang = 0.0f; ang < 2 *M_PI; ang += 2*M_PI/numero_coordenadas) {
        x = radio * sin(ang);
        y = radio * cos(ang);
        glVertex2f(x,y);
    }
    glEnd();
    glPopMatrix();
    glFlush();
}

void reshape(int w, int h) {
    glViewport(0,0,(GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10.0,10.0,-10.0,10,-10.0,10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

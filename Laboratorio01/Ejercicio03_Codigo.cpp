#ifdef __APPLE__
#else
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <GL/glut.h>
#endif

int numero_coordenadas = 5;
GLint factor = 3;

GLushort patron = 0x000F;

void init(void) {
    glEnable(GL_LINE_STIPPLE);
    glShadeModel(GL_FLAT);
}


void display(void) {
    GLfloat ang, radio=8.0f, x, y;
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();

    glLineStipple(factor,patron);
    glBegin(GL_LINE_LOOP);

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

int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(250,250);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Mi objeto");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutMainLoop();

    return 0;
}

#ifdef __APPLE__
#else
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <GL/glut.h>
#endif

int numero_coordenadas = 5;

void init(void) {
    glShadeModel(GL_FLAT);
}
void ejes2D(void){
    glBegin(GL_LINES);
    glVertex2f(-8,0);
    glVertex2f(8,0);
    glVertex2f(0,8);
    glVertex2f(0,-8);
    glEnd();
}

void display(void) {
    GLfloat ang, radio=8.0f, x, y;
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    ejes2D();
    glColor3f(0,1,1);
    glPointSize(10);

    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3f(1.0,0.0,0.0);
    glVertex2f(40.0,0.0);
    glVertex2f(-40.0,0.0);

    glColor3f(0.0,1.0,0.0);
    glVertex2f(0.0,40.0);
    glVertex2f(0.0,-40.0);

    glEnd();

    glPointSize(5);
    glBegin(GL_LINE);

    for (ang = 0.0f; ang < 2 *M_PI; ang += 2*M_PI/numero_coordenadas) {
        x = radio * sin(ang);
        y = radio * cos(ang);
        glVertex2f(x,y);
    }
    glEnd();
    glFlush();
}

void reshape(int w, int h) {
    glViewport(0,0,(GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION_MATRIX);
    glLoadIdentity();

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

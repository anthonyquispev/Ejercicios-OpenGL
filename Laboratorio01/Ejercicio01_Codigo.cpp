#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <GL/glut.h>

void init(void);
void display(void);
void reshape(int,int);
void circunferencia(int,int,int,int);
void discoHueco(void);

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(700,700);
    glutInitWindowPosition(350,0);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}

void init(void) {
    glClearColor(1.0,1.0,1.0,0.0);
    glShadeModel(GL_FLAT);
}

void reshape(int w, int h) {
    glViewport(0,0,(GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10.0,10.0,-10.0,10,-10.0,10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void circunferencia (int h, int k, int radio, int nCoordenadas) {
    float ang, x, y;
    glColor3f(0,0,1);
    glPointSize(5);
    glBegin(GL_POINTS);
    for (ang = 0.0f; ang < 2 * M_PI; ang += 2*M_PI/nCoordenadas)
    {
        x = h+radio * cos(ang);
        y = k+radio * sin(ang);
        glVertex2f(x,y);
    }
    glEnd();
}

void discoHueco () {
    GLUquadricObj *pt;
    pt = gluNewQuadric();
    gluQuadricDrawStyle(pt,GLU_LINE);
    glColor3f(0,1,0);

    gluPartialDisk(pt, 5, 8, 15, 4,0,270);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    // Disco
    discoHueco();

    glFlush();
}

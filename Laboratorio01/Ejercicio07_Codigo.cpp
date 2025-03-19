#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <GL/glut.h>

void circunferencia(int,int,int);
void mallaCP();
void cardiode(void);
void init(void);
void display(void);
void reshape(int,int);

void mallaCP(void)
{
    float x,y;

    // Círculos concéntricos
    for(int radio=1;radio<=8;radio++)
    {
        glBegin(GL_LINE_LOOP);
        circunferencia(0,0,radio);
        glEnd();
    }

    // Líneas radiales
    glBegin(GL_LINES);
        for (float ang = 0.0f; ang < 4 * M_PI; ang += 2*M_PI/20)
            {
                x = 8 * cos(ang);
                y = 8 * sin(ang);
                glVertex2f(0,0);
                glVertex2f(x,y);
            }
    glEnd();
}

void cardioide(void)
{
    float ang,radio,  x, y;
    int N=200;
    glBegin(GL_LINE_LOOP);
        for (ang = 0.0f; ang < 4 * M_PI; ang += 2*M_PI/N)
            {
                radio=7*cos(2*ang);
                x = radio * cos(ang);
                y = radio * sin(ang);
                glVertex2f(x,y);
            }
    glEnd();
}

void circunferencia(int h,int k,int radio)
{
    float ang,  x, y;
    int N=50;
    for (ang = 0.0f; ang <= 2 * M_PI; ang += 2*M_PI/N)
    {
        x = h+radio * cos(ang);
        y = k+radio * sin(ang);
        glVertex2f(x,y);
    }
}

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

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0,0,1);
    glLineWidth(3);
    mallaCP();
    glColor3f(1,0,0);
    cardioide();

    glFlush();
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

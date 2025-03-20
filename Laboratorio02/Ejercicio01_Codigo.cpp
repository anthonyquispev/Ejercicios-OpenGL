#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <GL/glut.h>
void init(void);
void display(void);
void reshape(int,int);

void elipse (int rx, int ry, int xc, int yc) {
    int x, y, p, px, py;
    int ty2 = 2 * pow(ry,2);
    int tx2 = 2 * pow(rx,2);
    x = 0;
    y = ry;

    glPointSize(4);
    glColor3f(1,0,0);
    glBegin(GL_POINTS);

    // REGIÓN 1
    glVertex2f(x+xc,y+yc);
    glVertex2f(-x+xc,y+yc);
    glVertex2f(-x+xc,-y+yc);
    glVertex2f(x+xc,-y+yc);

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
        glVertex2f(x+xc,y+yc);
        glVertex2f(-x+xc,y+yc);
        glVertex2f(-x+xc,-y+yc);
        glVertex2f(x+xc,-y+yc);
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
        glVertex2f(x+xc,y+yc);
        glVertex2f(-x+xc,y+yc);
        glVertex2f(-x+xc,-y+yc);
        glVertex2f(x+xc,-y+yc);
    }
    glEnd();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(900,900);
    glutInitWindowPosition(250,0);
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

    // Elipse
    elipse(40,25,0,0);

    glFlush();
}

void reshape(int w, int h)
{
    glViewport(0,0,(GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-50.0,50.0,-50.0,50,-10.0,10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

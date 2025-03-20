#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <GL/glut.h>

void init(void);
void display(void);
void reshape(int,int);
void cuadrado(void);
void poligono(int, int);

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(1000,1000);
    glutInitWindowPosition(100,100);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}

void init(void){
    glClearColor(1.0,1.0,1.0,0.0);
    glShadeModel(GL_FLAT);
    glPointSize(5);
}

void display(void){
    GLfloat ang, radio = 8.0f, x, y;
    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();
    glColor3f (0.0, 0.0, 1.0);
    cuadrado();
    poligono(5,6);
    glPopMatrix();
    glFlush();
}

void reshape(int w, int h){
    glViewport(0,0,(GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10.0,10.0,-10.0,10,-10.0,10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void cuadrado(void){
    glBegin(GL_LINE_LOOP);
    glVertex2f(-8,-8);
    glVertex2f(-8,8);
    glVertex2f(8,8);
    glVertex2f(8,-8);
    glEnd();
}

void poligono(int h, int radio){
    int n = h, i=0,n1=3;
    float x[h], y[h], angulo;
    for(angulo = 0.0f; angulo < 2 * M_PI; angulo += 2*M_PI/n){
        x[i] = radio * sin(angulo);
        y[i]= radio * cos(angulo);
        i++;
    }
    glBegin(GL_LINE_LOOP);
    for(i=0;i<n;i++){
        glVertex2f(x[i],y[i]);
        i++;
    }
    for(i=1;i<n;i++){
        glVertex2f(x[i],y[i]);
        i++;
    }
    glEnd();
}

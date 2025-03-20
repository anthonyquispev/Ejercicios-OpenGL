#include<stdlib.h>
#include<conio.h>
#include<windows.h>
#include <gl/glut.h>

// Figura
float x=0,y=0;
float dx=0.08, dy=0.08;
float ladoCuadrado=170;
float radioCircunferencia=8;

int ladoPintado = 0;
// 1->izquierda ; 2->arriba ; 3->derecha ; 4->abajo

static GLfloat colorLadoPintado[] = {1.0,1.0,1.0};
float grosorLineaNormal=2.5, grosorLineaPintada = 7.0;

// Desplazamiento
bool desplazamiento = 1;

void circunferencia_punto_medio(int R, int h, int k) {
    int x=0;
    int y=R, d=1-R;
    glColor3f(1,0,0);
    glPointSize(2.5);
    glBegin(GL_POINTS);
    while (x < y) {
        if (d < 0) {
            d += 2*x + 3;
        } else {
            d += 2*(x-y)+5;
            y--;
        }
        x++;
        glVertex2f(x+h,y+k);
        glVertex2f(-x+h,y+k);
        glVertex2f(-y+h,x+k);
        glVertex2f(-y+h,-x+k);
        glVertex2f(-x+h,-y+k);
        glVertex2f(x+h,-y+k);
        glVertex2f(y+h,-x+k);
        glVertex2f(y+h,x+k);
    }
    glEnd();
}

void cuadrado(float lado, int ladoPintado, float colorLadoPintado[]) {

    if (ladoPintado == 1) {
        glLineWidth(grosorLineaPintada);
        glColor3f(colorLadoPintado[0],colorLadoPintado[1],colorLadoPintado[2]);
        glBegin(GL_LINES);
        glVertex2f(-lado/2,-lado/2);
        glVertex2f(-lado/2,lado/2);
        glEnd();

        glLineWidth(grosorLineaNormal);
        glColor3f(1,0,1);
        glBegin(GL_LINES);
        glVertex2f(-lado/2,lado/2);
        glVertex2f(lado/2,lado/2);
        glVertex2f(lado/2,lado/2);
        glVertex2f(lado/2,-lado/2);
        glVertex2f(lado/2,-lado/2);
        glVertex2f(-lado/2,-lado/2);
        glEnd();
    } else if (ladoPintado == 2) {
        glLineWidth(grosorLineaNormal);
        glColor3f(1,0,1);
        glBegin(GL_LINES);
        glVertex2f(-lado/2,-lado/2);
        glVertex2f(-lado/2,lado/2);
        glEnd();

        glLineWidth(grosorLineaPintada);
        glColor3f(colorLadoPintado[0],colorLadoPintado[1],colorLadoPintado[2]);
        glBegin(GL_LINES);
        glVertex2f(-lado/2,lado/2);
        glVertex2f(lado/2,lado/2);
        glEnd();

        glLineWidth(grosorLineaNormal);
        glColor3f(1,0,1);
        glBegin(GL_LINES);
        glVertex2f(lado/2,lado/2);
        glVertex2f(lado/2,-lado/2);
        glVertex2f(lado/2,-lado/2);
        glVertex2f(-lado/2,-lado/2);
        glEnd();
    } else if (ladoPintado == 3) {
        glLineWidth(grosorLineaNormal);
        glColor3f(1,0,1);
        glBegin(GL_LINES);
        glVertex2f(-lado/2,-lado/2);
        glVertex2f(-lado/2,lado/2);
        glVertex2f(-lado/2,lado/2);
        glVertex2f(lado/2,lado/2);
        glEnd();

        glLineWidth(grosorLineaPintada);
        glColor3f(colorLadoPintado[0],colorLadoPintado[1],colorLadoPintado[2]);
        glBegin(GL_LINES);
        glVertex2f(lado/2,lado/2);
        glVertex2f(lado/2,-lado/2);
        glEnd();

        glLineWidth(grosorLineaNormal);
        glColor3f(1,0,1);
        glBegin(GL_LINES);
        glVertex2f(lado/2,-lado/2);
        glVertex2f(-lado/2,-lado/2);
        glEnd();
    } else if (ladoPintado == 4) {
        glLineWidth(grosorLineaNormal);
        glColor3f(1,0,1);
        glBegin(GL_LINES);
        glVertex2f(-lado/2,-lado/2);
        glVertex2f(-lado/2,lado/2);
        glVertex2f(-lado/2,lado/2);
        glVertex2f(lado/2,lado/2);
        glVertex2f(lado/2,lado/2);
        glVertex2f(lado/2,-lado/2);
        glEnd();

        glLineWidth(grosorLineaPintada);
        glColor3f(colorLadoPintado[0],colorLadoPintado[1],colorLadoPintado[2]);
        glBegin(GL_LINES);
        glVertex2f(lado/2,-lado/2);
        glVertex2f(-lado/2,-lado/2);
        glEnd();

    } else {
        glLineWidth(grosorLineaNormal);
        glColor3f(1,0,1);
        glBegin(GL_LINES);
        glVertex2f(-lado/2,-lado/2);
        glVertex2f(-lado/2,lado/2);
        glVertex2f(-lado/2,lado/2);
        glVertex2f(lado/2,lado/2);
        glVertex2f(lado/2,lado/2);
        glVertex2f(lado/2,-lado/2);
        glVertex2f(lado/2,-lado/2);
        glVertex2f(-lado/2,-lado/2);
        glEnd();
    }
}

void figura(void)
{
    // Cuadrado
    cuadrado(ladoCuadrado,ladoPintado,colorLadoPintado);
    // Circunferencia
    circunferencia_punto_medio(radioCircunferencia,x,y);
}

void inicio(void)
{
    glClearColor(0,0,0,0);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Dibujar figura
    figura();

    glFlush();
    glutSwapBuffers();
}

void girar_objeto_geometrico (void)
{
    if (desplazamiento) {
        // Movimiento horizontal
        if (x<=-((ladoCuadrado/2)-radioCircunferencia)) {
            dx=-dx;
            ladoPintado = 1;
        } else if (x>=((ladoCuadrado/2)-radioCircunferencia)) {
            dx=-dx;
            ladoPintado = 3;
        }
        x+=dx;
    } else {
        // Movimiento vertical
        if (y>=((ladoCuadrado/2)-radioCircunferencia)) {
            dy=-dy;
            ladoPintado = 2;
        } else if (y<=-((ladoCuadrado/2)-radioCircunferencia)) {
            dy=-dy;
            ladoPintado = 4;
        }
        y+=dy;
    }
    display();
}

void teclado(unsigned char tecla,int x,int y)
{
    switch(tecla){
        // Desplazamiento horizontal
        case 'j' : //izquierda
            desplazamiento=1;
            if(dx>0)dx=-dx;
            break;
        case 'l' : //derecha
            desplazamiento=1;
            if(dx<0)dx=-dx;
            break;
        // Desplazamiento vertical
        case 'i' : //arriba
            desplazamiento=0;
            if(dy<0)dy=-dy;
            break;
        case 'k' : //abajo
            desplazamiento=0;
            if(dy>0)dy=-dy;
            break;

        case 'f' :
            exit(0);
            break;
    }
}

void myReshape(int w, int h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float num = 100.0;
    if(w <=h)
        glOrtho(-num,num,-num*(GLfloat)h/(GLfloat)w, num*(GLfloat)h/(GLfloat)w, -10.0, 10.0);
    else
        glOrtho(-num*(GLfloat)w/(GLfloat)h, num*(GLfloat)w/(GLfloat)h, -num,num,-10.0,10.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600,600);
    glutCreateWindow("Mi objeto");
    inicio();
    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
    glutIdleFunc(girar_objeto_geometrico);
    glutKeyboardFunc(teclado);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    return 0;
}

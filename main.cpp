#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <string>

typedef std::string string;


void display();
void timer(int);
void reshape(int, int);

int scale = 50;



float gravityACC = 9.81;


int WIDTH = 400;
int HEIGHT = 400;

void init()
{
    //glClearColor(0.0,1.0,0.0,1.0);
   
}


int main(int argc, char** argv)
{   
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);

    glutInitWindowSize(400, 400);
    glutInitWindowPosition(100, 100);

    glutCreateWindow("INK ENGINE");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0,timer,0);
    

    init();
    glutMainLoop();
    return 0;
}

void reshape(int width, int height) {
    const float ar_origin = (float) WIDTH / (float) HEIGHT;
    const float ar_new = (float) width / (float) height;

    float scale_w = (float) width / (float) WIDTH;
    float scale_h = (float) height / (float) HEIGHT;
    if (ar_new > ar_origin) {
        scale_w = scale_h;
    } else {
        scale_h = scale_w;
    }

    float margin_x = (width - WIDTH * scale_w) / 2;
    float margin_y = (height - HEIGHT * scale_h) / 2;

    glViewport(margin_x, margin_y, WIDTH * scale_w, HEIGHT * scale_h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, WIDTH / ar_origin, 0, HEIGHT / ar_origin, 0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}

void triangle(int x, int y, int size)
{  
    glBegin(GL_POLYGON);
        //         x   y
        glVertex2d(x,y);  //start point
        glVertex2d(x+size,y); // far left
        glVertex2d(x,y+size); // top point
    glEnd();
}

void ribbon(int x, int y, int size)
{
    glBegin(GL_POLYGON);
        //         x   y
        glVertex2d(x,y);  //start point bottom left
        glVertex2d(x+size,y); // far left
        glVertex2d(x,y+size); // top point
        glVertex2d(x+size,y+size); //opposite to start
    glEnd();
}

void square(int x, int y, int size)
{
    triangle(x,y,size);
    triangle(x+size,y+size,-size);
}


void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    glutSwapBuffers();
}

void timer(int)
{   
    glutPostRedisplay();
    glutTimerFunc(1000/60, timer, 0);
}
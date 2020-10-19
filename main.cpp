#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <string>
#include <iostream>

#include "player.h"
#include "world.h"

typedef std::string string;

using namespace InkEngine;

player myPlayer;
world myWorld;


void display();
void timer(int);
void reshape(int, int);
void keyboardListener(unsigned char key, int x, int y);

int scale = 10000;  //resolution of the sim
int boundX = 1*scale;
int boundY = 1*scale;


float gravityACC = 9.81;


int HEIGHT;

int WIDTH;

void init()
{
   // glClearColor(0.0,1.0,0.0,1.0);
   
}



int main(int argc, char** argv)
{   
    glutInit(&argc, argv);

    HEIGHT = glutGet(GLUT_SCREEN_HEIGHT);
    WIDTH = glutGet(GLUT_SCREEN_WIDTH);

    glutInitDisplayMode(GLUT_RGB);
 
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(100, 100);

    glutCreateWindow("INK ENGINE");

    

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0,timer,0);
    glutKeyboardFunc(keyboardListener);
    
    init();
    glutMainLoop();
    return 0;
}

void reshape(int width, int height) {
   glViewport(0,0,width, height);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluOrtho2D(0,boundX,0,boundY);
   glMatrixMode(GL_MODELVIEW);
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

    //render objects

    square(myPlayer.xpos,myPlayer.ypos,myPlayer.mass*(scale/1000)); //rendering the player , player one

    glutSwapBuffers();
}


void keyboardListener(unsigned char key, int x, int y)
{   
    switch (key){
		case 'w': //jump
            if(myPlayer.ypos == 0)
            {
                myPlayer.Vvelocity += 10.2*(scale/1000);
            }
			    
			break;

		case 's': 
			if(myPlayer.ypos >= 0)
            {
                myPlayer.Vvelocity -= 0.2*(scale/1000);
            }   
		break;
        
        case 'a':
            if(myPlayer.xpos >= 0 && myPlayer.ypos == 0)
            {
                myPlayer.Hvelocity -= 0.25*(scale/1000);
            } 
        break;
        
        case 'd':
            if(myPlayer.xpos < boundX-myPlayer.mass && myPlayer.ypos == 0)
            {
                myPlayer.Hvelocity += 0.25*(scale/1000);
            } 
        break;

		default:
         break;
	}
   glutPostRedisplay();
}

float playerSpeed()
{
    //speed is a non vector so only use for friction ; use Hvelocity for direction
    if(myPlayer.Hvelocity > 0)
    {
        return myPlayer.Hvelocity;
    }
    else
    {
        return myPlayer.Hvelocity * -1;  //speed has no direction
    }
    
}

void timer(int)
{   

    

    //player physics
    if(myPlayer.ypos > 0)
    {
        myPlayer.Vvelocity += myWorld.gravity/100*(scale/1000);  //gravity
    }

    std::cout << myPlayer.Hvelocity << std::endl;
    
   
    //acceleration.
    myPlayer.ypos += myPlayer.Vvelocity;
    myPlayer.xpos += myPlayer.Hvelocity;

    if(myPlayer.ypos == 0 && myPlayer.Hvelocity > 0)
    {
        myPlayer.Hvelocity += myWorld.floorFriction/60*playerSpeed()*(scale/10000);
    }
    else if(myPlayer.ypos == 0 && myPlayer.Hvelocity < 0)
    {
        myPlayer.Hvelocity -= myWorld.floorFriction/60*playerSpeed()*(scale/10000);
    }

    //boundary definition
    if(myPlayer.ypos < 0)
    {
        myPlayer.ypos = 0;
        myPlayer.Vvelocity = 0;
    }

    if(myPlayer.xpos > boundX-myPlayer.mass)
    {
        myPlayer.xpos = boundY-myPlayer.mass;
        myPlayer.Hvelocity = 0;
    }

    if(myPlayer.xpos < 0)
    {
        myPlayer.xpos = 0;
        myPlayer.Hvelocity = 0;
    }

    glutPostRedisplay();
    glutTimerFunc(1000/60, timer, 0);
}
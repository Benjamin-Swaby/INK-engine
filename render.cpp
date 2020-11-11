#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <string>
#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>

#include "player.h"
#include "world.h"
#include "render.h"
#include "objects.h"


typedef std::thread thread;
typedef std::string string;
typedef std::mutex mutex;

using namespace InkEngine;


player myPlayer;
world myWorld;
int objCount;
objects worldOB[64]; //maximum 64 entities
mutex mtx;


void display();
void timer(int);
void reshape(int, int);
void keyboardListener(unsigned char key, int x, int y);
void Tick();

const int scale = 10000;  //resolution of the sim
const int boundX = 1*scale;
const int boundY = 1*scale;


float gravityACC = 9.81;


int HEIGHT;

int WIDTH;

void init()
{
   // glClearColor(0.0,1.0,0.0,1.0);
   
}



int render::start(int argc, char** argv)
{       
    glutInit(&argc, argv);
    HEIGHT = glutGet(GLUT_SCREEN_HEIGHT);
    WIDTH = glutGet(GLUT_SCREEN_WIDTH);

    glutInitDisplayMode(GLUT_RGB);
    
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(100, 100);

    glutCreateWindow("INK ENGINE");
     //internal referance to the class.

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0,timer,0);
    glutKeyboardFunc(keyboardListener);

    //set the length of the object array
    objCount = length;

    //load objects into the local variable
    for(int i = 0; i < objCount; i++)
    {
        worldOB[i] = worldOBJ[i];
    }

    //make a new thead to handle all the player phyisics independant of time
    thread t2(Tick);  //DO NOT DELETE THE FUNCTION UNLESS A CUSTOM IMPLEMENTATION CAN BE WRITTEN!!!
    

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



void renderObjs(objects * worldOBJ, int length)
{   
    for(int i = 0; i < length; i++)
    {   
        
        float xpos = worldOBJ[i].xpos;
        float ypos = worldOBJ[i].ypos;
        float mass = worldOBJ[i].mass;

        float* test = &ypos;

        std::cout << "on render" << *test << std::endl;
        square(xpos,ypos,mass*(scale/1000));
       
    }
}


void display()
{   
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    square(myPlayer.xpos,myPlayer.ypos,myPlayer.mass*(scale/1000)); //rendering the player , player one
    //renderObjs(worldOB, objCount);
    for(int i = 0; i < objCount; i++)
    {   
        
        float xpos = worldOB[i].xpos;
        float ypos = worldOB[i].ypos;
        float mass = worldOB[i].mass;

        std::cout << "on render" << worldOB[1].ypos << std::endl;
        square(xpos,ypos,mass*(scale/1000));
       
    }

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


float OBJspeed(objects ob)
{
    if(ob.Hvelocity > 0)
    {
        return ob.Hvelocity;
    }
    else
    {
        return ob.Hvelocity * -1; //speed is a scalar
    }
}


void Tick()
{   

    int tickCount = 0;

    while(true)
    {   

        //player physics
        std::this_thread::sleep_for (std::chrono::milliseconds(16));
           //player physics
        if(myPlayer.ypos > 0)
        {
            myPlayer.Vvelocity += myWorld.gravity/100*(scale/1000);  //gravity
        }
        
    
        //acceleration.
        myPlayer.ypos += myPlayer.Vvelocity;
        myPlayer.xpos += myPlayer.Hvelocity;

        //friction
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
            myPlayer.ypos = 0;   //floor definition
            myPlayer.Vvelocity = 0;
        }

        if(myPlayer.xpos > boundX-myPlayer.mass*(scale/1000))
        {
            myPlayer.xpos = boundX-myPlayer.mass*(scale/1000);
            if(myWorld.bounceWalls)
            {
                myPlayer.Hvelocity = -myPlayer.Hvelocity+0.5*(myPlayer.Hvelocity); //x bounce
            }
        }

        if(myPlayer.xpos < 0)
        {
            myPlayer.xpos = 0;
        
            if(myWorld.bounceWalls)
            {    
                 myPlayer.Hvelocity = -myPlayer.Hvelocity+0.5*(myPlayer.Hvelocity); //x bounce
            }
        }


        //object physics
        //
        
        for(int i = 0; i++; i < 64)
        {
              
            //vertical movement
            if(worldOB[i].ypos > 0)
            {
                worldOB[i].Vvelocity += myWorld.gravity/100*(scale);
            }

            if(worldOB[i].ypos < 0)
            {
                worldOB[i].ypos = 0;
                worldOB[i].Vvelocity = 0;
            }   
            
            //horizontal movement
            //
            //friction
            if(worldOB[i].ypos == 0 && worldOB[i].Hvelocity > 0)
            {
                worldOB[i].Hvelocity += myWorld.floorFriction/60*OBJspeed(worldOB[i])*(scale/1000);
            }
            else if (worldOB[i].ypos == 0 && worldOB[i].Hvelocity < 0)
            {
                 worldOB[i].Hvelocity -= myWorld.floorFriction/60*OBJspeed(worldOB[i])*(scale/1000);
            }
            

            //boundary defintion X and Y
            if(worldOB[i].xpos > boundX-worldOB[i].mass*(scale/1000))
            {
                worldOB[i].xpos = boundX-worldOB[i].mass*(scale/1000);
                if(myWorld.bounceWalls)
                {
                    worldOB[i].Hvelocity = -worldOB[i].Hvelocity+0.5*(worldOB[i].Hvelocity);
                }
            }



            worldOB[i].ypos += worldOB[1].Vvelocity;
   
        }

          
        }

        tickCount++;
    }
 



void timer(int)
{   
    
    glutPostRedisplay();
    glutTimerFunc(1000/60, timer, 0);
}

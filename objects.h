#include "player.h"
#pragma once
namespace InkEngine
{
    class objects
    {
        public:
            float xpos;
            float ypos;
            float Vvelocity;
            float Hvelocity;
            int mass;
            
            //default constructor
            objects()
            {

            }

            //constructor
            objects(float xpos, float ypos, int mass, float Vvelocity = 0, float Hvelocity = 0)
            {
                this->xpos = xpos;
                this->ypos = ypos;
                this->mass = mass;
                this->Vvelocity = Vvelocity;
                this->Hvelocity = Hvelocity;
            }
        
    };
}
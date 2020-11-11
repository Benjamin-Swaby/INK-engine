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
            bool dynamic;
            
            //default constructor
            objects()
            {

            }

            //constructor
            objects(float xpos, float ypos, int mass,bool dynamic = false, float Vvelocity = 0, float Hvelocity = 0)
            {
                this->xpos = xpos;
                this->ypos = ypos;
                this->mass = mass;
                this->Vvelocity = Vvelocity;
                this->Hvelocity = Hvelocity;
                this -> dynamic = dynamic;

            }
        
    };
}

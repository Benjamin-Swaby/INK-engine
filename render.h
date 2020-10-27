#pragma once
#include "objects.h"
namespace InkEngine
{
    class render
    {
        public:
            
            objects * worldOBJ;
            int length;
            //methods
            int start(int argc, char** argv);



            //constructor
            render(objects * objs, int length)
            {   
                this->length = length;
                worldOBJ = objs;
            }

            


    };
}



#pragma once
#include "objects.h"
namespace InkEngine
{
    class render
    {
        public:
            
            objects * worldOBJ;
            //methods
            int start(int argc, char** argv);



            //constructor
            render(objects * objs)
            {
                worldOBJ = objs;
            }

            


    };
}



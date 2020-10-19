#include "objects.h"
#pragma once
namespace InkEngine
{
    class render
    {
        public:
            objects * worldOBJ;
            int start(int argc, char** argv);
            

            //constructor
            render(objects * objs)
            {
                worldOBJ = objs;
            }

    };
}
#include "render.h"
#include "objects.h"
#include <iostream>

using namespace InkEngine;

int main(int argc, char** argv)
{
    objects myobjs[2];
    myobjs[0] = objects(1000.0,100.0,15);
    myobjs[1] = objects(200.0,200.0,15,true);

    render renderer(myobjs,2);
    renderer.start(argc, argv);


    return 0;
}

#include "render.h"
#include "objects.h"

using namespace InkEngine;

int main(int argc, char** argv)
{

    objects myobjs[2];
    myobjs[0] = objects(100.0,100.0,100);
    myobjs[1] = objects(100.0,100.0,100);

    render renderer(myobjs);


    renderer.start(argc, argv);


    return 0;
}

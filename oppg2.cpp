#include <stdlib.h>
#include "oppg2.h"



std::vector<Vertex> getvertixes2()
{
    float x = 0, y = 0, z = 0;
    std::vector<Vertex> vertixes;

    for (float i = 0; i < 10*4; i+=0.1)
    {
        x = sin(i);
        y = cos(i);
        z += 0.05;

        vertixes.push_back({x, y, z, 0.5, 0.5, 0.0});
    }

    FILE* dataFile = fopen("Oppg2_Formula.txt", "w+");
    fprintf(dataFile, "%s%zu%s", "#", vertixes.size(), "\n");
    for(const Vertex& v : vertixes)
    {
        fprintf(dataFile, "%f %f %f %f %f %f\n", v.x, v.y, v.z, v.r, v.g, v.b);
    }

    fclose(dataFile);

    return vertixes;



}

/*
Velg funksjonen av to variable som vi kaller apesadelen, f (x) = x2y, et passende
område i xy-planet (eller xz-planet), og en oppdeling. Velg en oppløsning h (bruk
en grov oppløsning til å begynne med) og regn ut funksjonsverdier over området,
som på gur 2.2. Lag en tekstl med xyz (eventuelt også rgb og uv-koordinater)
linjevis. Antall linjer skal stå øverst i la.
*/

#include "oppg3.h"
#include <qmath.h>


double f(const float x, const float y){
    return x*x*y;
};

std::vector<Vertex> getvertixes3()
{
    std::vector<Vertex> vertixes;


    float xmin=0.0f, xmax=1.0f, ymin=0.0f, ymax=1.0f, h=0.125f;
    for (auto x=xmin; x<xmax; x+=h) {
        for (auto y=ymin; y<ymax; y+=h)
        {
            float z = f(x, y);
            vertixes.push_back(Vertex{x,y,z,x,y,z});
            z = f(x+h, y);
            vertixes.push_back(Vertex{x+h,y,z,x,y,z});
            z = f(x, y+h);
            vertixes.push_back(Vertex{x,y+h,z,x,y,z});
            vertixes.push_back(Vertex{x,y+h,z,x,y,z});
            z = f(x+h, y);
            vertixes.push_back(Vertex{x+h,y,z,x,y,z});
            z = f(x+h, y+h);
            vertixes.push_back(Vertex{x+h,y+h,z,x,y,z});
        }
    }

    FILE* dataFile = fopen("Oppg3_Formula.txt", "w+");
    fprintf(dataFile, "%s%zu%s", "#", vertixes.size(), "\n");
    for(const Vertex& v : vertixes)
    {
        fprintf(dataFile, "%f %f %f %f %f %f\n", v.x, v.y, v.z, v.r, v.g, v.b);
    }

    fclose(dataFile);


    return vertixes;
}

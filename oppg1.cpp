/*
1. Velg en egen funksjon f (x) og en passende denisjonsmengde Df = [a, b].
2. Velg antall intervaller n slik at du får n + 1 punkter x0, x1, . . . , xn og
oppløsning h = ∆x = b−a
n .
3. Regn ut funksjonsverdier f (xi) i hvert punkt. Regn også ut f ′(x) eller
Newton's dierenskvotient i hvert punkt.
4. Bestem en farge for hvert verteks slik at grafen får en farge (for eksempel
grønn) når funksjonen er stigende, og en annen farge (for eksempel rød)
når funksjonen er avtakende.
5. Beregn funksjonsverdi og skriv ut verteksdata for hvert punkt på en tekst-
l. På første linje i len skal antall punkter stå. Deretter følger verteksdata
for hvert punkt linje for linje
*/

#include "oppg1.h"
#include <stdlib.h>

float f(const double x)
{
    return(x*x*x*x*2)+(5*x*x*x)-(0.4*x)-0.6;
}

float derf(const double x)
{
    return(2*x*x*x)+(5*x*x)-0.4;
}


std::vector<Vertex> getvertixes1()
{
    std::vector<Vertex> vertixes;
    DF df{-5, 5};
    unsigned int n = 100;
    float h = (df.b - df.a)/n;
    float x = df.a;
    float green, red;


    for (unsigned int i = 0; i < n + 1; i++){
        if(derf(x)>0.0){
            green = 1.0;
            red = 0.0;
        }
        else {
            green = 0.0;
            red = 1.0;
        }
        vertixes.push_back(Vertex{x, f(x), 0.0f, red, green, 0.0f});
        x += h;
    }

    FILE* dataFile = fopen("Oppg1_Formula.txt", "w+");
    fprintf(dataFile, "%s%zu%s", "#", vertixes.size(), "\n");
    for(const Vertex& v : vertixes)
    {
        fprintf(dataFile, "%f %f %f %f %f %f\n", v.x, v.y, v.z, v.r, v.g, v.b);
    }

    fclose(dataFile);
    return vertixes;
};

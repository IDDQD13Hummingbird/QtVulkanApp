#include "World.h"
#include <vector>

float randomFloat()
{
    srand(time(0));
    return (float)(rand()) / (float)(RAND_MAX);
}

World::World() {

    drawType = 1; // 0 = fill, 1 = line
    //std::vector<float> dot_x = {};
    //std::vector<float> dot_y = {};
    int dimension = 20; //how many layers of rows and columns of dots?
    int level; //Necessary tracker for incrementing.
    std::vector<float> dot_z = {};

    for (level = 0; level < dimension; level++){
        float value_y = level;
        for (int i = 0; i < dimension; i++){
            float value_x = i;
            srand(time(0));
            float random = randomFloat();
            mVertices.push_back(Vertex {value_x, value_y, random,   random, random, random, value_x/dimension, value_y/dimension});
            length++;
            //For now, Z is literally a random value. Can be easily replaced with a file read.
        }
    }

   /*
    Vertex v1{0.0f,   0.0f,  0.0f,   1.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    Vertex v2{1.0f,   0.0f,  0.0f,   0.0f, 1.0f, 0.0f, 0.0f, 0.0f};
    Vertex v3{0.0f,   1.0f,  0.0f,   0.0f, 0.0f, 1.0f, 0.0f, 0.0f};
    Vertex v4{1.0f,   1.0f,  0.0f,   1.0f, 1.0f, 0.0f, 0.0f, 0.0f};

    //Pushing 1st triangle,
    mVertices.push_back(Vertex {0.0f,   0.0f,  0.0f,   1.0f, 0.0f, 0.0f, 0.0f, 0.0f});
    mVertices.push_back(v2);
    mVertices.push_back(v3);
    mVertices.push_back(v4);

    //Indexes for the two triangles to form a quad
    mIndices.push_back(0);
    mIndices.push_back(1);
    mIndices.push_back(2);
    mIndices.push_back(2);
    mIndices.push_back(1);
    mIndices.push_back(3);
    */
    //Now we're done with the dots. There should be 20*20 = 400 dots to go through.
    //int pin = dimension;
    //int i = 0;
    //for(level = 0; level < dimension-1; level++){
        //int lvl = dimension*level;
    for (int i = 0; i < length; i++){
        if((i % dimension)-(dimension-1) != 0){
                //down
                mIndices.push_back(i);
                mIndices.push_back(i+1);
        }
        /*if((i % dimension*(dimension-1)) != 0){*/
            //downa
            mIndices.push_back(i);
            mIndices.push_back(i+dimension);
        //}
                //mIndices.push_back(i+dimension);
                //up
                //mIndices.push_back(i+1);
                //mIndices.push_back(i+1+dimension);
                //mIndices.push_back(i+dimension);
        }
    //}


        //
        /*
        //down
        mIndices.push_back(i);
        mIndices.push_back(i+1);

        mIndices.push_back(i+dimension);
        //up
        mIndices.push_back(i+1);
        mIndices.push_back(i+1+dimension);
        mIndices.push_back(i+dimension);
        */
            //
            /*mIndices.push_back(0)
            mVertices.push_back(Vertex{ dot_x[i], dot_y[i], dot_z[i],       colour, colour, colour,    0.f, 0.f });
            mVertices.push_back(Vertex{ dot_x[i+1], dot_y[i], dot_z[i],       colour, colour, colour,    1.f, 0.f });
            mVertices.push_back(Vertex{ dot_x[i], dot_y[i+1], dot_z[i],       colour, colour, colour,    0.f, 1.f });*/
        /*
        for (int i = 0; i < dimension-1; i++){
            //float colour = (i/dimension*level);
            mVertices.push_back(Vertex{ dot_x[i], dot_y[i], dot_z[i],       colour, colour, colour,    0.f, 0.f });
            mVertices.push_back(Vertex{ dot_x[i+1], dot_y[i], dot_z[i],       colour, colour, colour,    1.f, 0.f });
            mVertices.push_back(Vertex{ dot_x[i], dot_y[pin+i], dot_z[i],       colour, colour, colour,    0.f, 1.f });
        }
        pin = pin + dimension;
    }
*/


    mMatrix.setToIdentity();

}

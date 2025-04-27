#include "World.h"
#include <vector>

float randomFloat()
{
    srand(time(NULL));
    return (float)(rand()) / (float)(RAND_MAX);
}

World::World() {
    drawType = 1; // 0 = fill, 1 = line

    //std::vector<float> dot_x = {};
    //std::vector<float> dot_y = {};
    int dimension = 20; //how many layers of rows and columns of dots?
    int level; //Necessary tracker for incrementing.
    std::vector<float> dot_z = {};



    int x_min=0;
    int z_min=0;
    unsigned short x_max=dimension; //just the max boundaries of the input image
    unsigned short z_max=dimension; //just the max boundaries of the input image
    float heightPlacement{10.f};

    float vertexXStart{0.f};            // if world origo should be at center use: {0.f - width * horisontalSpacing / 2};
    float vertexZStart{0.f};            // if world origo should be at center use: {0.f + depth * horisontalSpacing / 2};


    //MAKE VERTICES FIRST
    for (auto x=0; x<x_max; x++){   // was x++, y++
        for (auto z=0; z<z_max; z++){
            int index = (z + x * z_max) * 4; // Each pixel has 4 bytes (RGBA)
            if (index >= dimension * dimension * 4) // Extra safety check
            {
                qDebug() << "Index out of bounds:" << index;
                return;
            }
            float heightFromBitmap = randomFloat();         // * heightSpacing + heightPlacement;
            //                                      x - value                      y-value               z-value
            mVertices.emplace_back(Vertex{vertexXStart + (z * dimension), heightFromBitmap*dimension, vertexZStart - (x * dimension),
                                          //  R , G, B                    U, V
                                          randomFloat(),randomFloat(), randomFloat(),           z / (z_max - 1.f), x / (x_max - 1.f)});
        }
    }

    // CONNECT VERTICES (TRIANGULATE THE PLANE) USING INDICES
    for(auto x=0; x<x_max-1; x++)
    {
        for(auto z=0; z<z_max-1; z++)
        {
            //Indices for one quad:
            mIndices.emplace_back(z + x * z_max);               // 0 + 0 * mWidth               = 0
            mIndices.emplace_back(z + x * z_max + z_max + 1);   // 0 + 0 * mWidth + mWidth + 1  = mWidth + 1
            mIndices.emplace_back(z + x * z_max + z_max);       // 0 + 0 * mWidth + mWidth      = mWidth
            mIndices.emplace_back(z + x * z_max);               // 0 + 0 * mWidth               = 0
            mIndices.emplace_back(z + x * z_max + 1);           // 0 + 0 * mWidth + 1           = 1
            mIndices.emplace_back(z + x * z_max + z_max + 1);   // 0 + 0 * mWidth + mWidth + 1  = mWidth + 1
        }
    }


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


    for (int i = 0; i < length; i++){
        if((i % dimension)-(dimension-1) != 0){
            //down
            mIndices.push_back(i);
            mIndices.push_back(i+1);
        }



    mMatrix.setToIdentity();
    }
}

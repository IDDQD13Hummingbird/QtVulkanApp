#include "Enemy.h"
#include "VisualObject.h"

Enemy::Enemy() : VisualObject()

{
    Vertex v1{-0.25f,   -0.25f,  0.0f,   1.0f, 0.2f, 0.2f,   0.0f, 0.0f};
    Vertex v2{0.25f,   -0.25f,  0.0f,   1.0f, 0.5f, 0.2f,   0.0f, 0.0f};
    Vertex v3{-0.25f,   0.25f,  0.0f,   1.0f, 0.75f, 0.25f, 0.0f, 0.0f};
    Vertex v4{0.25f,   0.25f,  0.0f,   1.0f, 0.25f, 0.25f, 0.0f, 0.0f};
    Vertex top{0.0f,  0.0f,  0.5f,   1.0f, 1.0f, 0.5f,   0.0f, 0.0f};

    //Pushing 1st triangle,
    mVertices.push_back(v1);  // 0
    mVertices.push_back(v2);  // 1
    mVertices.push_back(v3);  // 2
    mVertices.push_back(v4);  // 3
    mVertices.push_back(top); // 4
    //mVertices.push_back(v2);
    //mVertices.push_back(v3);

    //Indexes for the two triangles to form a quad
    mIndices.push_back(0);
    mIndices.push_back(1);
    mIndices.push_back(4);
    mIndices.push_back(2);
    mIndices.push_back(3);
    mIndices.push_back(4);
    mIndices.push_back(1);
    mIndices.push_back(2);
    mIndices.push_back(4);
    mIndices.push_back(0);
    mIndices.push_back(3);
    mIndices.push_back(4);


    //Temporary scale and positioning
    mMatrix.scale(0.5f);
    //mMatrix.translate((rand() % 11)+5.f, (rand() % 11)+5.f, 0.f);
}
/*
void Enemy::MoveEnemy()
{

    move(-1,-1,0);

 bool ismove = false;
    int dir = 0;
    for (int r = 0; r < 10; r++){
        if (ismove == true){
            dir = 1;
            ismove = false;
    }
        else{
        dir = -1;
        ismove = true;
    }
        for(int i = 0; i<10; i++){
            for(int j=0; j<10; i++){
            move(i*dir, j*dir, 0);
            }
        }
    }

}*/


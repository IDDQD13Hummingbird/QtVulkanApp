#include "VisualObject.h"

VisualObject::VisualObject()
{
    mMatrix.setToIdentity();
}

void VisualObject::move(float x, float y, float z)
{
    QVector3D add;
    add.setX(x); add.setY(y); add.setZ(z);
    mMatrix.translate(x, y, z);
    mPosition+=add;
}

void VisualObject::scale(float s)
{
    mMatrix.scale(s);
}

void VisualObject::rotate(float t, float x, float y, float z)
{
    mMatrix.rotate(t, x, y, z);
}

bool VisualObject::isColliding(QVector3D Position, float Radius/*, const VisualObject *other*/)
{
    QVector3D VectorDist = /*other->*/mPosition - Position;
    float Dist = VectorDist.length();
    float minDist = /*other->*/mRadius+Radius;
    if (Dist > minDist) {
        return false;
    }

    else { return true; };
}
/*
bool VisualObject::Collider_vs_Collider()
{
    if (me==nullptr||other==nullptr){
        throw("null pointer");
    }
    else{
        return isColliding(me->mPosition, me->mRadius);
    };

}
*/
void VisualObject::Tack(){
    tick += 0.1;
    if(tick > 360){
        tick = 0;
    }
    }

int VisualObject::getTick(){
    return tick;
}

int VisualObject::Direction(){
    if(sin(tick)>0)
    {
    return 1;
    }
    else if(sin(tick)<0){
    return -1;
    }
    else{return 0;};
}

void VisualObject::setPosition(const QVector3D &newPosition)
{
    mPosition = newPosition;
    mMatrix.setToIdentity();
    mMatrix.translate(newPosition);
}

QVector3D VisualObject::ExpungePosition()
{
    return mPosition;
}

float VisualObject::ExpungeRadius()
{
    return mRadius;
}

std::vector<Vertex> VisualObject::ExpungeVertices(){
    return mVertices;
}
/*
std::vector<Vertex> VisualObject::ExpungeVertex(int index){
    return mVertices[index];
};
*/

int VisualObject::ExpungeIndices(int i){
return mIndices[i];
}

int VisualObject::sizeofIndices()
{
    return mIndices.size();
}

void VisualObject::MoveEnemy(int dir){
    move(0.075*dir+sin(tick), 0.075*dir+sin(tick), 0);
};
    //ExpungePosition().x();
    /*int dir = 1;

    for(int i = 0; i<11; i++){
    setPosition({ExpungePosition().x() + i*dir, ExpungePosition().y() + i*dir, 0});
    }
    dir = -1;
    for(int i = 0; i<11; i++){
        setPosition({ExpungePosition().x() + i*dir, ExpungePosition().y() + i*dir, 0});
    }*/
    /*
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
    }*/




#ifndef DOOR_H
#define DOOR_H

#include "VisualObject.h"


class Door : public VisualObject
{
public:
    Door();
    bool ShallWe(QVector3D Position, float Radius/*, const VisualObject *other*/);
};



#endif // DOOR_H

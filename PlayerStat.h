#ifndef PLAYERSTAT_H
#define PLAYERSTAT_H


#include <qvector3d.h>


class PlayerStat {
public:
    virtual void LoseLife() = 0;
    virtual void AddPoints(int points) = 0;
    virtual int GetPoints() = 0;
    virtual QVector3D GetPosition() = 0;
    virtual float GetRadius() = 0;
    virtual void PushPlayer(QVector3D pushVector) = 0;
};

#endif // PLAYERSTAT_H

#ifndef ENEMY_H
#define ENEMY_H
#include "AbstractObjectInteract.h"


class Enemy : public AbstractObjectInteract
{
public:
    Enemy(InfoOverlapHandler* listner, std::string name, Vertex ControlPoints[3]);
    void Init();

    Vertex ControlPoints[3];
    float t{0};

    virtual void Tick(float deltaTime) override;

private:
    Vertex CalculateVectorToTPoint();
    Vertex CalculateTPoint();
    void UpdateT(float deltaTime);
    float lifeTime{0};
    float patrolTime{5};
    float TGrowthDirection{1};

    // IInteract interface
public:
    void Interact(PlayerStat *interactor) override;
};

#endif // ENEMY_H


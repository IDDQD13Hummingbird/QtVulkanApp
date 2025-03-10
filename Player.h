#ifndef PLAYER_H
#define PLAYER_H

#include "Enemy.h"
#include "ControlState.h"
#include "PlayerStat.h"
#include "ObjectOverlap.h"

class Player : public ObjectOverlap, public PlayerStat, public ControlState
{
private:
    int points{0};
protected:
    KeyState keyState;
    float MovementUnitsPerSecond{4};
private:
    void Init();
    void MoveFromInput(float deltaTime);
public:
    Player();
    virtual void Tick(float deltaTime) override;

    // IPlayer interface
public:
    void Damage() override;
    void AddScore(int points) override;
    int GetScore() override;
    QVector3D GetPosition() override;
    void PushPlayer(QVector3D pushVector) override;
    float GetRadius() override;

    // IControl interface
public:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

};

#endif // PLAYER_H

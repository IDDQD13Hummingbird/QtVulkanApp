#ifndef PLAYER_H
#define PLAYER_H

#include "PlayerStat.h"
#include "Controls.h"

class Player : public public PlayerStat, public Controls
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
    void LoseLife() override;
    void AddPoints(int points) override;
    int GetPoints() override;
    QVector3D GetPosition() override;
    void PushPlayer(QVector3D pushVector) override;
    float GetRadius() override;

    // IControl interface
public:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

};


#endif // PLAYER_H

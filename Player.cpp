#include "Player.h"

void Player::Init()
{
    Vertex vA{ -0.5f, 0.0f, 0.0f,   0.2f, 0.2f, 0.8f,       0.0f, 0.0f };   //A
    Vertex vB{ 0.5f, 0.5f, 0.0f,    0.1f, 0.1f, 0.7f,       0.0f, 0.0f };   //B
    Vertex vC{ 0.5f, -0.5f, 0.0f,   0.8f, 0.8f, 0.7f,       0.0f, 0.0f };   //C
    Vertex vD{ 1.5f, 0.0f, 0.0f,    0.25f, 0.25f, 0.85f,    0.0f, 0.0f };   //D
    Vertex vE{ -1.5f, 0.5f, 0.0f,   0.2f, 0.2f, 0.8f,       0.0f, 0.0f };   //E
    Vertex vF{ -1.5f, -0.5f, 0.0f,  0.8f, 0.8f, 0.7f,       0.0f, 0.0f };   //F
    Vertex vG{ 0.5f, 0.0f, 0.5f,    0.2f, 0.2f, 0.8f,       0.0f, 0.0f };   //G
    Vertex vH{ 0.5f, 0.0f, -0.5f,   0.2f, 0.2f, 0.8f,       0.0f, 0.0f };   //H
    Vertex vI{ -1.25f, 0.0f, 0.0f,  0.25f, 0.25f, 0.85f,    0.0f, 0.0f };   //I



    mVertices.push_back(vA);
    mVertices.push_back(vB);
    mVertices.push_back(vG);

    mVertices.push_back(vA);
    mVertices.push_back(vB);
    mVertices.push_back(vH);

    mVertices.push_back(vD);
    mVertices.push_back(vB);
    mVertices.push_back(vG);

    mVertices.push_back(vD);
    mVertices.push_back(vB);
    mVertices.push_back(vH);
    //
    mVertices.push_back(vA);
    mVertices.push_back(vG);
    mVertices.push_back(vC);

    mVertices.push_back(vA);
    mVertices.push_back(vH);
    mVertices.push_back(vC);

    mVertices.push_back(vD);
    mVertices.push_back(vG);
    mVertices.push_back(vC);

    mVertices.push_back(vD);
    mVertices.push_back(vH);
    mVertices.push_back(vC);
    //
    mVertices.push_back(vE);
    mVertices.push_back(vI);
    mVertices.push_back(vA);

    mVertices.push_back(vF);
    mVertices.push_back(vA);
    mVertices.push_back(vI);
}

void Player::MoveFromInput(float deltaTime)
{
    QVector2D movementDirection;

    if(keyState.W) {
        movementDirection.setX(1);
    }
    if(keyState.D) {
        movementDirection.setY(1);
    }
    if(keyState.S) {
        movementDirection.setX( ( movementDirection.x() - 1 ) );
    }
    if(keyState.A) {
        movementDirection.setY( ( movementDirection.y() - 1 ) );
    }

    if(movementDirection.x() == 0 && movementDirection.y() == 0) {
        return;
    }
    movementDirection.normalize();



    float xDistance = movementDirection.x() * deltaTime * MovementUnitsPerSecond;
    float zDistance = movementDirection.y() * deltaTime * MovementUnitsPerSecond;


    //move(xDistance, 0, zDistance);
    move(zDistance, xDistance, 0);
}

Player::Player() : ObjectOverlap("Player", {0, 0, 0, 0, 0, 0, 0, 0}, 1) {
    Init();
}

void Player::Tick(float deltaTime)
{

    if(!IsActive()) return;

    MoveFromInput(deltaTime);


}

void Player::Damage()
{
    qDebug("You lost\n");
    std::cout << "You lost\n";
    Deactivate();
}

void Player::AddScore(int points)
{
    Player::points+=points;
    qDebug() << Player::points << " of 7 pickups are collected\n";
}

int Player::GetScore()
{
    return points;
}

void Player::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()) {
    case Qt::Key_W:
        keyState.W=1;
        break;
    case Qt::Key_A:
        keyState.A=1;
        break;
    case Qt::Key_S:
        keyState.S=1;
        break;
    case Qt::Key_D:
        keyState.D=1;
        break;
    }
}

void Player::keyReleaseEvent(QKeyEvent *event)
{
    switch(event->key()) {
    case Qt::Key_W:
        keyState.W=0;
        break;
    case Qt::Key_A:
        keyState.A=0;
        break;
    case Qt::Key_S:
        keyState.S=0;
        break;
    case Qt::Key_D:
        keyState.D=0;
        break;
    }
}

QVector3D Player::GetPosition()
{
    float x = mMatrix.column(3).x();
    float y = mMatrix.column(3).y();
    float z = mMatrix.column(3).z();

    return QVector3D(x, y, z);
}

void Player::PushPlayer(QVector3D pushVector)
{
    move(pushVector.x(), pushVector.y(), pushVector.z());
}

float Player::GetRadius()
{
    return radius;
}

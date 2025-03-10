#include "PlayerGetter.h"


PlayerGetter::PlayerGetter()
{
    player = new Player();
}

PlayerGetter::~PlayerGetter()
{
    delete player;
}


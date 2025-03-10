#ifndef PLAYERGETTER_H
#define PLAYERGETTER_H
#include "Player.h"



class PlayerGetter
{
private:
    PlayerGetter();
    ~PlayerGetter();
    Player* player;
    static PlayerGetter* instance;


public:
    PlayerGetter(const PlayerGetter&) = delete; // rule of three
    PlayerGetter& operator=(const PlayerGetter&) = delete;

    static Player* GetPlayer() {
        return get().player;
    };

    static PlayerGetter& get() {
        if (instance == nullptr) instance = new PlayerGetter;
        return *instance;
    }

    static void destruct() {
        delete instance;
        instance = nullptr;
    }
};


#endif // PLAYERGETTER_H

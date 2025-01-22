#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include "Player.hpp"

class Game {

public:
    Game(const Player& player) : m_player(player) {} 

    virtual void play() = 0;

protected:

    Player m_player;


};

#endif // GAME_H

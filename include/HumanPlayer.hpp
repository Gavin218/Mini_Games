#ifndef HUMAN_PLAYER_HPP
#define HUMAN_PLAYER_HPP

#include "Player.hpp"
#include <iostream>

class HumanPlayer : public Player {
public:
    HumanPlayer(std::string id) : Player(id) {}

};

#endif

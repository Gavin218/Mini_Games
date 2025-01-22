#ifndef COMPUTER_PLAYER_HPP
#define COMPUTER_PLAYER_HPP

#include "Player.hpp"

#include <memory>


class ComputerPlayer : public Player {
public:
    ComputerPlayer(std::string id) : Player(id) {}

};

#endif
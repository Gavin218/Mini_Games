#ifndef COWBOY_SHOWDOWN_GAME_H
#define COWBOY_SHOWDOWN_GAME_H

#include <vector>
#include <memory>

#include "Game.hpp"
#include "Player.hpp"

class CowboyShowdownGame : public Game {

public:
    CowboyShowdownGame(const Player& player) : Game(player){}
    
    void play() override; 

private:

    std::vector<std::shared_ptr<Player>> m_enemys;

    bool showdown();



};

#endif // GAME_H
#ifndef SURVIVE_GAME_H
#define SURVIVE_GAME_H

#include <vector>
#include <memory>

#include "Game.hpp"
#include "Player.hpp"

class SurviveGame : public Game {

public:
    SurviveGame(const Player& player) : Game(player){}
    
    void play() override; 

private:

    std::vector<std::shared_ptr<Player>> m_competitors;


};

#endif // GAME_H
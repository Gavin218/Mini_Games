#ifndef RUSSIAN_ROULETTE_GAME_H
#define RUSSIAN_ROULETTE_GAME_H

#include <vector>
#include <memory>

#include "Game.hpp"
#include "Player.hpp"

class RussianRouletteGame : public Game {

public:
    RussianRouletteGame(const Player& player) : Game(player){}
    
    void play() override; 

private:

    std::vector<std::shared_ptr<Player>> m_enemys;

    std::vector<bool> m_bullets;

    void randomRound();

    bool showdown();

};

#endif // GAME_H
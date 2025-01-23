#ifndef GAME_UTIL_H
#define GAME_UTIL_H

#include <iostream>
#include <set>
#include <vector>
#include <memory>
#include <string>

#include <Player.hpp>


class GameUtil {
public:
    
    static std::string generateOneEnglishName();

    static std::vector<std::shared_ptr<Player>> generateEnemyVec(int enemyNum);

};

#endif // GAME_UTIL_H

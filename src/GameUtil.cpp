#include "GameUtil.hpp"
#include "ComputerPlayer.hpp"

#include <algorithm>
#include <random>
#include <chrono>

std::string GameUtil::generateOneEnglishName() {
    auto time_seed = std::chrono::system_clock::now().time_since_epoch().count();
    static std::mt19937 gen(time_seed);
    
    // 生成3-5的随机长度
    std::uniform_int_distribution<> lenDist(3, 5);
    int length = lenDist(gen);
    
    // 生成小写字母的分布
    std::uniform_int_distribution<> charDist(0, 25);
    
    std::string result;
    
    // 生成第一个大写字母
    result += 'A' + charDist(gen);
    
    // 生成剩余的小写字母
    for(int i = 1; i < length; i++) {
        result += 'a' + charDist(gen);
    }
    
    return result;
}

std::vector<std::shared_ptr<Player>> GameUtil::generateEnemyVec(int enemyNum) {
    std::vector<std::shared_ptr<Player>> enemys;
    std::set<std::string> names;
    for (int i = 0; i < enemyNum; i++) {
        std::string new_name = generateOneEnglishName();
        while (names.find(new_name) != names.end()) {
            new_name = generateOneEnglishName();
        }
        auto enemy = std::make_shared<ComputerPlayer>(new_name);
        enemys.push_back(enemy);
    }
    auto time_seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 gen(time_seed);  // 使用系统时间生成的种子
    std::shuffle(enemys.begin(), enemys.end(), gen);  // 打乱顺序
    return enemys;
}
#include "GameUtil.hpp"

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
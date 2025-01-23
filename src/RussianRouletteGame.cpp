#include "RussianRouletteGame.hpp"
#include "ComputerPlayer.hpp"
#include "GameUtil.hpp"

#include <algorithm>
#include <random>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <set>

void RussianRouletteGame::play() {
    std::cout << "进入俄罗斯轮盘赌游戏!!" << std::endl;
    std::cout << "游戏规则：双人对局，一个六发子弹的弹夹，安放一枚子弹，拨动转盘" << std::endl;
    std::cout << "一方朝自己射击，如果没死，就交由对方，直至弹响" << std::endl;
    int enemyNum;
    std::cout << "请输入对手数量";
    std::cin >> enemyNum;
    std::cin.get();
    std::cout << std::endl;

    std::set<std::string> names;
    for (int i = 0; i < enemyNum; i++) {
        std::string new_name = GameUtil::generateOneEnglishName();
        while (names.find(new_name) != names.end()) {
            new_name = GameUtil::generateOneEnglishName();
        }
        auto enemy = std::make_shared<ComputerPlayer>(new_name);
        m_enemys.push_back(enemy);
    }
    auto time_seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 gen(time_seed);  // 使用系统时间生成的种子
    std::shuffle(m_enemys.begin(), m_enemys.end(), gen);  // 打乱顺序

    std::cout << "游戏开始！主角 " << m_player.getId() << " 登场！" << std::endl;
    while (!m_enemys.empty()) {
        auto now_enemy = m_enemys[0];
        std::cout << "接下来你的对手是： " << now_enemy->getId() << " !!!!!!" << std::endl;

        randomRound();

        if (showdown()) {
            std::cout << "你死了！!!!" << std::endl;
            std::cout << "本次游戏，你一共战胜了 " << enemyNum - m_enemys.size() << "名对手" << std::endl;
            return ;
        } else {
            std::cout << "对手倒地！！！" << std::endl;
            m_enemys.erase(m_enemys.begin());
        }
    }
    std::cout << "最后获胜者是： " << m_player.getId() << " 你赢了！" << std::endl;
}


void RussianRouletteGame::randomRound() {
    m_bullets = std::vector<bool>(6, false);
    m_bullets[0] = true;
    auto time_seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 gen(time_seed);  
    std::shuffle(m_bullets.begin(), m_bullets.end(), gen);  // 打乱顺序
    std::cout << "已重新拨动轮盘！！" << std::endl;
}

bool RussianRouletteGame::showdown() {
    bool my_round = true;
    while (!m_bullets.empty()) {
        if (my_round) {
            std::cout << "请你扣动扳机！" << std::endl;
            // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            std::cin.get();  
        } else {
            std::cout << "等待对手扣动扳机！" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(3));
        }

        bool has_bullet = m_bullets[m_bullets.size() - 1];
        m_bullets.pop_back();
        if (has_bullet) {
            std::cout << "BOOM!!!!!!!！" << std::endl;
            return my_round;
        } else {
            std::cout << "ka~~~ (空弹)" << std::endl;
            if (my_round) {
                std::cout << "你逃过一劫！！手枪交给对手！！" << std::endl;
            } else {
                std::cout << "对手逃过一劫！！手枪交给你！！" << std::endl;
            }
            
            my_round = !my_round;
        }
        std::cout << std::endl;
    }
    return true;
}
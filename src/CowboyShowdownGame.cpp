#include "CowboyShowdownGame.hpp"
#include "GameUtil.hpp"

#include <iostream>
#include <chrono>
#include <thread>
#include <random>
#include <conio.h>  // 用于 _kbhit()
#include <windows.h>  // 用于设置控制台颜色

void CowboyShowdownGame::play() {
    std::cout << "进入牛仔游戏!!" << std::endl;
    std::cout << "游戏规则：双人对局，待信号发出，就可抽枪朝对方射击" << std::endl;
    std::cout << "一人倒下，另一人胜利" << std::endl;
    int enemyNum;
    std::cout << "请输入对手数量";
    std::cin >> enemyNum;
    std::cin.get();
    std::cout << std::endl;

    m_enemys = GameUtil::generateEnemyVec(enemyNum);

    std::cout << "游戏开始！主角 " << m_player.getId() << " 登场！" << std::endl;
    while (!m_enemys.empty()) {
        auto now_enemy = m_enemys[0];
        std::cout << "接下来你的对手是： " << now_enemy->getId() << " !!!!!!" << std::endl;

        if (showdown()) {
            std::cout << "对手被击中！！！你赢了！！" << std::endl;
            m_enemys.erase(m_enemys.begin());
        } else {
            std::cout << "你输了！!!!" << std::endl;
            std::cout << "本次游戏，你一共战胜了 " << enemyNum - m_enemys.size() << "名对手" << std::endl;
            return ;
        }
    }
    std::cout << "最后获胜者是： " << m_player.getId() << " 你赢了！" << std::endl;
}

bool CowboyShowdownGame::showdown() {
    std::cout << "你准备好了吗？（按回车表示好了）" << std::endl;
    std::cin.get();
    std::cout << "等待信号指令！信号指令一旦发出就可以射击！如果提前掏枪你将被判负！" << std::endl;
    
    // 设置随机数生成器
    auto time_seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 gen(time_seed);
    std::uniform_int_distribution<> waitDist(3000, 10000);
    int waitTime = waitDist(gen);
    
    // 清空输入缓冲区
    while (_kbhit()) {
        _getch();
    }
    
    // 等待过程中检测提前开枪
    auto startWait = std::chrono::high_resolution_clock::now();
    while (true) {
        if (_kbhit()) {
            _getch();  // 消费这个按键
            std::cout << "你提前开枪了！判负！" << std::endl;
            return false;
        }
        
        auto currentTime = std::chrono::high_resolution_clock::now();
        auto elapsedWaitTime = std::chrono::duration_cast<std::chrono::milliseconds>(
            currentTime - startWait).count();
            
        if (elapsedWaitTime >= waitTime) {
            break;  // 等待时间结束
        }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    
    // 设置文字颜色为红色
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
    std::cout << "信号发出!" << std::endl;
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    
    // 生成对手反应时间 (10-500ms)
    std::uniform_int_distribution<> reactionDist(10, 500);
    int enemyReactionTime = reactionDist(gen);
    
    // 开始正式对决
    auto startTime = std::chrono::high_resolution_clock::now();
    while (true) {
        auto currentTime = std::chrono::high_resolution_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(
            currentTime - startTime).count();
            
        if (_kbhit()) {
            _getch();
            std::cout << "你赢了！牛仔之神！！" << std::endl;
            return true;
        }
        
        if (elapsedTime >= enemyReactionTime) {
            std::cout << "你输了！对手先开枪了！" << std::endl;
            return false;
        }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}
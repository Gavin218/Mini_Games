#include "SurviveGame.hpp"
#include "GameUtil.hpp"

#include <iostream>
#include <chrono>
#include <thread>
#include <algorithm>
#include <random>

void SurviveGame::play() {
    std::cout << "进入生存游戏!!" << std::endl;
    std::cout << "游戏规则：房间内有与人数相等的椅子，每个人选择一把椅子坐下" << std::endl;
    std::cout << "随后，杀手进入，随机抽取向一把椅子上的人射击" << std::endl;
    std::cout << "被射击者死亡，椅子撤出，剩余椅子重新编号，剩余人重新选择" << std::endl;
    int enemyNum;
    std::cout << "请输入竞争者人数";
    std::cin >> enemyNum;
    std::cin.get();
    std::cout << std::endl;

    m_competitors = GameUtil::generateEnemyVec(enemyNum);

    std::cout << "游戏开始！主角 " << m_player.getId() << " 登场！" << std::endl;
    int round = 1;
    while (!m_competitors.empty()) {
        std::cout << "你进入了第 " << round++ << "轮！" << std::endl;
        int chair = 0;
        while (chair <= 0 || chair > m_competitors.size() + 1) {
            std::cout << "请输入选取椅子序号，范围为 1 到" << m_competitors.size() + 1 << std::endl;
            std::cin >> chair;
            std::cin.get();
            std::cout << std::endl;
            if (chair <= 0 || chair > m_competitors.size() + 1) {
                std::cout << "输入序号需在范围内！" << std::endl;
            }
        }
        std::cout << "你选择了 " << chair << " 已就座！" << std::endl;

        auto time_seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 gen(time_seed);  // 使用系统时间生成的种子
        std::shuffle(m_competitors.begin(), m_competitors.end(), gen);  // 打乱顺序
        m_competitors.insert(m_competitors.begin() + chair - 1, std::make_shared<Player>(m_player)); 
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "其他竞争者也已选好并坐下！" << std::endl;

   
        std::cout << "当前就座顺序为： ";
        for (int i = 0; i < m_competitors.size(); i++) {
            std::cout << m_competitors[i]->getId() << ", ";
        }
        std::cout << std::endl;

        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout << "杀手进入！！！！开始环顾选择" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(3));
        int dead_chair = GameUtil::randomNumInRange(1, m_competitors.size());
        std::cout << "杀手已经选好了！！！！他选择了 " << dead_chair << "  !!!" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout << "杀手射击！！！！" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        if (dead_chair == chair) {
            std::cout << "你被击中！！死亡！！！" << std::endl;
            return ;
        } else {
            std::cout << "被击中的人是 " << m_competitors[dead_chair - 1]->getId() << " !! 已倒地！！" << std::endl;
            m_competitors.erase(m_competitors.begin() + std::max(chair, dead_chair) - 1);
            m_competitors.erase(m_competitors.begin() + std::min(chair, dead_chair) - 1);
        }


        std::this_thread::sleep_for(std::chrono::seconds(3));
    }
    std::cout << "最后幸存者是： " << m_player.getId() << " 你赢了！" << std::endl;
}
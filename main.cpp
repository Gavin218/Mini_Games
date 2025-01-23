#include "Game.hpp"
#include "RussianRouletteGame.hpp"
#include "CowboyShowdownGame.hpp"
#include "Player.hpp"
#include "HumanPlayer.hpp"
#include "ComputerPlayer.hpp"

#include <windows.h>
#include <cstdlib>
#include <map>


int chooseGame(std::map<int, std::string>& game2Desc) {
    std::cout << "目前有以下游戏可供游玩： " << std::endl;
    for (auto it = game2Desc.begin(); it != game2Desc.end(); ++it) {
        std::cout << it->first << "-" << it->second << std::endl;
    }
    std::cout << "请输入选择："; 
    while (true) {
        int mode;
        std::cin >> mode;
        if (game2Desc.find(mode) == game2Desc.end()) {
            std::cout << "该游戏不存在！请重新输入：";
        } else {
            return mode;
        }
    }
    return -1;
}

std::map<int, std::string> addGameDesc() {
    std::map<int, std::string> game2Desc;
    game2Desc[1] = "俄罗斯轮盘赌";
    game2Desc[2] = "牛仔对决";
    return game2Desc;
}

int main() {
    // 设置控制台代码页为 UTF-8
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    std::map<int, std::string> game2Desc = addGameDesc();
    HumanPlayer player("SUPER MAN");

    std::cout << "请选择游戏：" << std::endl;

    // 定义一个指向游戏的指针，后面根据选择的游戏来初始化
    Game* game = nullptr; 

    switch (chooseGame(game2Desc)) {
    case 1:
        game = new RussianRouletteGame(player); // 根据选择创建游戏
        break;
    case 2:
        game = new CowboyShowdownGame(player); // 根据选择创建游戏
        break;
    default:
        break;
    }

    if (game != nullptr) {
        game->play(); // 使用指针调用游戏的 play 方法
        delete game;  // 游戏结束后释放内存
    }

    std::cout << "按回车键退出...";
    std::cin.get();
    return 0;
}

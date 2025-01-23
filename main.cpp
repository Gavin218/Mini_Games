#include "Game.hpp"
#include "RussianRouletteGame.hpp"
#include "Player.hpp"
#include "HumanPlayer.hpp"
#include "ComputerPlayer.hpp"

#include <windows.h>

int main() {

    // 设置控制台代码页为 UTF-8
    SetConsoleOutputCP(65001);
    // 如果还需要输入中文，也设置输入代码页
    SetConsoleCP(65001);

    HumanPlayer player("SUPER MAN");
    RussianRouletteGame game(player);
    game.play();
    return 0;
}
#include "Game.hpp"
#include "RussianRouletteGame.hpp"
#include "Player.hpp"
#include "HumanPlayer.hpp"
#include "ComputerPlayer.hpp"


int main() {
    HumanPlayer player("0009");
    RussianRouletteGame game(player);
    game.play();
    return 0;
}
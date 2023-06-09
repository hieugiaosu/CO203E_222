#ifndef GAME_H
#define GAME_H
#include<bits/stdc++.h>
#include "Player.h"
#include "Board.h"
#include "GuiSystem.h"
#include "ListOfPair.h"
    using namespace std;
class Game{
    private:
        Player * player1;
        Player * player2;
        Board * board;
        GuiSystem * gui;
    public:
        Game(Player* player1, Player* player2, Board* board, GuiSystem *gui);
        void setPlayer(Player* player1, Player* player2);
        void gameLoop();
        ~Game();
};
#endif
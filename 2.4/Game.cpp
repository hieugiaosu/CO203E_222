#include "include/Game.h"
#include "Board.cpp"
#include "GuiSystem.cpp"
#include "Player.cpp"
#include <chrono>
#include <thread>
Game::Game(Player* player1, Player* player2, Board* board, GuiSystem *gui){
    this->player1 = player1;
    this->player2 = player2;
    this->board = board;
    this->gui = gui;
}

void Game::gameLoop(){
    int turn = 1;
    this->board->reset();
    bool looping = true;
    int* move;
    while (looping){
        int** curr = this->board->getCurrBoardState();
        this->gui->drawCurrState(curr);
        if (turn == 1) move = this->player1->make_move(this->board,this->gui);
        else move = this->player2->make_move(this->board,this->gui);
        if (move == NULL) {
            turn*=-1;
            continue;
        }
        this->board->changeBoardState(move[0],move[1],turn);
        turn*=-1;
        delete[] move;
        curr = this->board->getCurrBoardState();
        this->gui->drawCurrState(curr);
        this->gui->delayMiliSeconds(100);
        looping = !this->board->terminateBoardStateCheck();
    }
    string winner_path = "bitmap/";
    int winner = this->board->getWinner();
    if (winner==1) winner_path += (this->player1->getName()+"_win.bmp");
        else if (winner == -1)  winner_path += (this->player2->getName()+"_win.bmp");
        else winner_path = "bitmap/draw.bmp";
    cout<<winner_path<<endl;
    enum Option option = this->gui->endGame(winner_path);
    // if (option == START_GAME){
    //     Player* temp = this->player1;
    //     this->player1 = this->player2;
    //     this->player2 = this->player1;
    //     this->player1->setTurn(1);
    //     this->player2->setTurn(-1);
    // }
}

void Game::setPlayer(Player* player1, Player* player2){
    this->player1 = player1;
    this->player2 = player2;
}
Game::~Game(){}
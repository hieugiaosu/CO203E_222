#include "Game.cpp"

int main(){
    HumanPlayer *human = new HumanPlayer(1,"you");
    ComputerLV1 *complv1 = new ComputerLV1(-1,"comp_level_1");
    Player* player1 = human;
    Player* player2 = complv1;
    Board* board = new Board;
    GuiSystem * gui = new GuiSystem;
    Game * game = new Game(player1,player2,board,gui);
    bool flag = false;
    try
    {
        enum Option option = NONE;
        gui->init();
        while (option != ENDGAME){
            if (option == QUIT) throw Terminate_program();
            if (option == SETTING) throw Terminate_program();
            if (option == NONE) option = gui->menu();
            if (option = START_GAME) {
                player1->setTurn(1);
                player2->setTurn(-1);
                game->setPlayer(player1,player2);
                game->gameLoop();
                option = CONTINUE;
            }
            if (option = CONTINUE){
                Player * temp = player2;
                player2 = player1;
                player1 = temp;
                option = START_GAME;
            }
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        delete game;
        delete gui;
        delete board;
        delete human;
        delete complv1;
        flag = true;
    }
    if (!flag){
        delete game;
        delete gui;
        delete board;
        delete human;
        delete complv1;
    }
    return 0;

}
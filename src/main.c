#include "../include/main_menu.h"
#include "../include/game.h"
#include "../include/scores.h"

int main() {
    const char* username=run_main_menu();
    if(username){
        int score=run_game();
        updatehighscore(username,score);
    }
    return 0;
}


#include "../include/main_menu.h"
#include "../include/game.h"
#include <stdio.h>

int main() {
    const char* user=run_main_menu();
    run_game(user);
return 0;
}

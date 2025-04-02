#include "../include/main_menu.h"
#include "../include/game.h"

int main() {
    const char* user=run_main_menu(); // displays main menu and returns username
    run_game(user);
}

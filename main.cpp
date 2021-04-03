#include <iostream>
#include "include/Game.h"

int main() {
    srand(time(NULL));
    Game* game = new Game();
    game->Run();
    return 0;
}

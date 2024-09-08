module;

#include <stdlib.h>
#include <time.h>

export module Game;

import WorldArea;
import GameRunner;

export namespace jod {
void RunGame() {
    srand(time(nullptr));

    auto worldArea = WorldArea({140, 100});
    
    auto mainCamera = worldArea.AddMainCamera({70, 50});

    auto player = worldArea.AddPlayer({70, 50});
    
    auto gameRunner = GameRunner(mainCamera, player);

    gameRunner.Start();
}
}
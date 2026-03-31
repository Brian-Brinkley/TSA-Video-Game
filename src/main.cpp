#include "main.h"


int main(){
    InitWindow(1920, 1080, "Video Game");
    //ToggleFullscreen();


    InitAudioDevice();
    //GuiStartState state = InitGuiStart();
    //GuiLoadStyleAmber();

    SetTargetFPS(60);
    Game game = Game();

    while(!WindowShouldClose()){
        game.Update(GetFrameTime());

        BeginDrawing();
        ClearBackground(BLACK);
        game.Draw();
        EndDrawing();
    }

    CloseAudioDevice();
    CloseWindow();
    return 0;
}

#include "main.h"


int main(){
    InitWindow(GetScreenWidth(), GetScreenHeight(), "Video Game");
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
        //jethro.Update(GetFrameTime());
        game.Draw();
        EndDrawing();
    }

    //UnloadMap(map);
    CloseAudioDevice();
    CloseWindow();
    return 0;
}

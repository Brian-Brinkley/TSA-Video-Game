#include "main.h"


int main(){
    InitWindow(GetScreenWidth(), GetScreenHeight(), "Video Game");
    ToggleFullscreen();


    InitAudioDevice();
    //GuiStartState state = InitGuiStart();
    //GuiLoadStyleAmber();

    SetConfigFlags(FLAG_VSYNC_HINT);
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

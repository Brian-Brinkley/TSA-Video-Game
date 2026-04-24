#include "main.h"


int main(){
#ifdef PLATFORM_DESKTOP
    InitWindow(1920, 1080, "Video Game");
#endif

#ifdef PLATFORM_WEB
    InitWindow(1600, 900, "Video Game");
#endif

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    SetWindowSize(GetScreenWidth(), GetScreenHeight());

    ToggleFullscreen();

    InitAudioDevice();
    //GuiStartState state = InitGuiStart();
    //GuiLoadStyleAmber();

    //SetTargetFPS(60);
    SetConfigFlags(FLAG_VSYNC_HINT);
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

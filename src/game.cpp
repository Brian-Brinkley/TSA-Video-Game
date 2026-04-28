#include "game.h"
#include "raymath.h"

Game::Game() {
    running = true;
    camera.zoom = 2;
    camera.offset = {GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};
    camera.rotation = 0;
    camera.target.x = std::round((jethro.position.x + jethro.source.width / 2) * 3) / 3;
    camera.target.y = std::round((jethro.position.y + jethro.source.height / 2) * 3) / 3;
    PlayMusicStream(music);
}

void Game::Update(float deltaTime) {
    if(running) {
        if(keyPressed) {
            jethro.Update(deltaTime, speed);
        }
        
        if(level1Running) {
            musicTimer.Update();
            UpdateMusicStream(music);
            CollisionCheck(level1Collisions, 'x');
            CollisionCheck(level1Collisions, 'y');
            if(CheckCollisionRecs(doorRec, jethro.collisionBox) && IsKeyDown(KEY_E)) {
                level1Running = false;
                //jethro.position = {28 * tileSize * zoom, 18 * tileSize * zoom};
                jethro.position = {16.75f * tileSize * zoom, 2.0f * tileSize * zoom};
                InitLevel2();
                level2Running = true;
            }
        }
        else if(level2Running) {
            //InitLevel2();
            /*while(!level2Ready) {
                std::cout << "Loading level 2... \n";
                }*/
            if(!musicTimer2.active) {
                musicTimer2.Activate();
                PlayMusicStream(music2);
            }
            UpdateMusicStream(music2);
            
            jethro.collisionBox.x += 2 * jethro.scale;
            jethro.collisionBox.y += 6 * jethro.scale;
            jethro.collisionBox.width = (jethro.source.width - 12) * jethro.scale;
            jethro.collisionBox.height = (jethro.source.height - 12) * jethro.scale;
            CollisionCheck(level2Collisions, 'x');
            CollisionCheck(level2Collisions, 'y');
            
            if(CheckCollisionRecs(powerCellRec, jethro.collisionBox) && IsKeyDown(KEY_E)) {
                std::cout << "Game Won \n";
                level2Running = false;
                running = false;
                return;
            }
        }
        
        camera.target = {std::round((jethro.position.x + jethro.source.width * playerScale / 2) * 3) / 3,
            std::round((jethro.position.y + jethro.source.height / 2) * 3) / 3};
            
        if(!Vector2Equals(jethro.directionState, jethro.direction)) {
            jethro.AnimationCheck();
            jethro.directionState = jethro.direction;
        }
        animationTimer.Update();
        return;
    }
}

void Game::CollisionCheck(std::vector<Rectangle> collision, char axis) {
    for(auto &r : collision) {
        if(CheckCollisionRecs(r, jethro.collisionBox)) {
            double dt = GetFrameTime();
            if(axis == 'x') {    
                if(jethro.direction.x != 0) {
                    jethro.position.x -= (jethro.direction.x * speed * dt);
                }
            }
            else if(axis == 'y') {
                if(jethro.direction.y != 0) {
                    jethro.position.y -= (jethro.direction.y * speed * dt);
                }
            }
        }
    }
}

void Game::Draw() {
    if(running) {
        BeginMode2D(camera);
        if(level1Running) {
            tileset.DrawTileMap(level1Tileset, level1Data, tileSize, tileSize, tileColumns, zoom);
            /*for(auto &r : level1Collisions) {
                DrawRectangleLinesEx({r.x, r.y, r.width, r.height}, 1.0f, RED);
                }*/
        }
        else if(level2Running) {
            tileset2.DrawTileMap(level2Tileset, level2Data, tileSize, tileSize, tileColumns2, zoom);
            DrawTextureEx(powerCell, {28 * tileSize * zoom, 18 * tileSize * zoom}, 0, zoom, WHITE);
            /*for(auto &r : level2Collisions) {
                DrawRectangleLinesEx({r.x, r.y, r.width, r.height}, 1.0f, RED);
                }*/
            DrawRectangleLinesEx({powerCellRec.x, powerCellRec.y, powerCellRec.width, powerCellRec.height}, 2, GREEN);
        }
        jethro.Draw();
        //DrawRectangleLinesEx({jethro.collisionBox.x, jethro.collisionBox.y, jethro.collisionBox.width, jethro.collisionBox.height}, 1.0f, GREEN);
        EndMode2D();
    }
    else {
        std::this_thread::sleep_for(std::chrono::milliseconds(1500));
        MeasureText("You Won!", 80);
        DrawTextEx(gameFont, "You Won!", {(GetScreenWidth() - MeasureTextEx(gameFont, "You Won!", 80, 2).x) / 2, (float)((GetScreenHeight() - 80) / 2)}, 80, 3, WHITE);
    }
    if(!keyPressed) {
    #ifdef PLATFORM_DESKTOP
        DrawRectangleRounded({15, 15, GetScreenWidth() - 30.0f, GetScreenHeight() - 30.0f}, 0.25f, 8, Fade(DARKGRAY, 0.8f));
        DrawTextEx(gameFont, "Use WASD to move, E to interact", {(GetScreenWidth() - MeasureTextEx(gameFont, "Use WASD to move, E to interact", 40, 2).x) / 2, (float)((GetScreenHeight() - 40) / 2)}, 40, 3, WHITE);
        DrawTextEx(gameFont, "Press E to start", {(GetScreenWidth() - MeasureTextEx(gameFont, "Press E to start", 30, 2).x) / 2, (float)((GetScreenHeight() + 40) / 2)}, 30, 2, WHITE);
    #endif
    #ifdef PLATFORM_WEB
        DrawRectangleRounded({15, 15, GetScreenWidth() - 30.0f, GetScreenHeight() - 30.0f}, 0.25f, 8, Fade(DARKGRAY, 0.8f));
        DrawTextEx(gameFont, "Use WASD to move, E to interact", {(1280 - MeasureTextEx(gameFont, "Use WASD to move, E to interact", 40, 2).x) / 2, (float)((900 - 40) / 2)}, 40, 3, WHITE);
        DrawTextEx(gameFont, "Press E to start", {(1280 - MeasureTextEx(gameFont, "Press E to start", 30, 2).x) / 2, (float)((900 + 40) / 2)}, 30, 2, WHITE);
    #endif
        if(IsKeyDown(KEY_E)) {
            keyPressed = true;
        }
    }
}

void Game::InitLevel2() {
    UnloadTexture(level1Tileset);
    musicTimer.Deactivate();
    UnloadMusicStream(music);
    //level2Tileset = LoadTexture("../../../graphics/tiles/Level2Tileset.png");
    //music2 = LoadMusicStream("../../../audio/Bossmusic2.wav");
    level2Ready = true;
}

#include "game.h"
#include "raymath.h"

Game::Game() {
    running = true;
    camera.zoom = 2;
    camera.offset = {GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};
    camera.rotation = 0;
    camera.target = {jethro.position.x + jethro.source.width / 2, jethro.position.y + jethro.source.height / 2};
    PlayMusicStream(music);
}

void Game::Update(float deltaTime) {
    if(running) {
        jethro.Update(deltaTime, speed);
        if(level1Running) {
            musicTimer.Update();
            UpdateMusicStream(music);
            CollisionCheck(level1Collisions, 'x');
            CollisionCheck(level1Collisions, 'y');
            if(CheckCollisionRecs(doorRec, jethro.collisionBox) && IsKeyDown(KEY_E)) {
                level1Running = false;
                std::this_thread::sleep_for(std::chrono::milliseconds(1500));
                level2Running = true;
            }
        else if(level2Running) {
            if(!musicTimer2.active) {
                musicTimer2.Activate();
                PlayMusicStream(music2);
            }
            
            UpdateMusicStream(music2);
            //CollisionCheck(level2Collisions, 'x');
            //CollisionCheck(level2Collisions, 'y');
            
        }
        }
        if(!Vector2Equals(jethro.directionState, jethro.direction)) {
            jethro.AnimationCheck();
            jethro.directionState = jethro.direction;
        }
        animationTimer.Update();
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
            for(auto &r : level2Collisions) {
                DrawRectangleLinesEx({r.x, r.y, r.width, r.height}, 1.0f, RED);
            }
            if(IsKeyDown(KEY_E)) {
                for(auto &s : level2Collisions) {
                    if(CheckCollisionRecs(jethro.collisionBox, s)) {
                        std::cout << s.x / zoom << ", " << s.y / zoom << s.width << s.height << "\n";
                    }
                    else std::cout << jethro.collisionBox.x << ", " << jethro.collisionBox.y << " \n";
                }
            }
        }
        jethro.Draw();
        DrawRectangleLinesEx({jethro.position.x, jethro.position.y, (float)(32 * zoom / playerScale), (float)(32 * zoom / playerScale)}, 1.0f, GREEN);
        camera.target = {jethro.position.x + jethro.source.width / 2, jethro.position.y + jethro.source.height / 2};
        EndMode2D();
    }
}

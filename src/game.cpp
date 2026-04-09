#include "game.h"
#include "raymath.h"

Game::Game() {
    running = true;
    camera.zoom = 2;
    camera.offset = {GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};
    camera.rotation = 0;
    camera.target.x = static_cast<float>(int(jethro.position.x + jethro.source.width / 2));
    camera.target.y = static_cast<float>(int(jethro.position.y + jethro.source.height / 2));
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
                jethro.position = {28 * tileSize * zoom, 18 * tileSize * zoom};
                //jethro.position = {16.75f * tileSize * zoom, 2.0f * tileSize * zoom};
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
            DrawTextureEx(powerCell, {28 * tileSize * zoom, 18 * tileSize * zoom}, 0, zoom, WHITE);
            /*for(auto &r : level2Collisions) {
                DrawRectangleLinesEx({r.x, r.y, r.width, r.height}, 1.0f, RED);
            }*/
        }
        jethro.Draw();
        //DrawRectangleLinesEx({jethro.collisionBox.x, jethro.collisionBox.y, jethro.collisionBox.width, jethro.collisionBox.height}, 1.0f, GREEN);
        camera.target = {static_cast<float>(int(jethro.position.x + jethro.source.width / 2)),
            static_cast<float>(int(jethro.position.y + jethro.source.height / 2))};
        EndMode2D();
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

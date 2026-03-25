#pragma once
#include <raylib.h>
#include <jethro.h>
#include <tileset.h>
#include <raymath.h>
#include <chrono>
#include <thread>

class Game {
public:
    bool running;
    float zoom = 4.0f;
    float playerScale = 2;
    bool level1Running = true;
    bool level2Running = false;

    float speed = 300;

    Jethro jethro = Jethro(LoadTexture("../../../graphics/MainCharacter.png"), {0, 13, 32, 35}, {15 * zoom, 19 * zoom}, {0, 0}, 0.0f, zoom / playerScale, WHITE, {0, 0});
    Timer animationTimer = Timer(1.0f, true, true, [&](){jethro.AnimationCheck();});

    Texture2D level1Tileset = LoadTexture("../../../graphics/tiles/WallTilesComplete.png");
    Texture2D level2Tileset = LoadTexture("../../../graphics/tiles/Level2.png");

    Tileset tileset;
    Tileset tileset2;
    Camera2D camera = Camera2D();
    Music music = LoadMusicStream("../../../audio/Music.wav");
    Music music2 = LoadMusicStream("../../../audio/bossmusic.wav");
    Timer musicTimer = Timer(14.0f, true, true, [&](){PlayMusicStream(music);});
    Timer musicTimer2 = Timer(18.0f, true, false, [&](){PlayMusicStream(music2);});

    Game();
    
    void Update(float deltaTime);
    void CollisionCheck(std::vector<Rectangle> collision, char axis);
    void Draw();
    void Start();
    void Stop();
private:
    std::vector<std::vector<int>> level1Data = {
        {1, 4, 3, 19, 1, 2, 7},
        {8, 18, 17, 19, 8, 9, 10},
        {8, 10, 19, 19, 8, 18, 17},
        {8, 10, 19, 19, 8, 10, 19},
        {8, 10, 19, 6, 5, 12, 3},
        {8, 10, 19, 8, 9, 9, 10},
        {8, 10, 19, 8, 9, 13, 14},
        {8, 12, 2, 5, 9, 20, 21},
        {15, 16, 16, 16, 16, 16, 17}
    };

    std::vector<Rectangle> level1Collisions = {
        {zoom * 0, zoom * 0, zoom * 224, zoom * 18},
        {zoom * 0, zoom * 18, zoom * 7, zoom * 251},
        {zoom * 217, zoom * 18, zoom * 7, zoom * 251},
        {zoom * 0, zoom * 269, zoom * 224, zoom * 19},
        {zoom * 185, zoom * 77, zoom * 32, zoom * 69},
        {zoom * 89, zoom * 18, zoom * 46, zoom * 128},
        {zoom * 57, zoom * 45, zoom * 32, zoom * 197},
        {zoom * 89, zoom * 146, zoom * 14, zoom * 96},
        {zoom * 192, zoom * 18, zoom * 25, zoom * 4}
    };
    
    std::vector<std::vector<int>> level2Data = {
        //pull from first array
    };
    
    std::vector<Rectangle> level2Collisions = {
        //{x, y, width, height} 
    };

    int tileSize = 32;
    int tileColumns = level1Tileset.width / tileSize;
    int tileColumns2 = level2Tileset.width / tileSize;

    Rectangle doorRec = {zoom * 43, zoom * 5, zoom * 11, zoom * 18};
};
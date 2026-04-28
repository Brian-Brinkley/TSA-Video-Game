#pragma once
#include <raylib.h>
#include <jethro.h>
#include <tileset.h>
#include <raymath.h>
#include <chrono>
#include <thread>
#include <iostream>

class Game {
public:
    bool running;
    float zoom = 4.0f;
    float playerScale = 2;
    bool level1Running = true;
    bool level2Running = false;
    bool level2Ready = false;

    float speed = 300;

    Jethro jethro = Jethro(LoadTexture("../../../graphics/MainCharacter.png"), {0, 13, 32, 35}, {6 * 32 * zoom, 1 * 32 * zoom}, {0, 0}, 0.0f, zoom / playerScale, WHITE, {0, 0});
    Timer animationTimer = Timer(1.0f, true, true, [&](){jethro.AnimationCheck();});

    Texture2D level1Tileset = LoadTexture("../../../graphics/tiles/WallTilesComplete.png");
    Texture2D level2Tileset = LoadTexture("../../../graphics/tiles/Level2Tileset.png");
    Texture2D powerCell = LoadTexture("../../../graphics/tiles/PowerCell.png");
    Font gameFont = LoadFont("../../../font/Snowbell.ttf");

    Tileset tileset;
    Tileset tileset2;
    Camera2D camera = Camera2D();
    Music music = LoadMusicStream("../../../audio/Music.wav");
    Music music2 = LoadMusicStream("../../../audio/Bossmusic2.wav");
    Timer musicTimer = Timer(13.0f, true, true, [&](){PlayMusicStream(music);});
    Timer musicTimer2 = Timer(29.0f, true, false, [&](){PlayMusicStream(music2);});

    Game();
    
    void Update(float deltaTime);
    void CollisionCheck(std::vector<Rectangle> collision, char axis);
    void Draw();
    void Start();
    void Stop();
    void InitLevel2();
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
        {6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 4, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
        {25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 13, 14, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25},
        {11, 11, 11, 11, 11, 11, 1, 2, 2, 24, 1, 2, 2, 2, 24, 11, 22, 23, 24, 11, 1, 20, 20, 20, 20, 20, 20, 20, 20, 17, 2, 2, 2, 2, 2, 17, 2, 2, 2, 3},
        {11, 11, 11, 11, 11, 11, 10, 11, 11, 10, 10, 11, 11, 11, 10, 11, 11, 11, 10, 11, 10, 11, 11, 11, 11, 11, 11, 11, 11, 10, 11, 11, 11, 11, 11, 7, 3, 11, 11, 12},
        {11, 1, 2, 2, 2, 2, 26, 3, 11, 10, 10, 15, 2, 11, 10, 11, 11, 11, 10, 11, 7, 20, 20, 20, 24, 15, 2, 2, 2, 9, 11, 11, 11, 11, 11, 10, 12, 11, 11, 12},
        {11, 10, 11, 11, 11, 11, 10, 12, 11, 10, 10, 12, 11, 11, 10, 11, 11, 11, 10, 11, 19, 3, 11, 1, 26, 21, 11, 11, 11, 11, 1, 2, 2, 3, 11, 10, 12, 11, 11, 12},
        {11, 10, 11, 11, 12, 11, 10, 12, 11, 19, 9, 12, 11, 11, 10, 11, 11, 11, 10, 11, 11, 12, 11, 10, 19, 3, 11, 11, 11, 11, 10, 11, 11, 12, 11, 10, 8, 3, 11, 12},
        {11, 19, 20, 20, 21, 11, 10, 8, 20, 20, 20, 21, 11, 1, 18, 20, 20, 20, 26, 20, 20, 21, 11, 10, 11, 8, 24, 11, 11, 11, 10, 11, 1, 21, 11, 10, 11, 12, 11, 12},
        {11, 11, 11, 11, 11, 11, 7, 2, 2, 2, 2, 24, 11, 10, 11, 11, 11, 11, 10, 11, 11, 11, 11, 10, 11, 11, 19, 3, 11, 1, 9, 11, 10, 11, 11, 10, 11, 12, 11, 12},
        {11, 1, 2, 2, 2, 17, 9, 11, 11, 11, 11, 10, 11, 10, 11, 11, 11, 11, 19, 20, 20, 20, 20, 26, 20, 3, 11, 12, 11, 10, 11, 11, 10, 11, 11, 10, 1, 21, 11, 12},
        {11, 19, 3, 11, 11, 10, 11, 11, 11, 11, 11, 7, 20, 26, 2, 2, 2, 3, 11, 11, 11, 11, 11, 10, 11, 8, 20, 21, 11, 10, 11, 11, 19, 20, 20, 9, 10, 11, 11, 12},
        {11, 11, 12, 11, 11, 10, 11, 11, 11, 11, 11, 10, 11, 19, 20, 20, 20, 8, 20, 20, 20, 20, 20, 26, 2, 3, 11, 11, 11, 19, 20, 3, 11, 11, 11, 11, 10, 11, 11, 12},
        {11, 11, 12, 11, 11, 19, 20, 20, 20, 20, 3, 10, 11, 1, 20, 20, 20, 20, 20, 20, 3, 11, 11, 10, 1, 21, 11, 1, 20, 20, 20, 16, 11, 11, 12, 11, 10, 11, 11, 12},
        {11, 11, 12, 11, 11, 11, 11, 11, 11, 11, 12, 10, 11, 10, 1, 20, 20, 20, 20, 20, 21, 11, 11, 10, 10, 11, 11, 10, 11, 11, 11, 8, 20, 17, 21, 11, 19, 2, 2, 16},
        {11, 11, 12, 11, 11, 11, 11, 1, 20, 20, 21, 10, 11, 10, 10, 11, 11, 11, 11, 11, 11, 11, 1, 9, 10, 11, 11, 10, 11, 11, 11, 11, 11, 10, 11, 11, 11, 11, 1, 21},
        {11, 11, 12, 11, 11, 11, 11, 10, 1, 20, 20, 9, 11, 10, 19, 20, 20, 20, 20, 20, 20, 3, 10, 11, 19, 20, 20, 9, 15, 20, 17, 20, 3, 10, 12, 11, 11, 1, 9, 11},
        {11, 11, 12, 11, 11, 1, 3, 10, 10, 11, 11, 11, 11, 10, 11, 11, 11, 11, 11, 11, 11, 12, 10, 11, 11, 11, 11, 15, 21, 11, 10, 11, 8, 9, 12, 12, 1, 9, 11, 11},
        {1, 2, 21, 11, 11, 10, 8, 9, 19, 20, 20, 3, 11, 19, 20, 20, 20, 20, 20, 20, 11, 12, 19, 20, 20, 17, 20, 21, 11, 11, 10, 11, 11, 11, 12, 12, 19, 3, 11, 11},
        {10, 11, 11, 11, 11, 19, 20, 20, 20, 20, 24, 8, 20, 11, 11, 11, 11, 11, 11, 11, 11, 12, 11, 11, 11, 10, 11, 11, 10, 11, 19, 20, 17, 20, 21, 12, 11, 12, 11, 11},
        {19, 20, 20, 20, 20, 20, 20, 20, 20, 20, 18, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 21, 11, 11, 20, 9, 11, 11, 19, 20, 20, 20, 18, 20, 20, 21, 11, 8, 20, 3}
    };

    std::vector<Rectangle> level2Collisions = {
        //{x, y, width, height}
        {zoom * 463, zoom * 75, zoom * 75, zoom * 160},
        {zoom * 538, zoom * 88, zoom * 40, zoom * 147},
        {zoom * 591, zoom * 75, zoom * 51, zoom * 160},
        {zoom * 642, zoom * 184, zoom * 47, zoom * 51},
        {zoom * 655, zoom * 88, zoom * 275, zoom * 51},
        {zoom * 783, zoom * 139, zoom * 34, zoom * 32},
        {zoom * 943, zoom * 88, zoom * 179, zoom * 83},
        {zoom * 1086, zoom * 171, zoom * 36, zoom * 160},
        {zoom * 1039, zoom * 248, zoom * 47, zoom * 83},
        {zoom * 1135, zoom * 120, zoom * 19, zoom * 392},
        {zoom * 1154, zoom * 120, zoom * 15, zoom * 179},
        {zoom * 1169, zoom * 216, zoom * 32, zoom * 83},
        {zoom * 1135, zoom * 88, zoom * 130, zoom * 19},
        {zoom * 830, zoom * 152, zoom * 132, zoom * 83},
        {zoom * 847, zoom * 235, zoom * 115, zoom * 32},
        {zoom * 783, zoom * 184, zoom * 47, zoom * 19},
        {zoom * 1182, zoom * 107, zoom * 83, zoom * 96},
        {zoom * 1214, zoom * 203, zoom * 51, zoom * 224},
        {zoom * 1168, zoom * 312, zoom * 46, zoom * 115},
        {zoom * 1154, zoom * 440, zoom * 111, zoom * 19},
        {zoom * 1154, zoom * 459, zoom * 64, zoom * 32},
        {zoom * 1154, zoom * 491, zoom * 32, zoom * 32},
        {zoom * 1231, zoom * 472, zoom * 49, zoom * 72},
        {zoom * 1231, zoom * 544, zoom * 49, zoom * 75},
        {zoom * 1214, zoom * 504, zoom * 17, zoom * 115},
        {zoom * 1199, zoom * 504, zoom * 14, zoom * 51},
        {zoom * 1167, zoom * 536, zoom * 32, zoom * 19},
        {zoom * 1150, zoom * 511, zoom * 4, zoom * 129},
        {zoom * 1154, zoom * 568, zoom * 47, zoom * 72},
        {zoom * 1201, zoom * 632, zoom * 64, zoom * 8},
        {zoom * 1278, zoom * 619, zoom * 2, zoom * 21},
        {zoom * 1278, zoom * 64, zoom * 2, zoom * 408},
        {zoom * 0, zoom * 632, zoom * 11450, zoom * 8},
        {zoom * 1039, zoom * 600, zoom * 98, zoom * 19},
        {zoom * 1118, zoom * 344, zoom * 19, zoom * 256},
        {zoom * 0, zoom * 344, zoom * 81, zoom * 211},
        {zoom * 0, zoom * 0, zoom * 1280, zoom * 64},
        {zoom * 0, zoom * 64, zoom * 194, zoom * 75},
        {zoom * 194, zoom * 64, zoom * 344, zoom * 11},
        {zoom * 550, zoom * 64, zoom * 728, zoom * 11},
        {zoom * 0, zoom * 139, zoom * 34, zoom * 205},
        {zoom * 0, zoom * 555, zoom * 2, zoom * 78},
        {zoom * 207, zoom * 88, zoom * 83, zoom * 51},
        {zoom * 254, zoom * 139, zoom * 36, zoom * 96},
        {zoom * 15, zoom * 568, zoom * 147, zoom * 51},
        {zoom * 162, zoom * 600, zoom * 160, zoom * 19},
        {zoom * 94, zoom * 312, zoom * 68, zoom * 256},
        {zoom * 47, zoom * 312, zoom * 47, zoom * 19},
        {zoom * 47, zoom * 152, zoom * 98, zoom * 83},
        {zoom * 34, zoom * 248, zoom * 160, zoom * 51},
        {zoom * 145, zoom * 152, zoom * 49, zoom * 40},
        {zoom * 158, zoom * 192, zoom * 36, zoom * 55},
        {zoom * 655, zoom * 152, zoom * 115, zoom * 19},
        {zoom * 702, zoom * 171, zoom * 36, zoom * 128},
        {zoom * 591, zoom * 248, zoom * 111, zoom * 51},
        {zoom * 574, zoom * 312, zoom * 164, zoom * 51},
        {zoom * 431, zoom * 248, zoom * 147, zoom * 83},
        {zoom * 162, zoom * 408, zoom * 175, zoom * 51},
        {zoom * 162, zoom * 459, zoom * 64, zoom * 64},
        {zoom * 222, zoom * 523, zoom * 4, zoom * 32},
        {zoom * 303, zoom * 75, zoom * 19, zoom * 128},
        {zoom * 208, zoom * 1552, zoom * 34, zoom * 115},
        {zoom * 241, zoom * 248, zoom * 177, zoom * 19},
        {zoom * 175, zoom * 312, zoom * 32, zoom * 83},
        {zoom * 207, zoom * 280, zoom * 147, zoom * 115},
        {zoom * 350, zoom * 395, zoom * 4, zoom * 77},
        {zoom * 239, zoom * 472, zoom * 115, zoom * 19},
        {zoom * 175, zoom * 568, zoom * 194, zoom * 19},
        {zoom * 175, zoom * 536, zoom * 34, zoom * 32},
        {zoom * 239, zoom * 491, zoom * 19, zoom * 77},
        {zoom * 367, zoom * 267, zoom * 51, zoom * 64},
        {zoom * 335, zoom * 88, zoom * 115, zoom * 51},
        {zoom * 382, zoom * 152, zoom * 68, zoom * 83},
        {zoom * 416, zoom * 139, zoom * 34, zoom * 13},
        {zoom * 382, zoom * 235, zoom * 36, zoom * 13},
        {zoom * 335, zoom * 139, zoom * 34, zoom * 96},
        {zoom * 290, zoom * 216, zoom * 45, zoom * 19},
        {zoom * 271, zoom * 504, zoom * 147, zoom * 51},
        {zoom * 382, zoom * 555, zoom * 36, zoom * 32},
        {zoom * 335, zoom * 587, zoom * 34, zoom * 32},
        {zoom * 369, zoom * 600, zoom * 320, zoom * 19},
        {zoom * 416, zoom * 568, zoom * 273, zoom * 32},
        {zoom * 367, zoom * 344, zoom * 51, zoom * 160},
        {zoom * 431, zoom * 344, zoom * 130, zoom * 19},
        {zoom * 418, zoom * 376, zoom * 320, zoom * 19},
        {zoom * 544, zoom * 363, zoom * 17, zoom * 13},
        {zoom * 640, zoom * 504, zoom * 48, zoom * 64},
        {zoom * 431, zoom * 504, zoom * 209, zoom * 51},
        {zoom * 431, zoom * 408, zoom * 19, zoom * 96},
        {zoom * 450, zoom * 408, zoom * 207, zoom * 19},
        {zoom * 670, zoom * 395, zoom * 68, zoom * 64},
        {zoom * 463, zoom * 440, zoom * 243, zoom * 51},
        {zoom * 702, zoom * 491, zoom * 4, zoom * 77},
        {zoom * 702, zoom * 568, zoom * 100, zoom * 51},
        {zoom * 702, zoom * 618, zoom * 66, zoom * 14},
        {zoom * 815, zoom  * 568, zoom * 83, zoom * 64},
        {zoom * 926, zoom * 504, zoom * 36, zoom * 115},
        {zoom * 894, zoom * 536, zoom * 32, zoom * 40},
        {zoom * 911, zoom * 576, zoom * 15, zoom * 43},
        {zoom * 962, zoom * 600, zoom * 64, zoom * 19},
        {zoom * 751, zoom * 376, zoom * 19, zoom * 179},
        {zoom * 770, zoom * 376, zoom * 47, zoom * 19},
        {zoom * 719, zoom * 472, zoom * 32, zoom * 83},
        {zoom * 751, zoom * 184, zoom * 19, zoom * 115},
        {zoom * 770, zoom * 216, zoom * 47, zoom * 83},
        {zoom * 817, zoom * 248, zoom * 17, zoom * 51},
        {zoom * 830, zoom * 280, zoom * 51, zoom * 51},
        {zoom * 751, zoom * 312, zoom * 66, zoom * 51},
        {zoom * 817, zoom * 344, zoom * 113, zoom * 19},
        {zoom * 894, zoom * 267, zoom * 36, zoom * 77},
        {zoom * 975, zoom * 184, zoom * 98, zoom * 51},
        {zoom * 943, zoom * 280, zoom * 32, zoom * 83},
        {zoom * 975, zoom * 235, zoom * 51, zoom * 128},
        {zoom * 1022, zoom * 344, zoom * 83, zoom * 83},
        {zoom * 1105, zoom * 344, zoom * 13, zoom * 40},
        {zoom * 830, zoom * 376, zoom * 179, zoom * 19},
        {zoom * 830, zoom * 363, zoom * 100, zoom * 13},
        {zoom * 830, zoom * 395, zoom * 36, zoom * 13},
        {zoom * 783, zoom * 408, zoom * 83, zoom * 83},
        {zoom * 1054, zoom * 440, zoom * 4, zoom * 83},
        {zoom * 770, zoom * 504, zoom * 111, zoom * 51},
        {zoom * 1071, zoom * 440, zoom * 47, zoom * 40},
        {zoom * 1071, zoom * 480, zoom * 34, zoom * 107},
        {zoom * 975, zoom * 504, zoom * 66, zoom * 83},
        {zoom * 1041, zoom * 536, zoom * 30, zoom * 51},
        {zoom * 879, zoom *  408, zoom * 34, zoom * 115},
        {zoom * 913, zoom * 408, zoom * 96, zoom * 32},
        {zoom * 913, zoom * 440, zoom * 141, zoom * 51}
    };
    
    int tileSize = 32;
    int tileColumns = level1Tileset.width / tileSize;
    int tileColumns2 = level2Tileset.width / tileSize;

    Rectangle doorRec = {zoom * 43, zoom * 5, zoom * 11, zoom * 18};

    Rectangle powerCellRec = {zoom * 898, zoom * 18 * tileSize, zoom * 13, zoom * 14};

};
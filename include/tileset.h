#pragma once
#include "raylib.h"
#include <vector>

class Tileset {
public:
    void DrawTileMap(Texture2D tileset,
                    const std::vector<std::vector<int>>& map,
                    int tileWidth,
                    int tileHeight,
                    int tilesetColums,
                    float scale = 1,
                    int offsetX = 0,
                    int offsetY = 0) {
                for(int y = 0; y < map.size(); y++) {
                    for(int x=0; x < map[y].size(); x++) {
                        int tileID = map[y][x];
                        
                        tileID -= 1;
                        if(tileID < 0) continue;

                        int srcX = (tileID % tilesetColums) * tileWidth;
                        int srcY = (tileID / tilesetColums) * tileHeight;

                        Rectangle source = {
                            (float)(srcX),
                            (float)(srcY),
                            (float)tileWidth,
                            (float)tileHeight
                        };

                        Rectangle dest = {
                            static_cast<float>(int(x * tileWidth * scale + offsetX)),
                            static_cast<float>(int(y * tileHeight * scale + offsetY)),
                            static_cast<float>(int(tileWidth * scale)),
                            static_cast<float>(int(tileHeight * scale))
                        };
                        DrawTexturePro(tileset, source, dest, {0, 0}, 0.0f, WHITE);
                }
            }
    }
};

class Level {
public:
    std::vector<Rectangle> collisions;
    std::vector<std::vector<int>> map;
    int tileWidth;
    int tileHeight;
    int tilesetColumns;
    float scale;
    int offsetX;
    int offsetY;

    Level(std::vector<Rectangle> collisions,
        std::vector<std::vector<int>> map,
        int tileWidth,
        int tileHeight,
        int tilesetColumns,
        float scale = 1,
        int offsetX = 0,
        int offsetY = 0) {
            this->collisions = collisions;
            this->map = map;
            this->tileWidth = tileWidth;
            this->tileHeight = tileHeight;
            this->tilesetColumns = tilesetColumns;
            this->scale = scale;
            this->offsetX = offsetX;
            this->offsetY = offsetY;
        }
};
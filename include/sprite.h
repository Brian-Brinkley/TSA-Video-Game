#pragma once
#include "raylib.h"

#pragma once
class Sprite {
public:
    Texture2D texture;
    Vector2 position;
    Rectangle source;
    Vector2 origin;
    float rotation;
    float scale;
    Color tint;
    Vector2 direction;
    double dt;

    Sprite(Texture2D texture, Rectangle source, Vector2 position, Vector2 origin, float rotation, float scale, Color tint, Vector2 direction) {
        this->texture = texture;
        this->source = source;
        this->position = position;
        this->origin = origin;
        this->rotation = rotation;
        this->scale = scale;
        this->tint = tint;
        this->direction = direction;
    }

    void Draw();

    void Move(double dt);


};
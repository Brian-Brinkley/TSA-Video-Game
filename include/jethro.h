#pragma once
#include "sprite.h"
#include "timer.h"

class Jethro : public Sprite {
public:
    Rectangle collisionBox;
    bool animationFrame = true;
    Vector2 directionState = direction;

    Jethro(Texture2D texture, Rectangle source, Vector2 position, Vector2 origin, float rotation, float scale, Color tint, Vector2 direction);
    void Update(double dt, float speed);
    void Input();
    void DirectionCheck();
    void AnimationCheck();
};
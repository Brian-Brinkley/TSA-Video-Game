#include "sprite.h"
#include "jethro.h"
#include "raymath.h"


Jethro::Jethro(Texture2D texture, Rectangle source, Vector2 position, Vector2 origin, float rotation, float scale, Color tint, Vector2 direction)
    : Sprite(texture, source, position, origin, rotation, scale, tint, direction) {
        this->texture = texture;
        this->source = source;
        this->position = position;
        this->origin = origin;
        this->rotation = rotation;
        this->scale = scale;
        this->tint = tint;
        this->direction = direction;
}

void Jethro::Input() {
    direction.x = (int)(IsKeyDown(KEY_D) - IsKeyDown(KEY_A));
    direction.y = (int)(IsKeyDown(KEY_S) - IsKeyDown(KEY_W));
    if(direction.x != 0 && direction.y != 0) {
        direction = Vector2Normalize(direction);
    }
}

void Jethro::Update(double dt, float speed) {
    Input();
    Move(dt);
    collisionBox = {position.x + 6, position.y, (source.width - 6) * scale, (source.height - 3) * scale};
}

void Jethro::DirectionCheck() {
    if(direction.y < 0 && direction.x == 0){
        source.x = 96;
        source.y = 13;
    }
    else if(direction.x < 0){
        source.x = 0;
        source.y = 61;
    }
    else if(direction.x > 0){
        source.x = 96;
        source.y = 61;
    }
    else{
        source.x = 0;
        source.y = 13;
    }
}

void Jethro::AnimationCheck() {
    if(direction.x != 0 || direction.y != 0) {
        if(direction.y < 0 && direction.x ==0) {
            if(animationFrame) {
                source.x = 128;
                source.y = 13;
                animationFrame = !animationFrame;
                return;
            }
            else {
                source.x = 160;
                source.y = 13;
                animationFrame = !animationFrame;
                return;
            }
        }
        else if(direction.x < 0) {
            if(animationFrame) {
                source.x = 32;
                source.y = 61;
                animationFrame = !animationFrame;
                return;
            }
            else {
                source.x = 64;
                source.y = 61;
                animationFrame = !animationFrame;
                return;
            }
        }
        else if(direction.x > 0) {
            if(animationFrame) {
                source.x = 128;
                source.y = 61;
                animationFrame = !animationFrame;
                return;
            }
            else {
                source.x = 160;
                source.y = 61;
                animationFrame = !animationFrame;
                return;
            }
        }
        else {
            if(animationFrame) {
                source.x = 32;
                source.y = 13;
                animationFrame = !animationFrame;
                return;
            }
            else {
                source.x = 64;
                source.y = 13;
                animationFrame = !animationFrame;
                return;
            }
        }
    }
    else {
        source.x = 0;
        source.y = 13;
        return;
    }

}

#include "sprite.h"

float speed = 300.0f;

void Sprite::Draw() {
    DrawTexturePro(texture, source, {position.x, position.y, 32 * scale, 48 * scale}, {0, 16 * scale}, rotation, tint);
}

void Sprite::Move(double dt) {
    position.x += static_cast<float>(int(direction.x * speed * dt));
    position.y += static_cast<float>(int(direction.y * speed * dt));
}
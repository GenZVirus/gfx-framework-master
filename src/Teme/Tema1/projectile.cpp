#include "projectile.h"

//Projectile Implementation

Projectile::Projectile(float posX, float posY, int mouseX, int mouseY) {
    PosX = posX;
    PosY = posY;
    lifeSpan = 1000;
    int projectileSpeed = 10;
    float vecX = mouseX - PosX;
    float vecY = -mouseY + PosY;
    float mag = sqrt(vecX * vecX + vecY * vecY) / projectileSpeed;
    if (mag != 0)
        forward = glm::vec2(vecX / mag, vecY / mag);
    angle = -atan2f(mouseY - PosY, mouseX - PosX);
    collisionPoints.push_back(glm::vec2(0, 0));
    collisionPoints.push_back(glm::vec2(0, 16));
    collisionPoints.push_back(glm::vec2(64, 16));
    collisionPoints.push_back(glm::vec2(64, 0));
}

Projectile::~Projectile() {

}

void Projectile::Update(float deltaTimeSeconds) {
    lifeSpan--;
    moveForward();
}

void Projectile::moveForward() {
    PosX += forward.x;
    PosY += forward.y;
}

float Projectile::getPosX() {
    return PosX;
}

float Projectile::getPosY() {
    return PosY;
}

void Projectile::addToPosX(int x) {
    PosX += x;
}

void Projectile::addToPosY(int y) {
    PosY += y;
}

void Projectile::onCollision() {
    lifeSpan = 0;
}


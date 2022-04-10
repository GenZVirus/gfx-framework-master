#include "enemy.h"
#include "teme/Tema1/Tema1.h"
#include <iostream>

using namespace std;
//Enemy Implementation

Enemy::Enemy(float posX, float posY, int sizeIn) {

    isColliding = false;
    cooldown = 1;
    size = sizeIn;
    stop = false;
    PosX = posX;
    PosY = posY;
    collisionPoints.push_back(glm::vec2(0, 0));
    collisionPoints.push_back(glm::vec2(0, size));
    collisionPoints.push_back(glm::vec2(size, size));
    collisionPoints.push_back(glm::vec2(size, 0));
}
Enemy::~Enemy() {

}

void Enemy::Update(float deltaTimeSeconds, float playerX, float playerY) {
    if (cooldown > 0)
        cooldown -= deltaTimeSeconds;
    float vecX = playerX - PosX;
    float vecY = playerY - PosY;
    float mag = sqrt(vecX * vecX + vecY * vecY);
    if (mag != 0) {
        vecForward = glm::vec2(vecX / mag, vecY / mag);
    }
}

float Enemy::getPosX() {
    return PosX;
}

float Enemy::getPosY() {
    return PosY;
}

void Enemy::addToPosX(float x) {
    PosX += x;
}

void Enemy::addToPosY(float y) {
    PosY += y;
}

void Enemy::move() {
    PosX += vecForward.x * 2;
    PosY += vecForward.y * 2;
}

void Enemy::onColision() {

}

bool Enemy::isCollidingWithEntity(std::list<glm::vec2> entityCP, float entityX, float entityY) {

    std::list<glm::vec2>::iterator itEntity = entityCP.begin();
    int nr = 0;
    while (itEntity != entityCP.end()) {
        float x = entityX + itEntity->x;
        float y = entityY + itEntity->y;
        if (x < size + PosX && x > PosX && y >  PosY && y < size + PosY) {
            return true;
        }
        ++itEntity;
    }
    return false;
}
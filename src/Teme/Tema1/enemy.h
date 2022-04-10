#pragma once

#include "components/simple_scene.h"

class Enemy {
public:
    Enemy(float posX, float posY, int size);
    ~Enemy();

    void Update(float deltaTimeSeconds, float playerX, float playerY);
    float getPosX();
    float getPosY();
    void addToPosX(float x);
    void addToPosY(float y);
    void onColision();
    bool isCollidingWithEntity(std::list<glm::vec2> entityCP, float entityX, float entityY);
    void move();

    std::list<glm::vec2> collisionPoints;
    int currentLife;
    int maxLife;
    bool stop;
    int size;
    float cooldown;
    bool isColliding;
    glm::vec2 vecForward;

protected:
    float PosX, PosY;
};
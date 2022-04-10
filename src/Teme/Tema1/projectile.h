#pragma once

#include "components/simple_scene.h"

class Projectile {
public:
    Projectile(float posX, float posY, int mouseX, int mouseY);
    ~Projectile();

    void Update(float deltaTimeSeconds);
    float getPosX();
    float getPosY();
    void addToPosX(int x);
    void addToPosY(int y);
    void onCollision();
    int lifeSpan;
    float angle;
    std::list<glm::vec2> collisionPoints;

private:
    void moveForward();

protected:

    float PosX, PosY;
    glm::vec2 forward;

};
#pragma once

#include "components/simple_scene.h"
#include "components/transform.h"
#include "components/camera.h"
#include "teme/Tema1/projectile.h"
#include "teme/Tema1/enemy.h"


namespace tema1
{

    class Tema1 : public gfxc::SimpleScene
    {
    public:
        Tema1();
        ~Tema1();

        void Init() override;

    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;
        void RenderMesh2DTextured(Mesh* mesh, Shader* shader, const glm::mat3& modelMatrix, Texture2D* texture1 = NULL, Texture2D* texture2 = NULL);
        int getPixelAt(int x, int y);
        bool isColliding(std::list<glm::vec2> cp, float x, float y);

    protected:


        //Transform (Optional)
        glm::mat3 modelMatrix;
        float translateX, translateY;
        float scaleX, scaleY;
        float angularStep;

        // World Translation
        float WorldPosX, WorldPosY;

        //Character Size
        float xSize, ySize;

        // Player CenterPosition
        float posX;
        float posY;

        // Player Speed
        float movementSpeed;

        gfxc::Camera* camera;
        Texture2D* backgroundTexture;
        Shader* shader;

        std::list<Projectile> projectiles;
        std::list<Enemy> enemies;

        int width, height, channels;
        std::list<glm::vec2> collisionPoints;
        unsigned char* collisionMap;

        float currentHealth;
        float maxHealth;
        float cooldown;

        glm::vec2 Spawner;
    };

}

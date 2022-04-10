#pragma once

#include "components/simple_scene.h"
#include "Teme/Tema2/implemented_camera.h"
#include "Enemy.h"
#include "Particles.h"


namespace tema2
{
    class Tema2 : public gfxc::SimpleScene
    {
    public:
        Tema2();
        ~Tema2();

        void Init() override;

    private:
        void CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned int>& indices);

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
        void RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix) override;
        void RenderTexturedMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, Texture2D* texture = NULL);
        void PlayerRenderer();
        void WorldRenderer();
        void playAnimation(float deltaTimeSeconds);
        int getPixelColor(int x, int y);
        bool isColliding(int x, int z);

    protected:
        int xSize;
        int zSize;
        unsigned char* map;
        int channels;
        std::list<glm::vec3> wallPos, groundPos;
        implemented::MyCamera* camera;
        glm::vec3 cameraPosition;
        glm::mat4 projectionMatrix;
        int FoV;
        glm::vec3 PlayerPosition;
        bool renderCameraTarget;
        float playerRotationY;
        float playerRightHandJoint, playerLeftHandJoint, playerRightLegJoint, playerLeftLegJoint;
        bool reverseAnimation;
        bool isMoving;
        Texture2D* wallTexture, *groundTexture;
        std::list<enemy::Enemy> enemies;
        std::list<particles::Particles> activeParticles;
    };
}

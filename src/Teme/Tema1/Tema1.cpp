#include "teme/Tema1/Tema1.h"

#include <vector>
#include <iostream>
#include <math.h>

#include "stb/stb_image.h"
#include "teme/Tema1/transform2D.h"
#include "teme/Tema1/object2D.h"

using namespace std;
using namespace tema1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema1::Tema1()
{
}


Tema1::~Tema1()
{
}


void Tema1::Init()
{
    // World starting position
    WorldPosX = WorldPosY = 0;
    cooldown = 0;
    Spawner = glm::vec2(700, 600);

    // Camera & Resolution
    glm::ivec2 resolution = window->GetResolution();
    camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    //Player
    {
        maxHealth = currentHealth = 100;

        float playerSize = 100;
        ySize = xSize = playerSize / 2;
        glm::vec3 corner = glm::vec3(0, 0, 0);

        // Initialize tx and ty (the translation steps)
        translateX = 0;
        translateY = 0;

        // Initialize sx and sy (the scale factors)
        scaleX = 1;
        scaleY = 1;

        // Initialize angularStep
        angularStep = 0;

        Mesh* player = object2D::CreateSquare("Player", corner, playerSize, glm::vec3(1, 1, 0), true);
        AddMeshToList(player);

        // Center Player Position
        posX = resolution.x / 2;
        posY = resolution.y / 2;

        collisionPoints.push_back(glm::vec2(0, 0));
        collisionPoints.push_back(glm::vec2(0, playerSize));
        collisionPoints.push_back(glm::vec2(playerSize, playerSize));
        collisionPoints.push_back(glm::vec2(playerSize, 0));

        // Player Speed
        movementSpeed = 3;
    }

    Mesh* healthBar = object2D::CreateRectangle("HealthBar", glm::vec3(0, 0, 0), maxHealth*2, 32, glm::vec3(1, 0, 0), true);
    AddMeshToList(healthBar);
    Mesh* healthBarBorder = object2D::CreateRectangle("HealthBarBorder", glm::vec3(0, 0, 0), maxHealth*2, 32, glm::vec3(1, 0, 0));
    AddMeshToList(healthBarBorder);

    // Projectile mesh
    Mesh* projectile = object2D::CreateRectangle("Projectile", glm::vec3(0, 0, 0), 64, 16, glm::vec3(0, 0, 1), true);
    AddMeshToList(projectile);

    // Enemy mesh
    Mesh* enemy = object2D::CreateSquare("Enemy", glm::vec3(0, 0, 0), 100, glm::vec3(1, 0, 0), true);
    AddMeshToList(enemy);
    Enemy newEnemy = Enemy(700.0f, 600.0f, 100);
    enemies.push_back(newEnemy);

    // World Size
    int backgroundSize = 2048;

    // Create world properties
    {
        vector<glm::vec3> vertices
        {
            glm::vec3(0,   0, 0),    // top right
            glm::vec3(backgroundSize, 0, 0),    // bottom right
            glm::vec3(backgroundSize, backgroundSize, 0),    // bottom left
            glm::vec3(0,  backgroundSize, 0),    // top left
        };

        vector<glm::vec3> normals
        {
            glm::vec3(0, 1, 1),
            glm::vec3(1, 0, 1),
            glm::vec3(1, 0, 0),
            glm::vec3(0, 1, 0)
        };

        vector<glm::vec2> textureCoords
        {
            // TODO(student): Complete texture coordinates for the square
            glm::vec2(1.0f, 0.0f),
            glm::vec2(1.0f, 1.0f),
            glm::vec2(0.0f, 1.0f),
            glm::vec2(0.0f, 0.0f)

        };

        vector<unsigned int> indices =
        {
            0, 1, 3,
            1, 2, 3
        };

        Mesh* worldMesh = new Mesh("background");
        worldMesh->InitFromData(vertices, normals, textureCoords, indices);
        meshes[worldMesh->GetMeshID()] = worldMesh;
    }

    // Create Shader
    {
        shader = new Shader("Tema1");
        shader->AddShader(PATH_JOIN(window->props.selfDir, PATH_JOIN("src", "Teme"), "tema1", "shaders", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, PATH_JOIN("src", "Teme"), "tema1", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
    }

    // Load World Texture
    const string sourceTextureDir = PATH_JOIN(window->props.selfDir, PATH_JOIN("src", "Teme"), "tema1", "textures");
    backgroundTexture = new Texture2D();
    backgroundTexture->Load2D(PATH_JOIN(sourceTextureDir, "background.png").c_str(), GL_REPEAT);

    // Load Collison Map
    collisionMap = stbi_load(PATH_JOIN(sourceTextureDir, "collision_map.png").c_str(), &width, &height, &channels, 0);

}


void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}

void Tema1::Update(float deltaTimeSeconds)
{
    // Player Update
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(posX + xSize, posY + ySize);
    modelMatrix *= transform2D::Rotate(angularStep);
    modelMatrix *= transform2D::Translate(-xSize, -ySize);

    RenderMesh2D(meshes["Player"], shaders["VertexColor"], modelMatrix);

    // Health Bar Update
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(50, window->GetResolution().y - 50);
    RenderMesh2D(meshes["HealthBarBorder"], shaders["VertexColor"], modelMatrix);
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(50, window->GetResolution().y - 50);
    modelMatrix *= transform2D::Scale(currentHealth / maxHealth, 1);
    RenderMesh2D(meshes["HealthBar"], shaders["VertexColor"], modelMatrix);

    // Player Update
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(posX + xSize, posY + ySize);
    modelMatrix *= transform2D::Rotate(angularStep);
    modelMatrix *= transform2D::Translate(-xSize, -ySize);

    RenderMesh2D(meshes["Player"], shaders["VertexColor"], modelMatrix);

    // Projectiles Update
    {
        std::list<Projectile>::iterator it = projectiles.begin();
        while (it != projectiles.end()) {

            it->Update(deltaTimeSeconds);
            if (isColliding(it->collisionPoints, it->getPosX() - WorldPosX, it->getPosY() - WorldPosY)) {
                it->onCollision();
            }
            if (it->lifeSpan == 0) {
                std::list<Projectile>::iterator prev = it++;
                projectiles.erase(prev);
            }
            else {
                modelMatrix = glm::mat3(1);
                modelMatrix *= transform2D::Translate(it->getPosX() + 32, it->getPosY() + 32);
                modelMatrix *= transform2D::Rotate(it->angle);
                modelMatrix *= transform2D::Translate(-32, -32);
                RenderMesh2D(meshes["Projectile"], shaders["VertexColor"], modelMatrix);
                it++;
            }
        }
    }

    // Enemies Update
    {
        std::list<Enemy>::iterator it = enemies.begin();
        while (it != enemies.end()) {
            it->Update(deltaTimeSeconds, posX, posY);
            if (!isColliding(it->collisionPoints, it->vecForward.x/2 + it->getPosX() - WorldPosX, it->vecForward.y/2 + it->getPosY() - WorldPosY)) {
                it->move();
            }
            if (it->isCollidingWithEntity(collisionPoints, posX, posY)) {
                if (currentHealth > 0 && it->cooldown <= 0)
                {
                    currentHealth -= 10;
                    it->cooldown = 1;
                }
            }
            bool check = false;
            std::list<Projectile>::iterator toBeErased;
            std::list<Projectile>::iterator itProjectile = projectiles.begin();
            while (itProjectile != projectiles.end()) {
                if (it->isCollidingWithEntity(itProjectile->collisionPoints, itProjectile->getPosX(), itProjectile->getPosY())) {
                    toBeErased = itProjectile;
                    check = true;
                }
                itProjectile++;
            }
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(it->getPosX(), it->getPosY());
            RenderMesh2D(meshes["Enemy"], shaders["VertexColor"], modelMatrix);
            if (check) {
                std::list<Enemy>::iterator prev = it++;
                enemies.erase(prev);
                projectiles.erase(toBeErased);
            }
            else {
                it++;
            }
        }
    }

    if (cooldown <= 0) {
        cooldown = 3;
        enemies.push_back(Enemy(Spawner.x, Spawner.y, 100));
    }
    else {
        cooldown -= deltaTimeSeconds;
    }

    // World Update
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(WorldPosX, WorldPosY);
    RenderMesh2DTextured(meshes["background"], shader, modelMatrix, backgroundTexture);
    
}

void Tema1::RenderMesh2DTextured(Mesh* mesh, Shader* shader, const glm::mat3& modelMatrix, Texture2D* texture1, Texture2D* texture2)
{
    if (!mesh || !shader || !shader->program)
        return;

    shader->Use();
    glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
    glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetProjectionMatrix()));

    glm::mat3 mm = modelMatrix;
    glm::mat4 model = glm::mat4(
        mm[0][0], mm[0][1], mm[0][2], 0.f,
        mm[1][0], mm[1][1], mm[1][2], 0.f,
        0.f, 0.f, mm[2][2], 0.f,
        mm[2][0], mm[2][1], 0.f, 1.f);

    glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(model));

    if (texture1)
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1->GetTextureID());
        glUniform1i(glGetUniformLocation(shader->GetProgramID(), "texture_1"), 0);
    }

    if (texture2)
    {
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2->GetTextureID());
        glUniform1i(glGetUniformLocation(shader->GetProgramID(), "texture_2"), 1);
    }

    glBindVertexArray(mesh->GetBuffers()->m_VAO);
    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);

}


void Tema1::FrameEnd()
{
}

void Tema1::OnInputUpdate(float deltaTime, int mods)
{
    // Move World on Input
    if(window->KeyHold(GLFW_KEY_W) && !isColliding(collisionPoints, -WorldPosX + posX, -WorldPosY + movementSpeed + posY))
    {
        WorldPosY -= movementSpeed;

        // Projectiles Position Update
        {
            std::list<Projectile>::iterator it = projectiles.begin();
            while (it != projectiles.end()) {
                it++->addToPosY(-movementSpeed);
            }
        }
        Spawner.y -= movementSpeed;

        // Enemies Position Update
        {
            std::list<Enemy>::iterator it = enemies.begin();
            while (it != enemies.end()) {
                it++->addToPosY(-movementSpeed);
            }
        }
    }
    if (window->KeyHold(GLFW_KEY_S) && !isColliding(collisionPoints, -WorldPosX + posX, -WorldPosY - movementSpeed + posY))
    {
        WorldPosY += movementSpeed;
        
        // Projectile Postion Update
        {
            std::list<Projectile>::iterator it = projectiles.begin();
            while (it != projectiles.end()) {
                it++->addToPosY(movementSpeed);
            }
        }

        Spawner.y += movementSpeed;

        // Enemies Position Update
        {
            std::list<Enemy>::iterator it = enemies.begin();
            while (it != enemies.end()) {
                it++->addToPosY(movementSpeed);
            }
        }
    }
    if (window->KeyHold(GLFW_KEY_D) && !isColliding(collisionPoints, -WorldPosX + posX + movementSpeed, -WorldPosY + posY))
    {
        WorldPosX -= movementSpeed;

        // Projectiles Position Update
        {
            std::list<Projectile>::iterator it = projectiles.begin();
            while (it != projectiles.end()) {
                it++->addToPosX(-movementSpeed);
            }
        }

        Spawner.x -= movementSpeed;

        // Enemies Position Update
        {
            std::list<Enemy>::iterator it = enemies.begin();
            while (it != enemies.end()) {
                it++->addToPosX(-movementSpeed);
            }
        }
    }
    if (window->KeyHold(GLFW_KEY_A) && !isColliding(collisionPoints, -WorldPosX + posX - movementSpeed, -WorldPosY + posY))
    {
        WorldPosX += movementSpeed;
        
        // Projectile Position Update
        {
            std::list<Projectile>::iterator it = projectiles.begin();
            while (it != projectiles.end()) {
                it++->addToPosX(movementSpeed);
            }
        }

        Spawner.x += movementSpeed;

        // Enemies Position Update
        {
            std::list<Enemy>::iterator it = enemies.begin();
            while (it != enemies.end()) {
                it++->addToPosX(movementSpeed);
            }
        }
    }

}

bool Tema1::isColliding(std::list<glm::vec2> cp, float x, float y) {
    std::list<glm::vec2>::iterator it = cp.begin();
    while (it != cp.end()) {
        if (getPixelAt(it->x + x, it->y + y) == 0)
            return true;
        it++;
    }
    return false;
}


void Tema1::OnKeyPress(int key, int mods)
{
    // Add key press event
}


void Tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
    float x = mouseX - posX;
    float y = mouseY - posY;
    angularStep = -atan2f(y, x);
}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
    if (button == GLFW_MOUSE_BUTTON_2) {
        projectiles.push_back(Projectile(posX, posY, mouseX, mouseY));
    }
}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema1::OnWindowResize(int width, int height)
{
}

int Tema1::getPixelAt(int x, int y) {
    if (x < 0 || y < 0) return 1;
    unsigned char* pixel = collisionMap + (y * width * 4) + (x * 4);
    return pixel[0] + pixel[1] + pixel[2];
}



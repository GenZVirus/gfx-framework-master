#include "teme/Tema2/Tema2.h"

#include <vector>
#include <iostream>
#include <stdlib.h>

#include "stb/stb_image.h"

using namespace std;
using namespace tema2;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema2::Tema2()
{
    Init();

    // Load Map
    const string sourceTextureDir = PATH_JOIN(window->props.selfDir, PATH_JOIN("src", "Teme"), "tema2", "textures");
    map = stbi_load(PATH_JOIN(sourceTextureDir, "map.png").c_str(), &xSize, &zSize, &channels, 0);

    //Create Character
    {
        //Create Head
        {
            vector<VertexFormat> vertices{
                VertexFormat(glm::vec3(-0.3, -0.3,  0.3), glm::vec3(0, 1, 0), glm::vec3(1, 0.95, 0.90)),
                VertexFormat(glm::vec3( 0.3, -0.3,  0.3), glm::vec3(0, 1, 0), glm::vec3(1, 0.95, 0.90)),
                VertexFormat(glm::vec3( 0.3,  0.3,  0.3), glm::vec3(0, 1, 0), glm::vec3(1, 0.95, 0.90)),
                VertexFormat(glm::vec3(-0.3,  0.3,  0.3), glm::vec3(0, 1, 0), glm::vec3(1, 0.95, 0.90)),

                VertexFormat(glm::vec3(-0.3, -0.3, -0.3), glm::vec3(0, 1, 0), glm::vec3(1, 0.95, 0.90)),
                VertexFormat(glm::vec3( 0.3, -0.3, -0.3), glm::vec3(0, 1, 0), glm::vec3(1, 0.95, 0.90)),
                VertexFormat(glm::vec3( 0.3,  0.3, -0.3), glm::vec3(0, 1, 0), glm::vec3(1, 0.95, 0.90)),
                VertexFormat(glm::vec3(-0.3,  0.3, -0.3), glm::vec3(0, 1, 0), glm::vec3(1, 0.95, 0.90))
            };
            vector<unsigned int> indices =
            {
                // front
                0, 1, 2,
                2, 3, 0,
                // right
                1, 5, 6,
                6, 2, 1,
                // back
                7, 6, 5,
                5, 4, 7,
                // left
                4, 0, 3,
                3, 7, 4,
                // bottom
                4, 5, 1,
                1, 0, 4,
                // top
                3, 2, 6,
                6, 7, 3
            };
            CreateMesh("head", vertices, indices);
        }

        //Create Body
        {
            vector<VertexFormat> vertices{
                VertexFormat(glm::vec3(-0.3, -0.6,  0.2), glm::vec3(0, 1, 0), glm::vec3(0.9, 0.9, 0.9)),
                VertexFormat(glm::vec3( 0.3, -0.6,  0.2), glm::vec3(0, 1, 0), glm::vec3(0.9, 0.9, 0.9)),
                VertexFormat(glm::vec3( 0.3,  0.6,  0.2), glm::vec3(0, 1, 0), glm::vec3(0.9, 0.9, 0.9)),
                VertexFormat(glm::vec3(-0.3,  0.6,  0.2), glm::vec3(0, 1, 0), glm::vec3(0.9, 0.9, 0.9)),
                                                  
                VertexFormat(glm::vec3(-0.3, -0.6, -0.2), glm::vec3(0, 1, 0), glm::vec3(0.9, 0.9, 0.9)),
                VertexFormat(glm::vec3( 0.3, -0.6, -0.2), glm::vec3(0, 1, 0), glm::vec3(0.9, 0.9, 0.9)),
                VertexFormat(glm::vec3( 0.3,  0.6, -0.2), glm::vec3(0, 1, 0), glm::vec3(0.9, 0.9, 0.9)),
                VertexFormat(glm::vec3(-0.3,  0.6, -0.2), glm::vec3(0, 1, 0), glm::vec3(0.9, 0.9, 0.9))
            };
            vector<unsigned int> indices =
            {
                // front
                0, 1, 2,
                2, 3, 0,
                // right
                1, 5, 6,
                6, 2, 1,
                // back
                7, 6, 5,
                5, 4, 7,
                // left
                4, 0, 3,
                3, 7, 4,
                // bottom
                4, 5, 1,
                1, 0, 4,
                // top
                3, 2, 6,
                6, 7, 3
            };
            CreateMesh("body", vertices, indices);
        }

        //Create Hand
        {
            vector<VertexFormat> vertices{
                VertexFormat(glm::vec3(-0.15, -0.6,  0.15), glm::vec3(0, 1, 0), glm::vec3(1, 0.95, 0.90)),
                VertexFormat(glm::vec3( 0.15, -0.6,  0.15), glm::vec3(0, 1, 0), glm::vec3(1, 0.95, 0.90)),
                VertexFormat(glm::vec3( 0.15,  0.6,  0.15), glm::vec3(0, 1, 0), glm::vec3(1, 0.95, 0.90)),
                VertexFormat(glm::vec3(-0.15,  0.6,  0.15), glm::vec3(0, 1, 0), glm::vec3(1, 0.95, 0.90)),
                                                       
                VertexFormat(glm::vec3(-0.15, -0.6, -0.15), glm::vec3(0, 1, 0), glm::vec3(1, 0.95, 0.90)),
                VertexFormat(glm::vec3( 0.15, -0.6, -0.15), glm::vec3(0, 1, 0), glm::vec3(1, 0.95, 0.90)),
                VertexFormat(glm::vec3( 0.15,  0.6, -0.15), glm::vec3(0, 1, 0), glm::vec3(1, 0.95, 0.90)),
                VertexFormat(glm::vec3(-0.15,  0.6, -0.15), glm::vec3(0, 1, 0), glm::vec3(1, 0.95, 0.90))
            };
            vector<unsigned int> indices =
            {
                // front
                0, 1, 2,
                2, 3, 0,
                // right
                1, 5, 6,
                6, 2, 1,
                // back
                7, 6, 5,
                5, 4, 7,
                // left
                4, 0, 3,
                3, 7, 4,
                // bottom
                4, 5, 1,
                1, 0, 4,
                // top
                3, 2, 6,
                6, 7, 3
            };
            CreateMesh("hand", vertices, indices);
        }

        //Create Leg
        {
            vector<VertexFormat> vertices{
                VertexFormat(glm::vec3(-0.15, -0.6,  0.15), glm::vec3(0, 1, 0), glm::vec3(0.3, 0.3, 0.3)),
                VertexFormat(glm::vec3( 0.15, -0.6,  0.15), glm::vec3(0, 1, 0), glm::vec3(0.3, 0.3, 0.3)),
                VertexFormat(glm::vec3( 0.15,  0.6,  0.15), glm::vec3(0, 1, 0), glm::vec3(0.3, 0.3, 0.3)),
                VertexFormat(glm::vec3(-0.15,  0.6,  0.15), glm::vec3(0, 1, 0), glm::vec3(0.3, 0.3, 0.3)),
                                                                                                  
                VertexFormat(glm::vec3(-0.15, -0.6, -0.15), glm::vec3(0, 1, 0), glm::vec3(0.3, 0.3, 0.3)),
                VertexFormat(glm::vec3( 0.15, -0.6, -0.15), glm::vec3(0, 1, 0), glm::vec3(0.3, 0.3, 0.3)),
                VertexFormat(glm::vec3( 0.15,  0.6, -0.15), glm::vec3(0, 1, 0), glm::vec3(0.3, 0.3, 0.3)),
                VertexFormat(glm::vec3(-0.15,  0.6, -0.15), glm::vec3(0, 1, 0), glm::vec3(0.3, 0.3, 0.3))
            };
            vector<unsigned int> indices =
            {
                // front
                0, 1, 2,
                2, 3, 0, 
                // right
                1, 5, 6,
                6, 2, 1,
                // back
                7, 6, 5,
                5, 4, 7,
                // left
                4, 0, 3,
                3, 7, 4,
                // bottom
                4, 5, 1,
                1, 0, 4,
                // top
                3, 2, 6,
                6, 7, 3
            };
            CreateMesh("leg", vertices, indices);
        }

        // Create Pistol
        {
            // Create Pistol Barrel
            {
                vector<VertexFormat> vertices{
                    VertexFormat(glm::vec3(-0.05, -0.2,  0.05), glm::vec3(0, 1, 0), glm::vec3(0.5, 0.5, 0.5)),
                    VertexFormat(glm::vec3( 0.05, -0.2,  0.05), glm::vec3(0, 1, 0), glm::vec3(0.5, 0.5, 0.5)),
                    VertexFormat(glm::vec3( 0.05,  0.2,  0.05), glm::vec3(0, 1, 0), glm::vec3(0.5, 0.5, 0.5)),
                    VertexFormat(glm::vec3(-0.05,  0.2,  0.05), glm::vec3(0, 1, 0), glm::vec3(0.5, 0.5, 0.5)),

                    VertexFormat(glm::vec3(-0.05, -0.2, -0.05), glm::vec3(0, 1, 0), glm::vec3(0.5, 0.5, 0.5)),
                    VertexFormat(glm::vec3( 0.05, -0.2, -0.05), glm::vec3(0, 1, 0), glm::vec3(0.5, 0.5, 0.5)),
                    VertexFormat(glm::vec3( 0.05,  0.2, -0.05), glm::vec3(0, 1, 0), glm::vec3(0.5, 0.5, 0.5)),
                    VertexFormat(glm::vec3(-0.05,  0.2, -0.05), glm::vec3(0, 1, 0), glm::vec3(0.5, 0.5, 0.5))
                };
                vector<unsigned int> indices =
                {
                    // front
                    0, 1, 2,
                    2, 3, 0,
                    // right
                    1, 5, 6,
                    6, 2, 1,
                    // back
                    7, 6, 5,
                    5, 4, 7,
                    // left
                    4, 0, 3,
                    3, 7, 4,
                    // bottom
                    4, 5, 1,
                    1, 0, 4,
                    // top
                    3, 2, 6,
                    6, 7, 3
                };
                CreateMesh("pistol_barrel", vertices, indices);
            }

            // Create Pistol Handle
            {
                vector<VertexFormat> vertices{
                VertexFormat(glm::vec3(-0.03, -0.2,  0.03), glm::vec3(0, 1, 0), glm::vec3(0.5, 0.5, 0.5)),
                VertexFormat(glm::vec3( 0.03, -0.2,  0.03), glm::vec3(0, 1, 0), glm::vec3(0.5, 0.5, 0.5)),
                VertexFormat(glm::vec3( 0.03,  0.2,  0.03), glm::vec3(0, 1, 0), glm::vec3(0.5, 0.5, 0.5)),
                VertexFormat(glm::vec3(-0.03,  0.2,  0.03), glm::vec3(0, 1, 0), glm::vec3(0.5, 0.5, 0.5)),

                VertexFormat(glm::vec3(-0.03, -0.2, -0.03), glm::vec3(0, 1, 0), glm::vec3(0.5, 0.5, 0.5)),
                VertexFormat(glm::vec3( 0.03, -0.2, -0.03), glm::vec3(0, 1, 0), glm::vec3(0.5, 0.5, 0.5)),
                VertexFormat(glm::vec3( 0.03,  0.2, -0.03), glm::vec3(0, 1, 0), glm::vec3(0.5, 0.5, 0.5)),
                VertexFormat(glm::vec3(-0.03,  0.2, -0.03), glm::vec3(0, 1, 0), glm::vec3(0.5, 0.5, 0.5))
                };
                vector<unsigned int> indices =
                {
                    // front
                    0, 1, 2,
                    2, 3, 0,
                    // right
                    1, 5, 6,
                    6, 2, 1,
                    // back
                    7, 6, 5,
                    5, 4, 7,
                    // left
                    4, 0, 3,
                    3, 7, 4,
                    // bottom
                    4, 5, 1,
                    1, 0, 4,
                    // top
                    3, 2, 6,
                    6, 7, 3
                };
                CreateMesh("pistol_handle", vertices, indices);
            }
        }
    }

    // Create world
    for (int z = 0; z < zSize; z++) {
        for (int x = 0; x < xSize; x++) {
            if (getPixelColor(x, z) == 765) {
                wallPos.push_back(glm::vec3(x, 0, z));
            }
            else {
                if (getPixelColor(x, z) == 510) {
                    enemies.push_back(enemy::Enemy(window->props.selfDir, glm::vec3(-xSize / 2 + x, 3, -zSize / 2 + z), camera, projectionMatrix));
                }
                groundPos.push_back(glm::vec3(x, 0, z));
            }
        }
    }

    // Load Block Mesh
    Mesh* mesh = new Mesh("block");
    mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
    meshes[mesh->GetMeshID()] = mesh;


    // Create World Shader
    {
        Shader* shader = new Shader("World");
        shader->AddShader(PATH_JOIN(window->props.selfDir, PATH_JOIN("src", "Teme"), "tema2", "shaders", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, PATH_JOIN("src", "Teme"), "tema2", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }

    // Load Wall texture
    {
        wallTexture = new Texture2D();
        wallTexture->Load2D(PATH_JOIN(sourceTextureDir, "nether_brick.png").c_str(), GL_REPEAT);
    }

    // Load Ground texture
    {
        groundTexture = new Texture2D();
        groundTexture->Load2D(PATH_JOIN(sourceTextureDir, "stone_bricks.png").c_str(), GL_REPEAT);
    }
}


void Tema2::CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned int>& indices)
{
    unsigned int VAO = 0;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO = 0;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

    unsigned int IBO = 0;
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

    // Set vertex position attribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

    // Set vertex normal attribute
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

    // Set texture coordinate attribute
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));

    // Set vertex color attribute
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));

    glDeleteBuffers(1, &VAO);
     
    // Check for OpenGL errors
    if (GetOpenGLError() == GL_INVALID_OPERATION)
    {
        cout << "\t[NOTE] : For students : DON'T PANIC! This error should go away when completing the tasks." << std::endl;
        cout << "\t[NOTE] : For developers : This happens because OpenGL core spec >=3.1 forbids null VAOs." << std::endl;
    }

    // Mesh information is saved into a Mesh object
    meshes[name] = new Mesh(name);
    meshes[name]->InitFromBuffer(VAO, static_cast<unsigned int>(indices.size()));
}

void Tema2::RenderTexturedMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, Texture2D* texture)
{
    if (!mesh || !shader || !shader->GetProgramID())
        return;

    // Render an object using the specified shader and the specified position
    glUseProgram(shader->program);

    // Bind model matrix
    GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
    glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    // Bind view matrix
    glm::mat4 viewMatrix = camera->GetViewMatrix();
    int loc_view_matrix = glGetUniformLocation(shader->program, "View");
    glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

    // Bind projection matrix
    glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
    int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
    glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture->GetTextureID());
    glUniform1i(glGetUniformLocation(shader->GetProgramID(), "texture_1"), 0);

    // Draw the object
    glBindVertexArray(mesh->GetBuffers()->m_VAO);
    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
}

Tema2::~Tema2()
{
}


void Tema2::Init()
{
    isMoving = false;
    reverseAnimation = false;
    playerRotationY = 0;
    playerRightHandJoint = playerLeftHandJoint = playerLeftLegJoint = playerRightLegJoint = 0;
    renderCameraTarget = true;
    window->DisablePointer();
    FoV = 60;
    camera = new implemented::MyCamera();
    camera->Set(glm::vec3(0, 5.5f, 0.1f), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
    PlayerPosition = glm::vec3(0, 0, 0);

    projectionMatrix = glm::perspective(RADIANS(FoV), window->props.aspectRatio, 0.01f, 200.0f);
    camera->projectionMatrix = projectionMatrix;
}


void Tema2::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();

    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void Tema2::Update(float deltaTimeSeconds)
{
    WorldRenderer();
    playAnimation(deltaTimeSeconds);

    // Update Enemies
    {
        std::list<enemy::Enemy>::iterator it = enemies.begin();
        while (it != enemies.end()) {
            it->EnemyRenderer(camera, projectionMatrix);
            it++;
        }
    }

    // Update particles
    {
        std::list<particles::Particles>::iterator it = activeParticles.begin();
        while (it != activeParticles.end()) {
            it->Play();
            if (it->lifespan <= 0) {
                std::list<particles::Particles>::iterator prev = it++;
                activeParticles.erase(prev);
            }
            else {
                it++;
            }
        }
    }


    if (getPixelColor(xSize / 2 + camera->position.x, zSize / 2 + camera->position.z) == 255) {
        cout << "Victory" << endl;
    }
}


void Tema2::FrameEnd()
{
}

void Tema2::RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix)
{
    if (!mesh || !shader || !shader->program)
        return;

    // Render an object using the specified shader and the specified position
    shader->Use();
    glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
    glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    mesh->Render();
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema2::OnInputUpdate(float deltaTime, int mods)
{
    float cameraSpeed = 5;
    float offset = 2;
    int x, z;
    if (!renderCameraTarget) {
        x = xSize / 2 + camera->position.x + camera->forward.x * offset;
        z = zSize / 2 + camera->position.z + camera->forward.z * offset;
        if (window->KeyHold(GLFW_KEY_W) && !isColliding(x, z)){
            // TODO(student): Translate the camera forward
            camera->MoveForward(cameraSpeed * deltaTime);
        }
        x = xSize / 2 + camera->position.x - camera->right.x * offset;
        z = zSize / 2 + camera->position.z - camera->right.z * offset;
        if (window->KeyHold(GLFW_KEY_A) && !isColliding(x, z)) {
            // TODO(student): Translate the camera to the left
            camera->TranslateRight(-cameraSpeed * deltaTime);
        }
        x = xSize / 2 + camera->position.x - camera->forward.x * offset;
        z = zSize / 2 + camera->position.z - camera->forward.z * offset;
        if (window->KeyHold(GLFW_KEY_S) && !isColliding(x, z)) {
            // TODO(student): Translate the camera backward
            camera->MoveForward(-cameraSpeed * deltaTime);
        }
        x = xSize / 2 + camera->position.x + camera->right.x * offset;
        z = zSize / 2 + camera->position.z + camera->right.z * offset;
        if (window->KeyHold(GLFW_KEY_D) && !isColliding(x, z)) {
            // TODO(student): Translate the camera to the right
            camera->TranslateRight(cameraSpeed * deltaTime);
        }
    }
    else {
        if (window->KeyHold(GLFW_KEY_W) || window->KeyHold(GLFW_KEY_A) || window->KeyHold(GLFW_KEY_S) || window->KeyHold(GLFW_KEY_D)) {
            isMoving = true;
        }
        else {
            isMoving = false;
        }

        x = xSize / 2 + camera->GetTargetPosition().x + camera->forward.x * offset;
        z = zSize / 2 + camera->GetTargetPosition().z + camera->forward.z * offset;
        if (window->KeyHold(GLFW_KEY_W) && !isColliding(x, z)) {
            // TODO(student): Translate the camera forward
            camera->MoveForward(cameraSpeed * deltaTime);
        }
        x = xSize / 2 + camera->GetTargetPosition().x - camera->right.x * offset;
        z = zSize / 2 + camera->GetTargetPosition().z - camera->right.z * offset;
        if (window->KeyHold(GLFW_KEY_A) && !isColliding(x, z)) {
            // TODO(student): Translate the camera to the left
            camera->TranslateRight(-cameraSpeed * deltaTime);
        }
        x = xSize / 2 + camera->GetTargetPosition().x - camera->forward.x * offset;
        z = zSize / 2 + camera->GetTargetPosition().z - camera->forward.z * offset;
        if (window->KeyHold(GLFW_KEY_S) && !isColliding(x, z)) {
            // TODO(student): Translate the camera backward
            camera->MoveForward(-cameraSpeed * deltaTime);
        }
        x = xSize / 2 + camera->GetTargetPosition().x + camera->right.x * offset;
        z = zSize / 2 + camera->GetTargetPosition().z + camera->right.z * offset;
        if (window->KeyHold(GLFW_KEY_D) && !isColliding(x, z)) {
            // TODO(student): Translate the camera to the right
            camera->TranslateRight(cameraSpeed * deltaTime);
        }
    }
}


void Tema2::OnKeyPress(int key, int mods)
{
    if (key == GLFW_KEY_F3)
    {
        renderCameraTarget = !renderCameraTarget;
        if (!renderCameraTarget) {
            camera->position = glm::vec3(camera->position.x + camera->forward.x, 4.0f, camera->position.z + camera->forward.z);
        }
        else {
            camera->position = glm::vec3(camera->position.x - camera->forward.x, 4.0f, camera->position.z - camera->forward.z);
        }
    }
}


void Tema2::OnKeyRelease(int key, int mods)
{
}


void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
    float sensivityOX = 0.001f;
    float sensivityOY = 0.001f;
    playerRotationY += sensivityOY * -deltaX;
    if (renderCameraTarget) {
        camera->RotateThirdPerson_OX(sensivityOX * -deltaY);
        camera->RotateThirdPerson_OY(sensivityOY * -deltaX);
    }
    else {
        camera->RotateFirstPerson_OX(-sensivityOX * deltaY);
        camera->RotateFirstPerson_OY(-sensivityOY * deltaX);
    }
    
}


void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
    if (button == 1) {
        {
            if (renderCameraTarget) {
                particles::Particles particle = particles::Particles(window->props.selfDir, camera);
                particle.Init(camera->GetTargetPosition(), glm::vec3(camera->forward.x + camera->right.x, camera->forward.y + camera->right.y, camera->forward.z + camera->right.z));
                activeParticles.push_back(particle);
            }
            else {
                particles::Particles particle = particles::Particles(window->props.selfDir, camera);
                particle.Init(camera->position, glm::vec3(camera->forward.x + 0.5, camera->forward.y, camera->forward.z));
                activeParticles.push_back(particle);
            }
        }
        std::list<enemy::Enemy>::iterator it = enemies.begin();
        while (it != enemies.end()) {

            glm::vec3 playerPosition = camera->position;
            glm::vec3 direction = camera->forward;
            glm::vec3 enemyPosition = it->position;
            float range = (playerPosition.x - enemyPosition.x) * direction.z - (playerPosition.z - enemyPosition.z) * direction.x;
            if ( range <= 0.5 && range >= 0) {
                particles::Particles particle = particles::Particles(window->props.selfDir, camera);
                particle.Init(it->position, glm::vec3(0));
                activeParticles.push_back(particle);
                cout << "Enemy killed" << endl;
                std::list<enemy::Enemy>::iterator prev = it++;
                enemies.erase(prev);
            }
            else {
                it++;
            }
        }
    }
}


void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{

}


void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
    // Treat mouse scroll event
}


void Tema2::OnWindowResize(int width, int height)
{
    // Treat window resize event
}

bool Tema2::isColliding(int x, int z) {
    if (getPixelColor(x + 1, z + 1) == 765
        || getPixelColor(x - 1, z - 1) == 765
        || getPixelColor(x + 1, z - 1) == 765
        || getPixelColor(x - 1, z + 1) == 765
        || getPixelColor(x, z + 1) == 765
        || getPixelColor(x + 1, z) == 765
        || getPixelColor(x - 1, z) == 765
        || getPixelColor(x, z - 1) == 765)
        return true;
    return false;
}

int Tema2::getPixelColor(int x, int y) {
    if (x < 0 || y < 0) return 1;
    unsigned char* pixel = map + (y * xSize * 4) + (x * 4);
    return pixel[0] + pixel[1] + pixel[2];
}

void Tema2::PlayerRenderer() {
    glm::mat4 bodyMatrix;
    glm::mat4 headMatrix;

    glm::mat4 rightHandMatrix;
    glm::mat4 leftHandMatrix;
    glm::mat4 rightLegMatrix;
    glm::mat4 leftLegMatrix;

    glm::mat4 rightHandJointMatrix;
    glm::mat4 leftHandJointMatrix;
    glm::mat4 rightLegJointMatrix;
    glm::mat4 leftLegJointMatrix;

    glm::mat4 pistol_barrel;

    PlayerPosition = camera->GetTargetPosition();
    float offsetY = -1.8f;
    // Render Character
    {
        // Render Body
        {
            bodyMatrix = glm::mat4(1);
            bodyMatrix = glm::translate(bodyMatrix, glm::vec3(0 + PlayerPosition.x, 1.1 + offsetY + PlayerPosition.y, 0 + PlayerPosition.z));
            bodyMatrix = glm::rotate(bodyMatrix, playerRotationY, glm::vec3(0, 1, 0));
            RenderMesh(meshes["body"], shaders["VertexNormal"], bodyMatrix);
        }
        
        // Render Head
        {
            headMatrix = bodyMatrix * glm::mat4(1);
            headMatrix = glm::translate(headMatrix, glm::vec3(0, 0.9, 0));
            RenderMesh(meshes["head"], shaders["VertexNormal"], headMatrix);
        }

        // Render Right Hand
        {
            rightHandJointMatrix = bodyMatrix * glm::mat4(1);
            rightHandJointMatrix = glm::translate(rightHandJointMatrix, glm::vec3(0.45, 0.5, 0));
            rightHandJointMatrix = glm::rotate(rightHandJointMatrix, RADIANS(90.0f), glm::vec3(1, 0, 0));
            rightHandMatrix = rightHandJointMatrix * glm::mat4(1);
            rightHandMatrix = glm::translate(rightHandMatrix, glm::vec3(0, -0.4, 0));
            RenderMesh(meshes["hand"], shaders["VertexNormal"], rightHandMatrix);

            // Render Pistol

            pistol_barrel = rightHandJointMatrix * glm::mat4(1);
            pistol_barrel = glm::translate(pistol_barrel, glm::vec3(0, -1.05, -0.2));
            RenderMesh(meshes["pistol_barrel"], shaders["VertexNormal"], pistol_barrel);
            pistol_barrel = glm::translate(pistol_barrel, glm::vec3(0, 0.2, 0.2));
            pistol_barrel = glm::rotate(pistol_barrel, RADIANS(80.0f), glm::vec3(1, 0, 0));
            RenderMesh(meshes["pistol_handle"], shaders["VertexNormal"], pistol_barrel);

        }

        // Render Left Hand
        {
            leftHandJointMatrix = bodyMatrix * glm::mat4(1);
            leftHandJointMatrix = glm::translate(leftHandJointMatrix, glm::vec3(-0.45, 0.5, 0));
            leftHandJointMatrix = glm::rotate(leftHandJointMatrix, asinf(playerLeftHandJoint), glm::vec3(1, 0, 0));
            leftHandMatrix = leftHandJointMatrix * glm::mat4(1);
            leftHandMatrix = glm::translate(leftHandMatrix, glm::vec3(0, -0.4, 0));
            RenderMesh(meshes["hand"], shaders["VertexNormal"], leftHandMatrix);
        }

        // Render Left Leg
        {
            leftLegJointMatrix = bodyMatrix * glm::mat4(1);
            leftLegJointMatrix = glm::translate(leftLegJointMatrix, glm::vec3(-0.15, -0.8, 0));
            leftLegJointMatrix = glm::rotate(leftLegJointMatrix, asinf(playerLeftLegJoint), glm::vec3(1, 0, 0));
            leftLegMatrix = leftLegJointMatrix * glm::mat4(1);
            leftLegMatrix = glm::translate(leftLegMatrix, glm::vec3(0, -0.4, 0));
            RenderMesh(meshes["leg"], shaders["VertexNormal"], leftLegMatrix);
        }

        // Render Right Leg
        {
            rightLegJointMatrix = bodyMatrix * glm::mat4(1);
            rightLegJointMatrix = glm::translate(rightLegJointMatrix, glm::vec3(0.15, -0.8, 0));
            rightLegJointMatrix = glm::rotate(rightLegJointMatrix, asinf(playerRightLegJoint), glm::vec3(1, 0, 0));
            rightLegMatrix = rightLegJointMatrix * glm::mat4(1);
            rightLegMatrix = glm::translate(rightLegMatrix, glm::vec3(0, -0.4, 0));
            RenderMesh(meshes["leg"], shaders["VertexNormal"], rightLegMatrix);
        }
    }
}

void Tema2::playAnimation(float deltaTimeSeconds) {
    if (renderCameraTarget) {
        if (isMoving) {
            if (!reverseAnimation) {
                playerRightHandJoint += 1.0 * deltaTimeSeconds;
                playerLeftHandJoint -= 1.0 * deltaTimeSeconds;
                playerRightLegJoint -= 1.0 * deltaTimeSeconds;
                playerLeftLegJoint += 1.0 * deltaTimeSeconds;
                if (playerRightHandJoint >= 0.5) reverseAnimation = true;
            }
            else {
                playerRightHandJoint -= 1.0 * deltaTimeSeconds;
                playerLeftHandJoint += 1.0 * deltaTimeSeconds;
                playerRightLegJoint += 1.0 * deltaTimeSeconds;
                playerLeftLegJoint -= 1.0 * deltaTimeSeconds;
                if (playerRightHandJoint <= -0.5) reverseAnimation = false;
            }
        }
        else {
            if (!reverseAnimation) { 
                playerLeftHandJoint -= 0.1 * deltaTimeSeconds;
                if (playerLeftHandJoint <= -0.1) reverseAnimation = true; 
            }
            else { 
                playerLeftHandJoint += 0.1 * deltaTimeSeconds;
                if (playerLeftHandJoint >= 0.1) reverseAnimation = false; 
            }
            playerRightHandJoint = 0;
            
            playerRightLegJoint = 0;
            playerLeftLegJoint = 0;
        }

        PlayerRenderer();
    }
    else {
        glm::mat4 rightHandMatrix;
        glm::mat4 rightHandJointMatrix;
        glm::mat4 pistol_barrel;
        PlayerPosition = camera->position;
        // Render Right Hand
        {
            rightHandJointMatrix =  glm::mat4(1);
            rightHandJointMatrix = glm::translate(rightHandJointMatrix, glm::vec3(PlayerPosition.x, PlayerPosition.y, PlayerPosition.z));
            rightHandJointMatrix = glm::rotate(rightHandJointMatrix, RADIANS(90.0f), glm::vec3(1, 0, 0));
            rightHandJointMatrix = glm::rotate(rightHandJointMatrix, -playerRotationY, glm::vec3(0, 0, 1));
            rightHandMatrix = rightHandJointMatrix * glm::mat4(1);
            rightHandMatrix = glm::translate(rightHandMatrix, glm::vec3(0.8, -0.4, 0.6));
            RenderMesh(meshes["hand"], shaders["VertexNormal"], rightHandMatrix);

            // Render Pistol

            pistol_barrel = rightHandJointMatrix * glm::mat4(1);
            pistol_barrel = glm::translate(pistol_barrel, glm::vec3(0.8, -1.05, 0.4));
            RenderMesh(meshes["pistol_barrel"], shaders["VertexNormal"], pistol_barrel);
            pistol_barrel = glm::translate(pistol_barrel, glm::vec3(0, 0.2, 0.2));
            pistol_barrel = glm::rotate(pistol_barrel, RADIANS(80.0f), glm::vec3(1, 0, 0));
            RenderMesh(meshes["pistol_handle"], shaders["VertexNormal"], pistol_barrel);

        }
    }
}

void Tema2::WorldRenderer() {
    // Render Plane
    {
        std::list<glm::vec3>::iterator it = groundPos.begin();
        while (it != groundPos.end()) {
            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, glm::vec3(-xSize / 2 + it->x, it->y, -zSize / 2 + it->z));
            RenderTexturedMesh(meshes["block"], shaders["World"], modelMatrix, groundTexture);
            it++;
        }
    }

    // Render Maze
    {
        std::list<glm::vec3>::iterator it = wallPos.begin();
        while (it != wallPos.end()) {
            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, glm::vec3(-xSize / 2 + it->x, it->y, -zSize / 2 + it->z));
            for (int i = 0; i < 4; i++) {
                modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 1, 0));
                RenderTexturedMesh(meshes["block"], shaders["World"], modelMatrix, wallTexture);
            }
            it++;
        }
    }
}
#include "Enemy.h"

#include <vector>
#include <iostream>
#include <stdlib.h>
#include "utils/text_utils.h"

using namespace std;
using namespace enemy;

Enemy::Enemy(std::string dir, glm::vec3 position, implemented::MyCamera* camera, glm::mat4 projectionMatrix) {
    this->position = position;
    this->camera = camera;
    this->projectionMatrix = projectionMatrix;
    //Create Character
    {
        //Create Head
        {
            vector<VertexFormat> vertices{
                VertexFormat(glm::vec3(-0.3, -0.3,  0.3), glm::vec3(0, 1, 0), glm::vec3(0.9, 0, 0)),
                VertexFormat(glm::vec3( 0.3, -0.3,  0.3), glm::vec3(0, 1, 0), glm::vec3(0.9, 0, 0)),
                VertexFormat(glm::vec3( 0.3,  0.3,  0.3), glm::vec3(0, 1, 0), glm::vec3(0.9, 0, 0)),
                VertexFormat(glm::vec3(-0.3,  0.3,  0.3), glm::vec3(0, 1, 0), glm::vec3(0.9, 0, 0)),
                                                                                        
                VertexFormat(glm::vec3(-0.3, -0.3, -0.3), glm::vec3(0, 1, 0), glm::vec3(0.9, 0, 0)),
                VertexFormat(glm::vec3( 0.3, -0.3, -0.3), glm::vec3(0, 1, 0), glm::vec3(0.9, 0, 0)),
                VertexFormat(glm::vec3( 0.3,  0.3, -0.3), glm::vec3(0, 1, 0), glm::vec3(0.9, 0, 0)),
                VertexFormat(glm::vec3(-0.3,  0.3, -0.3), glm::vec3(0, 1, 0), glm::vec3(0.9, 0, 0))
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
                VertexFormat(glm::vec3(-0.3, -0.6,  0.2), glm::vec3(0, 1, 0), glm::vec3(0.8, 0, 0)),
                VertexFormat(glm::vec3( 0.3, -0.6,  0.2), glm::vec3(0, 1, 0), glm::vec3(0.8, 0, 0)),
                VertexFormat(glm::vec3( 0.3,  0.6,  0.2), glm::vec3(0, 1, 0), glm::vec3(0.8, 0, 0)),
                VertexFormat(glm::vec3(-0.3,  0.6,  0.2), glm::vec3(0, 1, 0), glm::vec3(0.8, 0, 0)),
                                                                                        
                VertexFormat(glm::vec3(-0.3, -0.6, -0.2), glm::vec3(0, 1, 0), glm::vec3(0.8, 0, 0)),
                VertexFormat(glm::vec3( 0.3, -0.6, -0.2), glm::vec3(0, 1, 0), glm::vec3(0.8, 0, 0)),
                VertexFormat(glm::vec3( 0.3,  0.6, -0.2), glm::vec3(0, 1, 0), glm::vec3(0.8, 0, 0)),
                VertexFormat(glm::vec3(-0.3,  0.6, -0.2), glm::vec3(0, 1, 0), glm::vec3(0.8, 0, 0))
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
                VertexFormat(glm::vec3(-0.15, -0.6,  0.15), glm::vec3(0, 1, 0), glm::vec3(1, 0, 0)),
                VertexFormat(glm::vec3( 0.15, -0.6,  0.15), glm::vec3(0, 1, 0), glm::vec3(1, 0, 0)),
                VertexFormat(glm::vec3( 0.15,  0.6,  0.15), glm::vec3(0, 1, 0), glm::vec3(1, 0, 0)),
                VertexFormat(glm::vec3(-0.15,  0.6,  0.15), glm::vec3(0, 1, 0), glm::vec3(1, 0, 0)),

                VertexFormat(glm::vec3(-0.15, -0.6, -0.15), glm::vec3(0, 1, 0), glm::vec3(1, 0, 0)),
                VertexFormat(glm::vec3( 0.15, -0.6, -0.15), glm::vec3(0, 1, 0), glm::vec3(1, 0, 0)),
                VertexFormat(glm::vec3( 0.15,  0.6, -0.15), glm::vec3(0, 1, 0), glm::vec3(1, 0, 0)),
                VertexFormat(glm::vec3(-0.15,  0.6, -0.15), glm::vec3(0, 1, 0), glm::vec3(1, 0, 0))
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
                VertexFormat(glm::vec3(-0.15, -0.6,  0.15), glm::vec3(0, 1, 0), glm::vec3(1, 0, 0)),
                VertexFormat(glm::vec3( 0.15, -0.6,  0.15), glm::vec3(0, 1, 0), glm::vec3(1, 0, 0)),
                VertexFormat(glm::vec3( 0.15,  0.6,  0.15), glm::vec3(0, 1, 0), glm::vec3(1, 0, 0)),
                VertexFormat(glm::vec3(-0.15,  0.6,  0.15), glm::vec3(0, 1, 0), glm::vec3(1, 0, 0)),
                                                                                          
                VertexFormat(glm::vec3(-0.15, -0.6, -0.15), glm::vec3(0, 1, 0), glm::vec3(1, 0, 0)),
                VertexFormat(glm::vec3( 0.15, -0.6, -0.15), glm::vec3(0, 1, 0), glm::vec3(1, 0, 0)),
                VertexFormat(glm::vec3( 0.15,  0.6, -0.15), glm::vec3(0, 1, 0), glm::vec3(1, 0, 0)),
                VertexFormat(glm::vec3(-0.15,  0.6, -0.15), glm::vec3(0, 1, 0), glm::vec3(1, 0, 0))
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
    }

    // Create a shader program for drawing face polygon with the color of the normal
    {
    Shader* shader = new Shader("VertexNormal");
    shader->AddShader(PATH_JOIN(dir, RESOURCE_PATH::SHADERS, "MVP.Texture.VS.glsl"), GL_VERTEX_SHADER);
    shader->AddShader(PATH_JOIN(dir, RESOURCE_PATH::SHADERS, "Normals.FS.glsl"), GL_FRAGMENT_SHADER);
    shader->CreateAndLink();
    shaders[shader->GetName()] = shader;
    }
}

Enemy::~Enemy() {

}

void Enemy::CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned int>& indices)
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

void Enemy::EnemyRenderer(implemented::MyCamera* camera, glm::mat4 projectionMatrix) {

    this->camera = camera;
    this->projectionMatrix = projectionMatrix;

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

    float offsetY = -1.8f;
    // Render Character
    {
        // Render Body
        {
            bodyMatrix = glm::mat4(1);
            bodyMatrix = glm::translate(bodyMatrix, glm::vec3(0 + position.x, 1.1 + offsetY + position.y, 0 + position.z));
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
            rightHandMatrix = rightHandJointMatrix * glm::mat4(1);
            rightHandMatrix = glm::translate(rightHandMatrix, glm::vec3(0, -0.4, 0));
            RenderMesh(meshes["hand"], shaders["VertexNormal"], rightHandMatrix);

        }

        // Render Left Hand
        {
            leftHandJointMatrix = bodyMatrix * glm::mat4(1);
            leftHandJointMatrix = glm::translate(leftHandJointMatrix, glm::vec3(-0.45, 0.5, 0));
            leftHandMatrix = leftHandJointMatrix * glm::mat4(1);
            leftHandMatrix = glm::translate(leftHandMatrix, glm::vec3(0, -0.4, 0));
            RenderMesh(meshes["hand"], shaders["VertexNormal"], leftHandMatrix);
        }

        // Render Left Leg
        {
            leftLegJointMatrix = bodyMatrix * glm::mat4(1);
            leftLegJointMatrix = glm::translate(leftLegJointMatrix, glm::vec3(-0.15, -0.8, 0));
            leftLegMatrix = leftLegJointMatrix * glm::mat4(1);
            leftLegMatrix = glm::translate(leftLegMatrix, glm::vec3(0, -0.4, 0));
            RenderMesh(meshes["leg"], shaders["VertexNormal"], leftLegMatrix);
        }

        // Render Right Leg
        {
            rightLegJointMatrix = bodyMatrix * glm::mat4(1);
            rightLegJointMatrix = glm::translate(rightLegJointMatrix, glm::vec3(0.15, -0.8, 0));
            rightLegMatrix = rightLegJointMatrix * glm::mat4(1);
            rightLegMatrix = glm::translate(rightLegMatrix, glm::vec3(0, -0.4, 0));
            RenderMesh(meshes["leg"], shaders["VertexNormal"], rightLegMatrix);
        }
    }
}

void Enemy::RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix)
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

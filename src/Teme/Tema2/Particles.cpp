#include "Particles.h"

#include <vector>
#include <iostream>

using namespace std;
using namespace particles;


struct Particle
{
    glm::vec4 position;
    glm::vec4 speed;
    glm::vec4 initialPos;
    glm::vec4 initialSpeed;

    Particle() {}

    Particle(const glm::vec4& pos, const glm::vec4& speed)
    {
        SetInitial(pos, speed);
    }

    void SetInitial(const glm::vec4& pos, const glm::vec4& speed)
    {
        position = pos;
        initialPos = pos;

        this->speed = speed;
        initialSpeed = speed;
    }
};


ParticleEffect<Particle>* particleEffect;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Particles::Particles(std::string dir, implemented::MyCamera* camera)
{
    this->dir = dir;
    this->camera = camera;
}


Particles::~Particles()
{
}


void Particles::Init(glm::vec3 position, glm::vec3 forward)
{
    lifespan = 2;
    {
        Mesh* mesh = new Mesh("box");
        mesh->LoadMesh(PATH_JOIN(dir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    // Load textures
    {
        TextureManager::LoadTexture(PATH_JOIN(dir, RESOURCE_PATH::TEXTURES), "particle2.png");
    }

    LoadShader("Particle");

    unsigned int nrParticles = 100;

    particleEffect = new ParticleEffect<Particle>();
    particleEffect->Generate(nrParticles, true);

    auto particleSSBO = particleEffect->GetParticleBuffer();
    Particle* data = const_cast<Particle*>(particleSSBO->GetBuffer());

    int cubeSize = 20;
    int hSize = cubeSize / 2;

    for (unsigned int i = 0; i < nrParticles; i++)
    {
        glm::vec4 pos(1);
        pos.x = position.x + forward.x * 2 + (rand() % cubeSize - hSize) / 10.0f;
        pos.y = position.y + forward.y * 2 + (rand() % cubeSize - hSize) / 10.0f;
        pos.z = position.z + forward.z * 2 +(rand() % cubeSize - hSize) / 10.0f;

        glm::vec4 speed(0);
        speed.x = (rand() % 20 - 10) / 10.0f;
        speed.z = (rand() % 20 - 10) / 10.0f;
        speed.y = rand() % 2 + 2.0f;

        data[i].SetInitial(pos, speed);
    }

    particleSSBO->SetBufferData(data);
}

void Particles::Play()
{
    lifespan--;
    glLineWidth(3);

    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    glBlendFunc(GL_ONE, GL_ONE);
    glBlendEquation(GL_FUNC_ADD);
    {
        auto shader = shaders["Particle"];
        if (shader->GetProgramID())
        {
            shader->Use();
            TextureManager::GetTexture("particle2.png")->BindToTextureUnit(GL_TEXTURE0);
            particleEffect->Render(camera, shader);
        }
    }

    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
}

void Particles::LoadShader(const std::string& name, bool hasGeomtery)
{
    std::string shaderPath = PATH_JOIN(dir, PATH_JOIN("src", "Teme"), "Tema2", "shaders");

    // Create a shader program for particle system
    {
        Shader* shader = new Shader(name);
        shader->AddShader(PATH_JOIN(shaderPath, name + ".VS.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(shaderPath, name + ".FS.glsl"), GL_FRAGMENT_SHADER);
        if (hasGeomtery)
        {
            shader->AddShader(PATH_JOIN(shaderPath, name + ".GS.glsl"), GL_GEOMETRY_SHADER);
        }

        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }
}

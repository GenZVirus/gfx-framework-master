#pragma once

#include <string>

#include "components/simple_scene.h"
#include "core/gpu/particle_effect.h"
#include "implemented_camera.h"

namespace particles
{
    class Particles
    {
    public:
        Particles(std::string dir, implemented::MyCamera* camera);
        ~Particles();
        void Play();

        void Init(glm::vec3 position, glm::vec3 forward);
        int lifespan;

    private:
        void LoadShader(const std::string& name, bool hasGeomtery = true);

    protected:
        std::string dir;
        std::unordered_map<std::string, Mesh*> meshes;
        std::unordered_map<std::string, Shader*> shaders;
        implemented::MyCamera* camera;
        glm::mat4 modelMatrix;
        float translateX, translateY, translateZ;
        float scaleX, scaleY, scaleZ;
        float angularStepOX, angularStepOY, angularStepOZ;
        GLenum polygonMode;
    };
}

#pragma once

#include "components/simple_scene.h"
#include "Teme/Tema2/implemented_camera.h"

namespace enemy {
	class Enemy
	{
	public:
		Enemy(std::string dir, glm::vec3 position, implemented::MyCamera* camera, glm::mat4 projectionMatrix);
		~Enemy();
		void CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned int>& indices);
		void RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix);
		void EnemyRenderer(implemented::MyCamera* camera, glm::mat4 projectionMatrix);
		glm::vec3 position;


	private:
		std::string dir;
		std::unordered_map<std::string, Mesh*> meshes;
		std::unordered_map<std::string, Shader*> shaders;
		implemented::MyCamera* camera;
		glm::mat4 projectionMatrix;
	};
}
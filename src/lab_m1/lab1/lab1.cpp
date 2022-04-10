#include "lab_m1/lab1/lab1.h"

#include <vector>
#include <iostream>
#include <stdlib.h>

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Lab1::Lab1(glm::vec4 bgColor)
{
    // TODO(student): Never forget to initialize class variables!
    Lab1::bgColor = bgColor;
    position = glm::vec3(0, 0, 0);
    W = A = S = D = E = Q = 0;
}


Lab1::~Lab1()
{
}


void Lab1::Init()
{
    // Load a mesh from file into GPU memory. We only need to do it once,
    // no matter how many times we want to draw this mesh.
    {
        Mesh* mesh = new Mesh("box");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    // TODO(student): Load some more meshes. The value of RESOURCE_PATH::MODELS
    // is actually a path on disk, go there and you will find more meshes.

    {
        Mesh* mesh = new Mesh("sphere");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "sphere.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("archer");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "characters\\archer"), "Archer.fbx");
        meshes[mesh->GetMeshID()] = mesh;
    }

    currentMesh = meshes.begin();

}


void Lab1::FrameStart()
{
}


void Lab1::Update(float deltaTimeSeconds)
{
    glm::ivec2 resolution = window->props.resolution;

    // Sets the clear color for the color buffer

    // TODO(student): Generalize the arguments of `glClearColor`.
    // You can, for example, declare three variables in the class header,
    // that will store the color components (red, green, blue).
    glClearColor(bgColor.r, bgColor.g, bgColor.b, bgColor.a);

    // Clears the color buffer (using the previously set color) and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);

    // Render the object
    //RenderMesh(meshes["box"], glm::vec3(1, 0.5f, 0), glm::vec3(0.5f));

    // Render the object again but with different properties
    //RenderMesh(meshes["box"], glm::vec3(-1, 0.5f, 0));

    // TODO(student): We need to render (a.k.a. draw) the mesh that
    // was previously loaded. We do this using `RenderMesh`. Check the
    // signature of this function to see the meaning of its parameters.
    // You can draw the same mesh any number of times.

    //RenderMesh(meshes["sphere"], glm::vec3(0, 0.5f, -1));
    if(currentMesh->first == "archer")
        RenderMesh(currentMesh->second, position, glm::vec3(0.005f));
    else RenderMesh(currentMesh->second, position);



}


void Lab1::FrameEnd()
{
    DrawCoordinateSystem();
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Lab1::OnInputUpdate(float deltaTime, int mods)
{
    // Treat continuous update based on input

    // TODO(student): Add some key hold events that will let you move
    // a mesh instance on all three axes. You will also need to
    // generalize the position used by `RenderMesh`.
    if (W) {
        position.z += 1.0f * deltaTime;
    }
    if (A) {
        position.x -= 1.0f * deltaTime;
    }
    if (S) {
        position.z -= 1.0f * deltaTime;
    }
    if (D) {
        position.x += 1.0f * deltaTime;
    }
    if (E) {
        position.y -= 1.0f * deltaTime;
    }
    if (Q) {
        position.y += 1.0f * deltaTime;
    }
}


void Lab1::OnKeyPress(int key, int mods)
{
    // Add key press event
    // TODO(student): Change the values of the color components.
    // TODO(student): Add a key press event that will let you cycle
    // through at least two meshes, rendered at the same position.
    // You will also need to generalize the mesh name used by `RenderMesh`.
    switch (key) {
        case GLFW_KEY_F: {
            bgColor = glm::vec4(rand() % 256 / 1000.0f, rand() % 256 / 1000.0f, rand() % 256 / 1000.0f, rand() % 256 / 1000.0f);
            break;
        }
        case GLFW_KEY_G: {
            currentMesh++;
            if (currentMesh == meshes.end()) currentMesh = meshes.begin();
            break;
        }
        case GLFW_KEY_W: {
            W = 1;
            break;
        }
        case GLFW_KEY_A: {
            A = 1;
            break;
        }
        case GLFW_KEY_S: {
            S = 1;
            break;
        }
        case GLFW_KEY_D: {
            D = 1;
            break;
        }
        case GLFW_KEY_E: {
            E = 1;
            break;
        }
        case GLFW_KEY_Q: {
            Q = 1;
            break;
        }
        default: {break; }
    }

}


void Lab1::OnKeyRelease(int key, int mods)
{
    switch (key) {
    case GLFW_KEY_W: {
        W = 0;
        break;
    }
    case GLFW_KEY_A: {
        A = 0;
        break;
    }
    case GLFW_KEY_S: {
        S = 0;
        break;
    }
    case GLFW_KEY_D: {
        D = 0;
        break;
    }
    case GLFW_KEY_E: {
        E = 0;
        break;
    }
    case GLFW_KEY_Q: {
        Q = 0;
        break;
    }
    default: {break; }
    }
}


void Lab1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}


void Lab1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Lab1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Lab1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
    // Treat mouse scroll event
}


void Lab1::OnWindowResize(int width, int height)
{
    // Treat window resize event
}

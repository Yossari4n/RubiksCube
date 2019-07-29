#include "MainScene.h"

#include "../cbs/components/FirstPersonController.h"
#include "../cbs/components/Camera.h"
#include "../cbs/components/MeshRenderer/MeshRenderer.h"
#include "../cbs/components/PointLight.h"
#include "../cbs/components/DummyComp.h"
#include "../cbs/components/Cubie.h"

constexpr glm::vec3 MODEL_SCALE(1.0f / (976.032f * 2.0f), 1.0f / (976.032f * 2.0f), 1.0f / (986.312f * 2.0f));

void MainScene::CreateScene() {
    FrameRateLimit(0);
    Skybox("data/skybox/right.jpg",
           "data/skybox/left.jpg",
           "data/skybox/top.jpg",
           "data/skybox/bottom.jpg",
           "data/skybox/back.jpg",
           "data/skybox/front.jpg");

    auto camera = CreateObject("Camera"); {
        camera->Root().Position(glm::vec3(3.0f, 0.0f, 0.0f));
        camera->Root().Rotation(glm::vec3(0.0f, -179.0f, 0.0f)); // TODO fix FirstPersonController when object rotated 180 degrees
        camera->CreateComponent<Camera>(glm::perspective(glm::radians(45.0f), 2880.0f / 1800.0f, 0.1f, 3000.0f));
        camera->CreateComponent<PointLight>(glm::vec3(0.1f),
                                            glm::vec3(0.8f),
                                            glm::vec3(0.5f),
                                            1.0f,
                                            0.0014f,
                                            0.000007f);
        auto fpc = camera->CreateComponent<FirstPersonController>();
    }

    auto rubiks_cube = CreateObject("RubiksCube"); {
        auto cubie = rubiks_cube->CreateComponent<Cubie>(BLUE, RED, BLACK, WHITE);
        rubiks_cube->Connect(rubiks_cube->Root().ModelOut, cubie->Model);
    }
}

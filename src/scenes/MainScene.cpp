#include "MainScene.h"

#include "../cbs/components/ThirdPersonController.h"
#include "../cbs/components/Camera.h"
#include "../cbs/components/MeshRenderer/MeshRenderer.h"
#include "../cbs/components/PointLight.h"
#include "../cbs/components/DummyComp.h"
#include "../cbs/components/RubiksCube/RubiksCube.h"
#include "../cbs/components/TextRenderer.h"

void MainScene::CreateScene() {
    FrameRateLimit(60);
    Skybox("resources/skybox/right.png",
           "resources/skybox/left.png",
           "resources/skybox/top.png",
           "resources/skybox/bottom.png",
           "resources/skybox/back.png",
           "resources/skybox/front.png");

    auto rubiks_cube = CreateObject("RubiksCube"); {
        auto cube = rubiks_cube->CreateComponent<RubiksCube>();
        auto text_renderer = rubiks_cube->CreateComponent<TextRenderer>("", ImVec2(0.0f, 0.75f), IWidget::EAlign::CENTER, IWidget::EAlign::NONE);
        text_renderer->ChangeFont("resources/fonts/times.ttf", 100.0f);
        text_renderer->ChangeColor(ImVec4(0.1f, 0.1f, 0.1f, 1.0f));
        rubiks_cube->Connect(cube->TasksSignaturesOut, text_renderer->ChangeTextIn);
    }

    auto camera = CreateObject("Camera"); {
        camera->CreateComponent<Camera>(glm::perspective(glm::radians(45.0f), static_cast<float>(g_Window.Width()) / static_cast<float>(g_Window.Height()), 0.1f, 50.0f));
        camera->CreateComponent<PointLight>(glm::vec3(0.1f),
                                            glm::vec3(0.8f),
                                            glm::vec3(0.5f),
                                            1.0f,
                                            0.0014f,
                                            0.000007f);
        camera->CreateComponent<ThirdPersonController>(rubiks_cube, glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), 15.0f);
        camera->CreateComponent<DummyComp>();
    }
}

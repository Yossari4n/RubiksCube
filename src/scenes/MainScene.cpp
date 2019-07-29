#include "MainScene.h"

#include "../cbs/components/FirstPersonController.h"
#include "../cbs/components/Camera.h"
#include "../cbs/components/MeshRenderer/MeshRenderer.h"
#include "../cbs/components/PointLight.h"
#include "../cbs/components/DummyComp.h"

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
        camera->Root().Move(camera->Root().Front() * -2.0f);
        camera->CreateComponent<Camera>(glm::perspective(glm::radians(45.0f), 2880.0f / 1800.0f, 0.1f, 3000.0f));
        camera->CreateComponent<PointLight>(glm::vec3(0.1f),
                                            glm::vec3(0.8f),
                                            glm::vec3(0.5f),
                                            1.0f,
                                            0.0014f,
                                            0.000007f);
        auto fpc = camera->CreateComponent<FirstPersonController>();
    }

    auto first = CreateObject("First"); {
        auto mesh_renderer = first->CreateComponent<MeshRenderer>("data/earth/13902_Earth_v1_l3.obj",
                                                                   ShaderProgram::Type::PHONG);

        auto model_transform = first->CreateComponent<Transform>();
        model_transform->Scale(MODEL_SCALE);

        first->CreateComponent<DummyComp>();

        first->Connect(first->Root().TransformOut, model_transform->Parent);
        first->Connect(model_transform->ModelOut, mesh_renderer->Model);
    }
}

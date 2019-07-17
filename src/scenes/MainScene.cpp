#include "MainScene.h"

#include "../cbs/components/FirstPersonController.h"
#include "../cbs/components/Camera.h"

void MainScene::CreateScene() {
    FrameRate(60);
    Skybox("data/skybox/right.jpg",
           "data/skybox/left.jpg",
           "data/skybox/top.jpg",
           "data/skybox/bottom.jpg",
           "data/skybox/back.jpg",
           "data/skybox/front.jpg");
        
    auto camera = CreateObject("Camera");
    camera->Root().Position(glm::vec3(0.0f, 0.0f, 80.0f));
    camera->Root().Rotate(glm::vec3(0.0f, 0.0f, 0.0f));
    camera->CreateComponent<Camera>(glm::perspective(glm::radians(45.0f), 2880.0f / 1800.0f, 0.1f, 3000.0f));
    auto camera_fpc = camera->CreateComponent<FirstPersonController>();
}

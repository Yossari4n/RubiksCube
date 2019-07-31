#include "MainScene.h"

#include "../cbs/components/FirstPersonController.h"
#include "../cbs/components/Camera.h"
#include "../cbs/components/MeshRenderer/MeshRenderer.h"
#include "../cbs/components/PointLight.h"
#include "../cbs/components/DummyComp.h"
#include "../cbs/components/RubiksCube/RubiksCube.h"

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
        camera->Root().Rotation(glm::vec3(0.0f, -179.0f, 0.0f)); // TODO fix FirstPersonController when object rotated 180 degrees OY
        camera->CreateComponent<Camera>(glm::perspective(glm::radians(45.0f), static_cast<float>(g_Window.Width()) / static_cast<float>(g_Window.Height()), 0.1f, 50.0f));
        camera->CreateComponent<PointLight>(glm::vec3(0.1f),
                                            glm::vec3(0.8f),
                                            glm::vec3(0.5f),
                                            1.0f,
                                            0.0014f,
                                            0.000007f);
        camera->CreateComponent<FirstPersonController>();
    }

    auto rubiks_cube = CreateObject("RubiksCube"); {
        auto cube = rubiks_cube->CreateComponent<RubiksCube>();

        /*
        // Create cube's faces and connect them
        auto front = rubiks_cube->CreateComponent<Face>();
        auto front_t = rubiks_cube->CreateComponent<Transform>();
        rubiks_cube->Connect(front_t->TransformOut, front->FaceTransform);
        rubiks_cube->Connect(front->This, cube->FrontFace);

        auto left = rubiks_cube->CreateComponent<Face>();
        auto left_t = rubiks_cube->CreateComponent<Transform>();
        rubiks_cube->Connect(left_t->TransformOut, left->FaceTransform);
        rubiks_cube->Connect(left->This, cube->LeftFace);

        auto right = rubiks_cube->CreateComponent<Face>();
        auto right_t = rubiks_cube->CreateComponent<Transform>();
        rubiks_cube->Connect(right_t->TransformOut, right->FaceTransform);
        rubiks_cube->Connect(right->This, cube->RightFace);

        auto top = rubiks_cube->CreateComponent<Face>();
        auto top_t = rubiks_cube->CreateComponent<Transform>();
        rubiks_cube->Connect(top_t->TransformOut, top->FaceTransform);
        rubiks_cube->Connect(top->This, cube->TopFace);

        auto bottom = rubiks_cube->CreateComponent<Face>();
        auto bottom_t = rubiks_cube->CreateComponent<Transform>();
        rubiks_cube->Connect(bottom_t->TransformOut, bottom->FaceTransform);
        rubiks_cube->Connect(bottom->This, cube->BottomFace);

        auto back = rubiks_cube->CreateComponent<Face>();
        auto back_t = rubiks_cube->CreateComponent<Transform>();
        rubiks_cube->Connect(back_t->TransformOut, back->FaceTransform);
        rubiks_cube->Connect(back->This, cube->BackFace);


        // Connect faces with it's neighbours
        //
        rubiks_cube->Connect(top->This, front->Neighbours[0]);
        rubiks_cube->Connect(right->This, front->Neighbours[1]);
        rubiks_cube->Connect(bottom->This, front->Neighbours[2]);
        rubiks_cube->Connect(left->This, front->Neighbours[3]);

        // 
        rubiks_cube->Connect(back->This, top->Neighbours[0]);
        rubiks_cube->Connect(right->This, top->Neighbours[1]);
        rubiks_cube->Connect(front->This, top->Neighbours[2]);
        rubiks_cube->Connect(left->This, top->Neighbours[3]);

        // 
        rubiks_cube->Connect(back->This, left->Neighbours[0]);
        rubiks_cube->Connect(top->This, left->Neighbours[1]);
        rubiks_cube->Connect(front->This, left->Neighbours[2]);
        rubiks_cube->Connect(bottom->This, left->Neighbours[3]);

        // 
        rubiks_cube->Connect(back->This, right->Neighbours[0]);
        rubiks_cube->Connect(bottom->This, right->Neighbours[1]);
        rubiks_cube->Connect(front->This, right->Neighbours[2]);
        rubiks_cube->Connect(top->This, right->Neighbours[3]);

        //
        rubiks_cube->Connect(front->This, bottom->Neighbours[0]);
        rubiks_cube->Connect(right->This, bottom->Neighbours[1]);
        rubiks_cube->Connect(back->This, bottom->Neighbours[2]);
        rubiks_cube->Connect(left->This, bottom->Neighbours[3]);

        // 
        rubiks_cube->Connect(top->This, back->Neighbours[0]);
        rubiks_cube->Connect(left->This, back->Neighbours[1]);
        rubiks_cube->Connect(bottom->This, back->Neighbours[2]);
        rubiks_cube->Connect(right->This, back->Neighbours[3]);


        // Creat cubies
        auto qb1 = rubiks_cube->CreateComponent<Cubie>(BLUE);
        auto qb1_t = rubiks_cube->CreateComponent<Transform>();
        rubiks_cube->Connect(front_t->TransformOut, qb1_t->Parent);
        rubiks_cube->Connect(qb1_t->ModelOut, qb1->Model);

        auto qb2 = rubiks_cube->CreateComponent<Cubie>(BLUE, RED, BLACK, WHITE);
        auto qb2_t = rubiks_cube->CreateComponent<Transform>();
        qb2_t->MoveRelative(glm::vec3(0.0f, 1.0f, 1.0f));
        rubiks_cube->Connect(front_t->TransformOut, qb2_t->Parent);
        rubiks_cube->Connect(qb2_t->ModelOut, qb2->Model);

        auto qb3 = rubiks_cube->CreateComponent<Cubie>(BLUE, BLACK, BLACK, WHITE);
        auto qb3_t = rubiks_cube->CreateComponent<Transform>();
        qb3_t->MoveRelative(glm::vec3(0.0f, 1.0f, 0.0f));
        rubiks_cube->Connect(front_t->TransformOut, qb3_t->Parent);
        rubiks_cube->Connect(qb3_t->ModelOut, qb3->Model);

        auto qb4 = rubiks_cube->CreateComponent<Cubie>(BLUE, BLACK, ORANGE, WHITE);
        auto qb4_t = rubiks_cube->CreateComponent<Transform>();
        qb4_t->MoveRelative(glm::vec3(0.0f, 1.0f, -1.0f));
        rubiks_cube->Connect(front_t->TransformOut, qb4_t->Parent);
        rubiks_cube->Connect(qb4_t->ModelOut, qb4->Model);

        auto qb5 = rubiks_cube->CreateComponent<Cubie>(BLUE, RED);
        auto qb5_t = rubiks_cube->CreateComponent<Transform>();
        qb5_t->MoveRelative(glm::vec3(0.0f, 0.0f, 1.0f));
        rubiks_cube->Connect(front_t->TransformOut, qb5_t->Parent);
        rubiks_cube->Connect(qb5_t->ModelOut, qb5->Model);

        auto qb6 = rubiks_cube->CreateComponent<Cubie>(BLUE, BLACK, ORANGE);
        auto qb6_t = rubiks_cube->CreateComponent<Transform>();
        qb6_t->MoveRelative(glm::vec3(0.0f, 0.0f, -1.0f));
        rubiks_cube->Connect(front_t->TransformOut, qb6_t->Parent);
        rubiks_cube->Connect(qb6_t->ModelOut, qb6->Model);

        auto qb7 = rubiks_cube->CreateComponent<Cubie>(BLUE, RED, BLACK, BLACK, YELLOW);
        auto qb7_t = rubiks_cube->CreateComponent<Transform>();
        qb7_t->MoveRelative(glm::vec3(0.0f, -1.0f, 1.0f));
        rubiks_cube->Connect(front_t->TransformOut, qb7_t->Parent);
        rubiks_cube->Connect(qb7_t->ModelOut, qb7->Model);

        auto qb8 = rubiks_cube->CreateComponent<Cubie>(BLUE, BLACK, BLACK, BLACK, YELLOW);
        auto qb8_t = rubiks_cube->CreateComponent<Transform>();
        qb8_t->MoveRelative(glm::vec3(0.0f, -1.0f, 0.0f));
        rubiks_cube->Connect(front_t->TransformOut, qb8_t->Parent);
        rubiks_cube->Connect(qb8_t->ModelOut, qb8->Model);

        auto qb9 = rubiks_cube->CreateComponent<Cubie>(BLUE, BLACK, ORANGE, BLACK, YELLOW);
        auto qb9_t = rubiks_cube->CreateComponent<Transform>();
        qb9_t->MoveRelative(glm::vec3(0.0f, -1.0f, -1.0f));
        rubiks_cube->Connect(front_t->TransformOut, qb9_t->Parent);
        rubiks_cube->Connect(qb9_t->ModelOut, qb9->Model);
        */
    }
}

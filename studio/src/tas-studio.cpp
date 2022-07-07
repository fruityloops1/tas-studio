#include "client/Client.h"
#include "client/TasClient.h"
#include "file/KCollision.h"
#include "nlib/util.h"
#include "raylib.h"
#include "types.h"
#include "ui/Camera.h"
#include "ui/Scene.h"
#include <vector>

int main()
{
    fl::TasClient client;
    client.connect("192.168.188.27", 7032);

    SetTraceLogLevel(LOG_NONE);
    InitWindow(1920, 1080, "TAS Client");
    SetTargetFPS(60);
    auto& visual = fl::Scene::instance();

    fl::Camera camera;
    Camera3D cam;
    cam.projection = CAMERA_PERSPECTIVE;

    visual.checkerShader = LoadShader("res/shaders/normal.vs", "res/shaders/normal.fs");

    int cameraDirLoc = GetShaderLocation(visual.checkerShader, "cameraDirection");

    Model model = LoadModel("TreasureBox_Close.kcl.obj");

    while (!WindowShouldClose()) {
        // UpdateCamera(&camera);
        // camera.update();
        cam.fovy = visual.cameraInfo.fovy;
        cam.position = *(Vector3*)&visual.cameraInfo.pos;
        cam.target = *(Vector3*)&visual.cameraInfo.at;
        cam.up = *(Vector3*)&visual.cameraInfo.up;

        fl::Vector3f cameraDir = (visual.cameraInfo.at - visual.cameraInfo.pos).normalize();

        BeginDrawing();

        ClearBackground(BLACK);

        BeginMode3D(cam);

        SetShaderValue(visual.checkerShader, cameraDirLoc, &cameraDir, SHADER_UNIFORM_VEC3);
        DrawCube(*(Vector3*)&visual.playerPos, 0.55, 0.55, 0.55, RED);

        for (const fl::Scene::Actor* actor : visual.actors) {
            if (actor->kcl.valid) {
                fl::Vector3f pos = actor->trans * .01;
                printf("%s", actor->getName());
                for (int i = 0; i < actor->kcl.model.materialCount; i++) {
                    actor->kcl.model.materials[i].maps->color = WHITE;
                    actor->kcl.model.materials[i].shader = visual.checkerShader;
                }
                DrawModel(actor->kcl.model, { 0, 0, 0 }, .01, WHITE);
            } else
                DrawCube(*(Vector3*)&actor->trans, .3, .3, .3, BLUE);
        }

        EndMode3D();
        EndDrawing();
    }

    return 0;
}
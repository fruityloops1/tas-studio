#include "client/Client.h"
#include "client/TasClient.h"
#include "file/KCollision.h"
#include "nlib/types.h"
#include "nlib/util.h"
#include "oead/sarc.h"
#include "oead/yaz0.h"
#include "raylib.h"
#include "raymath.h"
#include "types.h"
#include "ui/Camera.h"
#include "ui/Scene.h"
#include <filesystem>
#include <vector>

void initActorKCL(fl::Scene::Actor* actor) {
    auto& scene = fl::Scene::instance();
    std::string szsPath = nlib::util::format("res/ObjectData/%s.szs", actor->getName());

    if (!std::filesystem::exists(szsPath)) {
        printf("File does not exist: %s\n", szsPath.c_str());
        return;
    }

    std::vector<u8> szsData = nlib::util::readFile<u8>(szsPath);
    std::vector<u8> sarcData = oead::yaz0::Decompress(szsData);
    oead::Sarc sarc(sarcData);
    const auto& file = sarc.GetFile(nlib::util::format("%s.kcl", actor->getKCLName()));
    if (!file.has_value()) {
        printf("File has no value: %s (%s)\n", actor->getKCLName(), szsPath.c_str());
        return;
    }

    try {
        fl::KCL kcl(file->data);
        std::string objName = nlib::util::format("%s.obj", file->name.data());
        std::string mtlName = nlib::util::format("%s.mtl", file->name.data());
        std::string objStr = nlib::util::format("mtllib %s\n", mtlName.c_str());
        objStr.append(kcl.toObj());
        std::string mtlStr = kcl.toMtl();
        std::vector<u8> obj(objStr.begin(), objStr.end());
        std::vector<u8> mtl(mtlStr.begin(), mtlStr.end());

        nlib::util::writeFile(objName, std::span<const u8>(obj));
        nlib::util::writeFile(mtlName, std::span<const u8>(mtl));
        actor->kcl.model = LoadModel(objName.c_str());

        Color colors[] = {WHITE, RED,     BLUE,   GREEN,      YELLOW, ORANGE, PINK,
                          LIME,  SKYBLUE, PURPLE, DARKPURPLE, BROWN,  BLACK};

        for (int i = 0; i < actor->kcl.model.materialCount; i++) {
            actor->kcl.model.materials[i].maps->color = colors[i % 11];
            actor->kcl.model.materials[i].shader = scene.checkerShader;
        }

        actor->kcl.valid = true;
        actor->kcl.initPending = false;
        // std::filesystem::remove(objName);
        // std::filesystem::remove(mtlName);
    } catch (const nlib::Exception& ex) {
        // myballs
        printf("Invalid kcl: %s.kcl (%s)\n", actor->getName(), actor->getKCLName());
    }
}

int main() {
    fl::TasClient client;
    client.connect("192.168.188.27", 7032);

    SetTraceLogLevel(LOG_NONE);
    InitWindow(1920, 1080, "TAS Client");
    SetTargetFPS(60);
    auto& scene = fl::Scene::instance();

    fl::Camera camera;
    Camera3D cam;
    cam.projection = CAMERA_PERSPECTIVE;

    scene.checkerShader = LoadShader("res/shaders/normal.vs", "res/shaders/normal.fs");

    int cameraDirLoc = GetShaderLocation(scene.checkerShader, "cameraDirection");
    while (!WindowShouldClose()) {
        // UpdateCamera(&camera);
        // camera.update();
        cam.fovy = scene.cameraInfo.fovy;
        cam.position = *(Vector3*)&scene.cameraInfo.pos;
        cam.target = *(Vector3*)&scene.cameraInfo.at;
        cam.up = *(Vector3*)&scene.cameraInfo.up;

        fl::Vector3f cameraDir = (scene.cameraInfo.at - scene.cameraInfo.pos).normalize();

        BeginDrawing();

        ClearBackground(BLACK);

        BeginMode3D(cam);

        SetShaderValue(scene.checkerShader, cameraDirLoc, &cameraDir, SHADER_UNIFORM_VEC3);

        DrawCube(*(Vector3*)&scene.playerPos, 0.25, 0.25, 0.25, RED);
        DrawCube(*(Vector3*)&scene.cappyPos, 0.25, 0.25, 0.25, RED);

        if (!scene.playerSensors.empty()) {
            auto& collider = scene.playerSensors[0];
            Color col = GREEN;
            col.a = 90;
            DrawSphere(*(Vector3*)&collider.pos, collider.radius / 100, col);
        }

        for (int i = 1; i < scene.playerSensors.size(); i++) {
            auto& sensor = scene.playerSensors[i];
            Color col = PINK;
            col.a = 25;
            DrawSphere(*(Vector3*)&sensor.pos, sensor.radius / 100, col);
        }

        for (fl::Scene::Actor* actor : scene.actors) {
            if (!actor || !actor->isAlive)
                continue;
            fl::Vector3f pos = actor->trans * .01;
            if (actor->kcl.initPending)
                initActorKCL(actor);
            if (actor->kcl.valid) {
                actor->kcl.model.transform =
                    QuaternionToMatrix({actor->rotate.x, actor->rotate.y, actor->rotate.z, actor->rotate.w});
                DrawModel(actor->kcl.model, *(Vector3*)&pos, .01, WHITE);
            } else
                DrawCube(*(Vector3*)&pos, .3, .3, .3, BLUE);
        }

        EndMode3D();
        EndDrawing();
    }

    return 0;
}
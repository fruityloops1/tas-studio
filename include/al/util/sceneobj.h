#pragma once

#include "al/scene/SceneObjHolder.h"
#include "game/GameData/GameDataHolderBase.h"
namespace al {

bool isExistSceneObj(const al::IUseSceneObjHolder* holder, int id);
void setSceneObj(const al::IUseSceneObjHolder* holder, al::ISceneObj* sceneobj, int id);
ISceneObj* tryGetSceneObj(const al::IUseSceneObjHolder* holder, int id);

} // namespace al
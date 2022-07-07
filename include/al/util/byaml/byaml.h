#pragma once

#include "al/actor/ActorInitInfo.h"
#include "al/actor/Placement.h"
#include "sead/gfx/seadColor.h"
#include "sead/math/seadVector.h"
namespace al {

const PlacementInfo& getPlacementInfo(const al::ActorInitInfo&);
bool tryGetPlacementInfoByKey(al::PlacementInfo* out, const al::PlacementInfo&, const char* key);
int getCountPlacementInfo(const al::PlacementInfo&);
bool tryGetPlacementInfoAndKeyNameByIndex(al::PlacementInfo* piOut, const char** keyOut, const al::PlacementInfo&, int);

bool tryGetArg(int*, const al::ActorInitInfo&, const char*);
bool tryGetArg(int*, const al::PlacementInfo&, const char*);
bool tryGetArg(float*, const al::ActorInitInfo&, const char*);
bool tryGetArg(float*, const al::PlacementInfo&, const char*);
bool tryGetArg(bool*, const al::ActorInitInfo&, const char*);
bool tryGetArg(bool*, const al::PlacementInfo&, const char*);
bool tryGetArgV3f(sead::Vector3f*, const al::ActorInitInfo&, const char*);
bool tryGetArgV3f(sead::Vector3f*, const al::PlacementInfo&, const char*);
bool tryGetStringArg(const char**, const al::PlacementInfo&, const char*);
bool tryGetStringArg(const char**, const al::ActorInitInfo&, const char*);
bool tryGetArgColor(sead::Color4f*, const al::ActorInitInfo&, const char*);
bool tryGetArgColor(sead::Color4f*, const al::PlacementInfo&, const char*);

} // namespace al
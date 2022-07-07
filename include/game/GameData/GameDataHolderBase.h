#pragma once

#include "al/actor/ActorInitInfo.h"
namespace al {

class ISceneObj {
public:
    virtual const char* getSceneObjName() { return ""; };
    virtual ~ISceneObj() {};
    virtual void initAfterPlacementSceneObj(const al::ActorInitInfo&) {};
    virtual void initSceneObj() {};
};

};

#include "al/hio/HioNode.h"
#include "al/message/MessageSystem.h"

class GameDataHolderBase : public al::ISceneObj, public al::IUseMessageSystem, public al::HioNode {
public:
};
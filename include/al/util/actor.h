#pragma once

#include "al/LiveActor/LiveActor.h"
#include "al/actor/ActorInitInfo.h"
#include "sead/prim/seadSafeString.h"

namespace al {
void registerSubActor(al::LiveActor*, al::LiveActor*);
void initCreateActorNoPlacementInfo(al::LiveActor*, const al::ActorInitInfo&);
void initSubActorKeeperNoFile(al::LiveActor*, const al::ActorInitInfo&, int);
void initMapPartsActor(al::LiveActor*, const al::ActorInitInfo&, const char*);
void initActorWithArchiveName(al::LiveActor*, const al::ActorInitInfo&, const sead::SafeString&, const char*);
void initActor(al::LiveActor*, const al::ActorInitInfo&);

void rotateQuatXDirDegree(al::LiveActor*, float);
void rotateQuatYDirDegree(al::LiveActor*, float);
void rotateQuatZDirDegree(al::LiveActor*, float);

void initActorPoseTQSV(al::LiveActor*);
void initActorPoseTQGSV(al::LiveActor*);

void startNerveAction(al::LiveActor*, const char*);

void initActorBgmKeeper(al::LiveActor*, const al::ActorInitInfo&, const char*);
LiveActor* createLinksActorFromFactory(const al::ActorInitInfo&, const char* linkName, int index);

} // namespace al
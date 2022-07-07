#pragma once

#include "al/actor/ActorInitInfo.h"
#include "al/layout/LayoutActor.h"
#include "al/layout/LayoutInitInfo.h"

namespace al {

const LayoutInitInfo& getLayoutInitInfo(const al::ActorInitInfo&);
void initLayoutActor(al::LayoutActor*, const al::LayoutInitInfo&, const char*, const char*);

bool isActionEnd(const al::IUseLayoutAction*, const char*);

} // namespace al
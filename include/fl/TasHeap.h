#pragma once

#include <sead/heap/seadFrameHeap.h>

namespace fl {

bool tryCreateTasHeap();
sead::FrameHeap*& getTasHeap();

} // namespace fl
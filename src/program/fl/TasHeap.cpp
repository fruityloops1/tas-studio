#include "fl/TasHeap.h"
#include "al/util.hpp"

bool fl::tryCreateTasHeap()
{
    if (getTasHeap() == nullptr) {
        getTasHeap() = sead::FrameHeap::create(0x1000000, "TasHeap", al::getSequenceHeap(), 8, sead::Heap::HeapDirection::cHeapDirection_Reverse, false);
        return true;
    }
    return false;
}

sead::FrameHeap*& fl::getTasHeap()
{
    static sead::FrameHeap* heap = nullptr;

    return heap;
}
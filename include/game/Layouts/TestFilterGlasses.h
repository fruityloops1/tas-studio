#pragma once

#include "al/layout/LayoutActor.h"
#include "al/layout/LayoutInitInfo.h"
#include "types.h"

class TestFilterGlasses : public al::LayoutActor {
public:
    TestFilterGlasses(const char*, const al::LayoutInitInfo&, const char*);
    ~TestFilterGlasses();
    void startAppear();
    void end();

    spad(gap, 0x100);
};
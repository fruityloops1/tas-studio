#pragma once

#include "AreaObjFactory.h"
#include "AreaObjFactoryEntries100.h"

class ProjectAreaFactory : public al::AreaObjFactory {
public:
    ProjectAreaFactory();

    void* mGraphicsArea;
    int someShit = 1;
};
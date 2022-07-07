#pragma once

#include "al/actor/IUseName.h"
namespace al {

class LayoutActionKeeper {
};

class IUseLayoutAction : virtual public al::IUseName {
    virtual al::LayoutActionKeeper* getLayoutActionKeeper() const = 0;
};

} // namespace al
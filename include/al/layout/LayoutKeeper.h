#pragma once

#include "al/actor/IUseName.h"

namespace al {

class LayoutKeeper {
};

class IUseLayout : virtual public al::IUseName {

    virtual al::LayoutKeeper* getLayoutKeeper() const = 0;
};
} // namespace al
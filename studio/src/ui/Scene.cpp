#include "ui/Scene.h"
#include "types.h"

namespace fl {

Scene& Scene::instance()
{
    static Scene inst;
    return inst;
}

} // namespace fl
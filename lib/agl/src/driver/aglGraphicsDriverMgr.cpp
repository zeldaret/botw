#include "agl/driver/aglGraphicsDriverMgr.h"

namespace agl::driver {
SEAD_SINGLETON_DISPOSER_IMPL(GraphicsDriverMgr)

GraphicsDriverMgr::GraphicsDriverMgr() {
    mDefaultCommandBuffer = nullptr;
    _30 = nullptr;
}

GraphicsDriverMgr::~GraphicsDriverMgr() = default;
}  // namespace agl::driver
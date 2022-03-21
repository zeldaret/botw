#pragma once

#include <heap/seadDisposer.h>
#include <hostio/seadHostIONode.h>
#include "agl/driver/aglGraphicsDriverMgr.h"

namespace agl::driver {

class NVNMgr : public GraphicsDriverMgr {
    // TODO: This is wrong and should actually touch the GraphicsDriverMgr implementation
    SEAD_SINGLETON_DISPOSER(NVNMgr)
public:
    NVNMgr();
    ~NVNMgr() override;

private:
};

// TODO: need sead::Graphics reversing...
// static_assert(sizeof(NVNMgr) == 0x548);

};  // namespace agl::driver
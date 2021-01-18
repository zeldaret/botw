#pragma once

#include <heap/seadDisposer.h>

namespace ksys {

// TODO
class CookingMgr {
    SEAD_SINGLETON_DISPOSER(CookingMgr)
    CookingMgr();
    // TODO: inline
    ~CookingMgr();
};

}  // namespace ksys

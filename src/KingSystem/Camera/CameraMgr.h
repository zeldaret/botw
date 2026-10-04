#pragma once

#include <heap/seadDisposer.h>
#include <hostio/seadHostIONode.h>

namespace sead {
class LookAtCamera;
}

namespace ksys {

// FIXME: incomplete
class CameraMgr : public sead::hostio::Node {
    SEAD_SINGLETON_DISPOSER(CameraMgr)
    CameraMgr() = default;
    virtual ~CameraMgr() = default;

public:
    sead::LookAtCamera* getLookAtCamera() const;
};

}  // namespace ksys

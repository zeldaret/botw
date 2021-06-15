#pragma once

#include <heap/seadDisposer.h>
#include <mc/seadWorkerMgr.h>
#include "KingSystem/Utils/Types.h"

namespace ksys {

class HavokWorkerMgr : public sead::WorkerMgr {
    SEAD_SINGLETON_DISPOSER(HavokWorkerMgr)
    HavokWorkerMgr() = default;
    ~HavokWorkerMgr() override;

public:
    // TODO: implement. This is almost exactly the same as sead::WorkerMgr::initialize
    // but with a custom Worker class that calls out to Havok.
    void initialize(const InitializeArg& arg) override;

    u32 getWorkerThreadId(int idx) const;
};
KSYS_CHECK_SIZE_NX150(HavokWorkerMgr, 0xd8);

}  // namespace ksys

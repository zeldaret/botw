#include "KingSystem/System/HavokWorkerMgr.h"

namespace ksys {

SEAD_SINGLETON_DISPOSER_IMPL(HavokWorkerMgr)

HavokWorkerMgr::~HavokWorkerMgr() = default;

u32 HavokWorkerMgr::getWorkerThreadId(int idx) const {
    return mWorkers[idx]->getId();
}

}  // namespace ksys

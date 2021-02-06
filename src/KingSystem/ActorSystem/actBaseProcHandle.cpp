#include "KingSystem/ActorSystem/actBaseProcHandle.h"
#include "KingSystem/Utils/InitTimeInfo.h"

namespace ksys::act {

static util::InitTimeInfo sInfo;

BaseProcHandle::BaseProcHandle() {
    mUnit = nullptr;
    mFlag = 0;
}

BaseProcHandle::~BaseProcHandle() {
    if (mUnit) {
        mUnit->deleteProc(0, this);
        mUnit = nullptr;
    }
    mFlag = 0;
}

bool BaseProcHandle::procReady() {
    return mUnit && mUnit->isReady();
}

BaseProc* BaseProcHandle::getProc() {
    if (mUnit)
        return mUnit->getProc();

    return nullptr;
}

}  // namespace ksys::act

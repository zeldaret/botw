#include "KingSystem/ActorSystem/actBaseProcHandle.h"

namespace ksys::act {

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
#include "Game/DLC/aocManager.h"
#include <filedevice/seadFileDeviceMgr.h>
#include "KingSystem/Utils/SafeDelete.h"

#ifdef NNSDK
#include <nn/fs.h>
#endif

namespace uking::aoc {

SEAD_SINGLETON_DISPOSER_IMPL(Manager)

Manager::Manager() : mGdtReinitSlot{this, &Manager::onGdtReinit} {
    resetFlags();
}

Manager::~Manager() {
    if (auto* gdm = ksys::gdt::Manager::instance())
        gdm->removeReinitCallback(mGdtReinitSlot);

    mFileDevicePrefix.deregister();
    mFileDevicePrefix2.deregister();
    mVersionFileDevPrefix.deregister();

    if (mFileDevice) {
        sead::FileDeviceMgr::instance()->unmount("aoc");
        ksys::util::safeDelete(mFileDevice);
    }

#ifdef NNSDK
    if (mAocFsCache) {
        nn::fs::Unmount("aoc");
        ksys::util::safeDelete(mAocFsCache);
    }
#endif
}

void Manager::resetFlags() {
    mFlagAocVerAtLastPlay = ksys::gdt::InvalidHandle;
    mFlagLatestAocVerPlayed = ksys::gdt::InvalidHandle;
    mFlagHasAocVer1 = ksys::gdt::InvalidHandle;
    mFlagHasAocVer2 = ksys::gdt::InvalidHandle;
    mFlagHasAocVer3 = ksys::gdt::InvalidHandle;
}

}  // namespace uking::aoc

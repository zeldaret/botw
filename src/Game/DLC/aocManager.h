#pragma once

#include <heap/seadDisposer.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Resource/resHandle.h"
#include "KingSystem/Resource/resResourceMgrTask.h"

namespace sead {
class FileDevice;
}

namespace uking::aoc {

// TODO
class Manager {
    SEAD_SINGLETON_DISPOSER(Manager)
    Manager();
    ~Manager();

public:
    u32 getVersion() const { return mVersion; }

    /// @return Whether the Master Trials DLC is supported.
    bool hasAoc2() const { return mVersion >= 0x200; }

    /// @return Whether the Champion's Ballad DLC is supported.
    bool hasAoc3() const { return mVersion >= 0x300; }

private:
    sead::FileDevice* mFileDevice{};
    ksys::res::FileDevicePrefix mFileDevicePrefix;

    ksys::res::Handle mVersionResHandle;
    sead::FixedSafeString<16> mVersionString;
    u32 mVersion{};
    // TODO: more fields
};

}  // namespace uking::aoc

#pragma once

#include <container/seadSafeArray.h>
#include <heap/seadDisposer.h>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include <prim/seadStorageFor.h>
#include <prim/seadTypedBitFlag.h>
#include "KingSystem/GameData/gdtManager.h"
#include "KingSystem/Resource/resHandle.h"
#include "KingSystem/Resource/resResourceMgrTask.h"
#include "KingSystem/Utils/Types.h"

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
    enum class Flag : u8 {

    };

    struct DLCPosition {
        sead::Vector3f translate = sead::Vector3f::zero;
        sead::Vector3f rotate = sead::Vector3f::zero;
        sead::Vector3f translate2 = sead::Vector3f::zero;
        float scale = 0.0;
        ksys::gdt::FlagHandle flag_handle = ksys::gdt::InvalidHandle;
    };
    KSYS_CHECK_SIZE_NX150(DLCPosition, 0x2c);

    struct VersionFile {
        ksys::res::Handle file_handle;
        sead::FixedSafeString<16> string;
    };
    KSYS_CHECK_SIZE_NX150(VersionFile, 0x78);

    void resetFlags();
    void onGdtReinit(ksys::gdt::Manager::ReinitEvent* event);

    sead::FileDevice* mFileDevice{};

    ksys::res::FileDevicePrefix mVersionFileDevPrefix;
    sead::StorageFor<VersionFile, true> mVersionFile{sead::ZeroInitializeTag{}};
    u32 mVersion{};

    ksys::res::Handle mAocMapMainFieldPack;
    ksys::res::FileDevicePrefix mFileDevicePrefix;
    ksys::res::Handle* mAocArchive{};
    ksys::res::FileDevicePrefix mFileDevicePrefix2;

    sead::SafeArray<DLCPosition, 20> mDLCPositions;

    ksys::gdt::FlagHandle mFlagAocVerAtLastPlay{};
    ksys::gdt::FlagHandle mFlagLatestAocVerPlayed{};
    ksys::gdt::FlagHandle mFlagHasAocVer1{};
    ksys::gdt::FlagHandle mFlagHasAocVer2{};
    ksys::gdt::FlagHandle mFlagHasAocVer3{};
    ksys::gdt::Manager::ReinitSignal::Slot mGdtReinitSlot;

    sead::TypedBitFlag<Flag> mFlags{};
#ifdef NNSDK
    u8* mAocFsCache{};
#endif
};
KSYS_CHECK_SIZE_NX150(Manager, 0x598);

}  // namespace uking::aoc

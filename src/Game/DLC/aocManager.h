#pragma once

#include <container/seadSafeArray.h>
#include <heap/seadDisposer.h>
#include <math/seadVector.h>
#include <prim/seadBitFlag.h>
#include <prim/seadEnum.h>
#include <prim/seadSafeString.h>
#include <prim/seadStorageFor.h>
#include "KingSystem/GameData/gdtManager.h"
#include "KingSystem/Resource/resHandle.h"
#include "KingSystem/Resource/resResourceMgrTask.h"
#include "KingSystem/Utils/Types.h"

namespace ksys {
class OverlayArena;
}

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
    void init(sead::Heap* heap);

    u32 getVersion() const { return mVersion; }

    /// @return Whether the Master Trials DLC is supported.
    bool hasAoc2() const { return mVersion >= 0x200; }

    /// @return Whether the Champion's Ballad DLC is supported.
    bool hasAoc3() const { return mVersion >= 0x300; }

    void loadAocMainFieldPack(ksys::OverlayArena* arena);
    void registerAocMainFieldPack();
    void unloadAocMainFieldPack();

    sead::FileDevice* getFileDeviceForMapFile(const sead::SafeString& path) const;
    bool getFileDeviceForMap(sead::FileDevice** p_file_device, ksys::res::Handle** p_handle,
                             const sead::SafeString& path);
    sead::FileDevice* getFileDeviceForStaticCompound(const sead::SafeString& path) const;
    sead::FileDevice* getFileDeviceForTeraMesh(const sead::SafeString& path) const;
    sead::FileDevice* getFileDeviceForNavMesh(const sead::SafeString& path) const;
    sead::FileDevice* getFileDeviceForTerrain(const sead::SafeString& path) const;
    sead::FileDevice* getFileDeviceForGame(const sead::SafeString& path) const;
    sead::FileDevice* getFileDeviceForUI(const sead::SafeString& path) const;

    bool isAocFile(const sead::SafeString& path, const sead::SafeString& dir,
                   const sead::SafeString& dir_aoc_field,
                   const sead::SafeString& dir_main_field_dungeon,
                   const sead::SafeString& dir_cdungeon) const;
    static bool isAocDungeon(const sead::SafeString& map_name);
    static bool isAocMap(const sead::SafeString& map_type, const sead::SafeString& map_name);
    static bool isAocField(const sead::SafeString& map_type);

    sead::FileDevice* getFileDeviceForDungeonPack(const sead::SafeString& path) const;
    void registerAocPack(ksys::res::Handle* pack);
    bool aocPackHasFile(const sead::SafeString& path) const;

    bool changeMoviePath(sead::BufferedSafeString& path) const;

    void parseAocMainFieldStaticInfo(const al::ByamlIter& iter);
    // TODO: figure out what this does
    bool getSomePos(sead::Vector3f* translate, u32* p_mask, u32* mask);

    bool parseVersion();
    void setGameDataFlags() const;

private:
    SEAD_ENUM(GameDataFlag, AoCVerAtLastPlay ,LatestAoCVerPlayed ,HasAoCVer1 ,HasAoCVer2 ,HasAoCVer3)
    SEAD_ENUM(VersionError, TooNew, TooOld)

    struct DLCPosition {
        sead::Vector3f translate = sead::Vector3f::zero;
        sead::Vector3f rotate = sead::Vector3f::zero;
        sead::Vector3f translate2 = sead::Vector3f::zero;
        float scale = 0.0;
        ksys::gdt::FlagHandle flag_handle = ksys::gdt::InvalidHandle;
    };
    KSYS_CHECK_SIZE_NX150(DLCPosition, 0x2c);

    struct VersionFile {
        bool readVersion();

        ksys::res::Handle file_handle;
        sead::FixedSafeString<16> string;
    };
    KSYS_CHECK_SIZE_NX150(VersionFile, 0x78);

    void loadVersionFile();
    void checkVersion();

    void resetFlags();
    void initGameData();
    void reinitFlags();
    void onGdtReinit(ksys::gdt::Manager::ReinitEvent* event);

    sead::FileDevice* mFileDevice{};

    ksys::res::FileDevicePrefix mVersionFileDevPrefix;
    sead::StorageFor<VersionFile, true> mVersionFile{sead::ZeroInitializeTag{}};
    u32 mVersion{};

    ksys::res::Handle mAocMainFieldPack;
    ksys::res::FileDevicePrefix mAocMainFieldPackPrefix;
    ksys::res::Handle* mAocPack{};
    ksys::res::FileDevicePrefix mAocPackPrefix;

    sead::SafeArray<DLCPosition, 20> mDLCPositions;

    ksys::gdt::FlagHandle mFlagAocVerAtLastPlay{};
    ksys::gdt::FlagHandle mFlagLatestAocVerPlayed{};
    ksys::gdt::FlagHandle mFlagHasAocVer1{};
    ksys::gdt::FlagHandle mFlagHasAocVer2{};
    ksys::gdt::FlagHandle mFlagHasAocVer3{};
    ksys::gdt::Manager::ReinitSignal::Slot mGdtReinitSlot;

    sead::BitFlag8 mVersionFlags{};
#ifdef NNSDK
    u8* mAocFsCache{};
#endif
};
KSYS_CHECK_SIZE_NX150(Manager, 0x598);

}  // namespace uking::aoc

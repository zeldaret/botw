#include "Game/DLC/aocManager.h"
#include <container/seadBuffer.h>
#include <filedevice/seadFileDeviceMgr.h>
#include <prim/seadStringBuilder.h>
#include <resource/seadSharcArchiveRes.h>
#include "KingSystem/Resource/resLoadRequest.h"
#include "KingSystem/Resource/resResourceMgrTask.h"
#include "KingSystem/Utils/InitTimeInfo.h"
#include "KingSystem/Utils/SafeDelete.h"

#ifdef NNSDK
#include <filedevice/nin/seadNinAocFileDeviceNin.h>
#include <nn/aoc.h>
#include <nn/fs.h>
#include <prim/seadStringUtil.h>
#endif

namespace uking::aoc {

namespace {

struct DungeonInfo {
    int number;
    sead::SafeString flag;
};

ksys::util::InitConstants sInitConstants;
DungeonInfo sDungeonInfoData[] = {
    {120, "Defeat_OneHitDungeon001"},
    {121, "BalladOfHeroGerudo_AppearDungeon03"},
    {122, "Defeat_OneHitDungeon002"},
    {123, "Defeat_OneHitDungeon003"},
    {124, "BalladOfHeroZora_AppearDungeon01"},
    {125, "BalladOfHeroZora_AppearDungeon02"},
    {126, "BalladOfHeroZora_AppearDungeon03"},
    {127, "BalladOfHeroRito_TargetHittingSuccess"},
    {128, "BalladOfHeroRito_AppearDungeon03"},
    {129, "BalladOfHeroRito_AppearDungeon02"},
    {130, "BalladOfHeroGoron_FirstKillGolemR"},
    {131, "BalladOfHeroGoron_AppearDungeon01"},
    {132, "BalladOfHeroGoron_AppearDungeon03"},
    {133, "BalladOfHeroGerudo_AppearDungeon02"},
    {134, "BalladOfHeroGerudo_AppearDungeon01"},
    {135, "Defeat_OneHitDungeon004"},
};
sead::Buffer<DungeonInfo> sDungeonInfo{sDungeonInfoData};
constexpr int NumDungeons = 16;

}  // namespace

SEAD_SINGLETON_DISPOSER_IMPL(Manager)

Manager::Manager() : mGdtReinitSlot{this, &Manager::onGdtReinit} {
    resetFlags();
}

Manager::~Manager() {
    if (auto* gdm = ksys::gdt::Manager::instance())
        gdm->removeReinitCallback(mGdtReinitSlot);

    mAocMainFieldPackPrefix.deregister();
    mAocPackPrefix.deregister();
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

void Manager::init(sead::Heap* heap) {
#ifdef NNSDK
    std::array<int, 2> dlc_info;
    if (nn::aoc::ListAddOnContent(dlc_info.data(), 0, dlc_info.size()) == dlc_info.size() &&
        (dlc_info[0] == 1 || dlc_info[1] == 1)) {
        size_t cache_size = 0;
        nn::fs::QueryMountAddOnContentCacheSize(&cache_size, 1);
        const size_t cache_size_ = cache_size;
        mAocFsCache = static_cast<u8*>(heap->tryAlloc(cache_size_, sizeof(void*)));

        nn::fs::MountAddOnContent("aoc", 1, mAocFsCache, cache_size);

        mFileDevice = new (heap) sead::NinAocFileDevice("aoc");
        sead::FileDeviceMgr::instance()->mount(mFileDevice, "aoc");
        loadVersionFile();
    }
#endif
}

void Manager::loadVersionFile() {
    if (!mFileDevice)
        return;

    mVersionFileDevPrefix.registerPrefix("Aoc/0010/", mFileDevice, false);

    ksys::res::LoadRequest req;
    req.mRequester = "aocManager";
    req._26 = false;
    req.mAocFileDevice = mFileDevice;
    const sead::SafeString path = "System/AocVersion.txt";
    mVersionFile->file_handle.requestLoad(path, &req);
}

void Manager::loadAocMainFieldPack(ksys::OverlayArena* arena) {
    if (!hasAoc3())
        return;

    auto* device = mFileDevice;
    if (!device)
        return;

    ksys::res::LoadRequest req;
    req.mRequester = "aocManager";
    req._8 = true;
    req._26 = false;
    req.mAocFileDevice = device;
    req.mArena = arena;
    mAocMainFieldPack.requestLoad("Pack/AocMainField.pack", &req);
}

void Manager::registerAocMainFieldPack() {
    mAocMainFieldPack.waitForReady();
    mAocMainFieldPack.parseResource(nullptr);
    if (mAocMainFieldPack.isSuccess())
        mAocMainFieldPackPrefix.registerPrefix("Aoc/0010/", mAocMainFieldPack.getResource(), false);
}

void Manager::unloadAocMainFieldPack() {
    mAocMainFieldPackPrefix.deregister();
    mAocMainFieldPack.requestUnload();
}

sead::FileDevice* Manager::getFileDeviceForMapFile(const sead::SafeString& path) const {
    if (!hasAoc2())
        return nullptr;

    auto* device = mFileDevice;

    if (aocPackHasFile(path))
        return nullptr;

    if (path.startsWith("Map/MainField/"))
        return device;

    if (hasAoc3() && path.startsWith("Map/MainFieldDungeon/"))
        return device;

    if (isAocFile(path, "Map/", "Map/AocField/", "Map/MainFieldDungeon/", "Map/CDungeon/"))
        return device;

    return nullptr;
}

bool Manager::getFileDeviceForMap(sead::FileDevice** p_file_device, ksys::res::Handle** p_handle,
                                  const sead::SafeString& path) {
    if (!hasAoc2())
        return false;

    auto* device = mFileDevice;

    if (path.startsWith("Map/MainField/")) {
        if (mAocMainFieldPack.isSuccess())
            *p_handle = &mAocMainFieldPack;
        else
            *p_file_device = device;
        return true;
    }

    if (aocPackHasFile(path))
        return false;

    if (hasAoc3() && path.startsWith("Map/MainFieldDungeon/")) {
        *p_file_device = device;
        return true;
    }

    if (isAocFile(path, "Map/", "Map/AocField/", "Map/MainFieldDungeon/", "Map/CDungeon/")) {
        *p_file_device = device;
        return true;
    }

    return false;
}

sead::FileDevice* Manager::getFileDeviceForStaticCompound(const sead::SafeString& path) const {
    if (!hasAoc2())
        return nullptr;

    auto* device = mFileDevice;

    if (aocPackHasFile(path))
        return nullptr;

    if (isAocFile(path, "Physics/StaticCompound/", "Physics/StaticCompound/AocField/",
                  "Physics/StaticCompound/MainFieldDungeon/", "Physics/StaticCompound/CDungeon/")) {
        return device;
    }

    return nullptr;
}

sead::FileDevice* Manager::getFileDeviceForTeraMesh(const sead::SafeString& path) const {
    if (!hasAoc2())
        return nullptr;

    if (path.startsWith("Physics/TeraMeshRigidBody/AocField/"))
        return mFileDevice;

    return nullptr;
}

sead::FileDevice* Manager::getFileDeviceForNavMesh(const sead::SafeString& path) const {
    if (!hasAoc2())
        return nullptr;

    auto* device = mFileDevice;

    if (aocPackHasFile(path))
        return nullptr;

    if (isAocFile(path, "NavMesh/", "NavMesh/AocField/", "NavMesh/MainFieldDungeon/",
                  "NavMesh/CDungeon/")) {
        return device;
    }

    return nullptr;
}

sead::FileDevice* Manager::getFileDeviceForTerrain(const sead::SafeString& path) const {
    if (!hasAoc2())
        return nullptr;

    if (path.startsWith("Terrain/A/AocField"))
        return mFileDevice;

    return nullptr;
}

sead::FileDevice* Manager::getFileDeviceForGame(const sead::SafeString& path) const {
    if (!hasAoc2())
        return nullptr;

    if (path.startsWith("Game/AocField/"))
        return mFileDevice;

    return nullptr;
}

sead::FileDevice* Manager::getFileDeviceForUI(const sead::SafeString& path) const {
    if (!hasAoc3())
        return nullptr;

    if (path.startsWith("UI/StaffRollDLC/"))
        return mFileDevice;

    return nullptr;
}

bool Manager::isAocFile(const sead::SafeString& path, const sead::SafeString& dir,
                        const sead::SafeString& dir_aoc_field,
                        const sead::SafeString& dir_main_field_dungeon,
                        const sead::SafeString& dir_cdungeon) const {
    if (!path.startsWith(dir))
        return false;

    if (path.startsWith(dir_aoc_field))
        return true;

    if (path.startsWith(dir_main_field_dungeon)) {
        const auto rel_path = path.getPart(dir_main_field_dungeon.calcLength());
        if (rel_path.startsWith("RemainsElectric"))
            return false;
        if (rel_path.startsWith("RemainsFire"))
            return false;
        if (rel_path.startsWith("RemainsWater"))
            return false;
        if (rel_path.startsWith("RemainsWind"))
            return false;
        return true;
    }

    if (path.startsWith(dir_cdungeon)) {
        const auto rel_path = path.getPart(dir_cdungeon.calcLength());
        return isAocDungeon(rel_path);
    }

    return false;
}

static bool isAocDungeonNumber(const sead::SafeString& number) {
    int num;
    sead::FixedSafeString<4> buffer;
    buffer.copy(number, 3);
    return sead::StringUtil::tryParseS32(&num, buffer, sead::StringUtil::CardinalNumber::Base10) &&
           num >= 120;
}

bool Manager::isAocDungeon(const sead::SafeString& map_name) {
    if (!map_name.startsWith("Dungeon"))
        return true;
    const auto number = map_name.getPart(sead::SafeString("Dungeon").calcLength());
    return isAocDungeonNumber(number);
}

bool Manager::isAocMap(const sead::SafeString& map_type, const sead::SafeString& map_name) {
    if (isAocField(map_type))
        return true;

    if (map_type == "MainFieldDungeon") {
        if (map_name == "RemainsElectric")
            return false;
        if (map_name == "RemainsFire")
            return false;
        if (map_name == "RemainsWater")
            return false;
        if (map_name == "RemainsWind")
            return false;
        return true;
    }

    if (map_type == "CDungeon")
        return isAocDungeon(map_name);

    return false;
}

bool Manager::isAocField(const sead::SafeString& map_type) {
    return map_type == "AocField";
}

sead::FileDevice* Manager::getFileDeviceForDungeonPack(const sead::SafeString& path) const {
    if (!hasAoc3())
        return nullptr;

    auto* device = mFileDevice;

    const sead::SafeString prefix = "Pack/";
    const auto prefix_len = prefix.calcLength();

    if (!path.startsWith(prefix))
        return nullptr;

    const auto rel_path = path.getPart(prefix_len);

    if (rel_path.startsWith("Dungeon") && !isAocDungeon(rel_path))
        device = nullptr;

    return device;
}

void Manager::registerAocPack(ksys::res::Handle* pack) {
    mAocPack = pack;
    if (pack) {
        mAocPackPrefix.registerPrefix("Aoc/0010/", pack->getResource(), true);
    } else {
        mAocPackPrefix.deregister();
    }
}

bool Manager::aocPackHasFile(const sead::SafeString& path) const {
    if (!mAocPack)
        return false;

    const auto* res = sead::DynamicCast<sead::SharcArchiveRes>(mAocPack->getResource());
    if (!res)
        return false;

    sead::FixedStringBuilder<0x81> builder;
    builder.copy(path.cstr());
    ksys::res::ResourceMgrTask::instance()->addSExtensionPrefix(builder);
    return res->isExistFile(builder);
}

bool Manager::changeMoviePath(sead::BufferedSafeString& path) const {
    if (!hasAoc3())
        return false;

    const sead::SafeString prefix = "Movie/";
    const auto prefix_len = prefix.calcLength();
    if (!path.startsWith(prefix))
        return false;

    const auto rel_path = path.getPart(prefix_len);
    if (!rel_path.startsWith("Demo6"))
        return false;

    path.prepend("aoc://");
    return true;
}

bool Manager::parseVersion() {
    if (!mVersionFile->readVersion())
        return false;

    if (mVersionFile->string.isEmpty()) {
        mVersion = 0;
        return true;
    }

    {
        const int dot_index = mVersionFile->string.findIndex(".");
        const int minor_index = dot_index + 1;
        if (dot_index <= 0 || minor_index >= mVersionFile->string.calcLength()) {
            mVersionFile->string.clear();
            mVersion = 0;
            return true;
        }

        u32 major, minor;
        const auto parse = [&] {
            sead::FixedSafeString<16> major_str;
            major_str.copy(mVersionFile->string, dot_index);

            constexpr auto base = sead::StringUtil::CardinalNumber::Base10;
            if (!sead::StringUtil::tryParseU32(&major, major_str, base))
                return false;

            const auto minor_str = mVersionFile->string.getPart(minor_index);
            if (!sead::StringUtil::tryParseU32(&minor, minor_str, base))
                return false;

            return true;
        };

        if (!parse()) {
            mVersionFile->string.clear();
            mVersion = 0;
            return true;
        }

        mVersion = (major << 8) + minor;
    }

    checkVersion();
    return true;
}

// NON_MATCHING: stack and duplicated branch -- volatile variables are painful
void Manager::checkVersion() {
    if (mVersion == 0)
        return;

    const auto fail = [this](VersionError error) {
        mVersionFlags.setBit(error);
        mVersion = 0;
    };

    if (mVersion < 0x300) {
        fail(VersionError::TooOld);
    } else if (mVersion >= 0x400) {
        fail(VersionError::TooNew);
    }

    mVersionFlags.isOnBit(VersionError(VersionError::TooOld));
    mVersionFlags.isOnBit(VersionError(VersionError::TooNew));
}

bool Manager::VersionFile::readVersion() {
    if (!file_handle.requestedLoad())
        return true;

    if (file_handle.isSuccess()) {
        auto* res = sead::DynamicCast<sead::DirectResource>(file_handle.getResource());
        string.copy(reinterpret_cast<const char*>(res->getRawData()), res->getRawSize());
    } else {
        if (!file_handle.checkLoadStatus())
            return false;
        string.clear();
    }

    file_handle.requestUnload();
    return true;
}

void Manager::initGameData() {
    reinitFlags();
    ksys::gdt::Manager::instance()->addReinitCallback(mGdtReinitSlot);
}

static const sead::SafeString& getDungeonFlag(int number) {
    for (auto it = sDungeonInfo.begin(); it != sDungeonInfo.end(); ++it) {
        if (it->number == number)
            return it->flag;
    }
    return sead::SafeString::cEmptyString;
}

void Manager::reinitFlags() {
    mFlagAocVerAtLastPlay = ksys::gdt::Manager::instance()->getS32Handle("AoCVerAtLastPlay");
    mFlagLatestAocVerPlayed = ksys::gdt::Manager::instance()->getS32Handle("LatestAoCVerPlayed");
    mFlagHasAocVer1 =
        ksys::gdt::Manager::instance()->getBoolHandle(GameDataFlag::text(GameDataFlag::HasAoCVer1));
    mFlagHasAocVer2 =
        ksys::gdt::Manager::instance()->getBoolHandle(GameDataFlag::text(GameDataFlag::HasAoCVer2));
    mFlagHasAocVer3 =
        ksys::gdt::Manager::instance()->getBoolHandle(GameDataFlag::text(GameDataFlag::HasAoCVer3));

    for (int i = 0; i < mDLCPositions.size(); ++i) {
        ksys::gdt::FlagHandle handle = ksys::gdt::InvalidHandle;

        if (i < NumDungeons) {
            if (mDLCPositions[i].flag_handle == ksys::gdt::InvalidHandle)
                continue;

            handle = ksys::gdt::Manager::instance()->getBoolHandle(getDungeonFlag(i + 120));
        }

        mDLCPositions[i].flag_handle = handle;
    }
}

void Manager::setGameDataFlags() const {
    ksys::gdt::Manager::instance()->setS32(mVersion, mFlagAocVerAtLastPlay);

    s32 latest_ver;
    if (ksys::gdt::Manager::instance()->getS32(mFlagLatestAocVerPlayed, &latest_ver)) {
        if (u32(latest_ver) < mVersion)
            ksys::gdt::Manager::instance()->setS32(mVersion, mFlagLatestAocVerPlayed);
    }

    const auto ver = mVersion;
    ksys::gdt::Manager::instance()->setBool(ver >= 0x100, mFlagHasAocVer1);
    ksys::gdt::Manager::instance()->setBool(ver >= 0x200, mFlagHasAocVer2);
    ksys::gdt::Manager::instance()->setBool(ver >= 0x300, mFlagHasAocVer3);
}

void Manager::onGdtReinit(ksys::gdt::Manager::ReinitEvent* event) {
    reinitFlags();
}

}  // namespace uking::aoc

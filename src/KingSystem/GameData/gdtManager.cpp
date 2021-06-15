#include "KingSystem/GameData/gdtManager.h"
#include <algorithm>
#include <cstring>
#include <devenv/seadEnvUtil.h>
#include <framework/seadFramework.h>
#include <mc/seadCoreInfo.h>
#include <prim/seadStringUtil.h>
#include <thread/seadThreadUtil.h>
#include <time/seadTickTime.h>
#include <type_traits>
#include "Game/DLC/aocManager.h"
#include "KingSystem/GameData/gdtSaveMgr.h"
#include "KingSystem/GameData/gdtTriggerParam.h"
#include "KingSystem/Map/mapMubinIter.h"
#include "KingSystem/Resource/resEntryFactory.h"
#include "KingSystem/Resource/resLoadRequest.h"
#include "KingSystem/Resource/resResourceGameData.h"
#include "KingSystem/Resource/resSystem.h"
#include "KingSystem/System/OverlayArenaSystem.h"
#include "KingSystem/Utils/Byaml/Byaml.h"
#include "KingSystem/Utils/Byaml/ByamlArrayIter.h"
#include "KingSystem/Utils/Debug.h"
#include "KingSystem/Utils/HeapUtil.h"
#include "KingSystem/Utils/InitTimeInfo.h"
#include "KingSystem/Utils/SafeDelete.h"

namespace ksys::gdt {

SEAD_SINGLETON_DISPOSER_IMPL(Manager)

static util::InitTimeInfoEx sInitTimeInfo;

Manager::Manager() {
    mRetryBuffer = nullptr;
    mGimmickResetBuffer = nullptr;
    mFlagBuffer1 = nullptr;
    mFlagBuffer = nullptr;
}

Manager::~Manager() {
    mShopGameDataInfoHandle.requestUnload();

    if (mGameDataHeap) {
        if (mFlagBuffer1) {
            mFlagBuffer1->destroyHeap();
            mFlagBuffer1 = nullptr;
        }

        if (mFlagBuffer) {
            mFlagBuffer->destroyHeap();
            mFlagBuffer = nullptr;
        }

        if (mRetryBuffer) {
            mRetryBuffer->destroyHeap();
            mRetryBuffer = nullptr;
        }

        if (mGimmickResetBuffer) {
            mGimmickResetBuffer->destroyHeap();
            mGimmickResetBuffer = nullptr;
        }

        if (mSaveAreaHeap) {
            mSaveAreaHeap->destroy();
            mSaveAreaHeap = nullptr;
        }

        mGameDataHeap->destroy();
        mGameDataHeap = nullptr;
    }

    if (mGameDataComHeap) {
        mGameDataComHeap->destroy();
        mGameDataComHeap = nullptr;
    }
}

// NON_MATCHING: address differences for the static bgdata_factory that causes different regalloc
void Manager::init(sead::Heap* heap, sead::Framework* framework) {
    sead::TickTime a;
    sead::TickTime b;

    mGameDataHeap = util::DualHeap::create(0xf00000, "GameDataHeap", heap, nullptr, sizeof(void*),
                                           sead::Heap::cHeapDirection_Forward, true);
    mIncreaseLogger = new (mGameDataHeap) IncreaseLogger;
    SaveMgr::createInstance(mGameDataHeap);

    SaveMgr::InitArg arg;
    arg.heap = mGameDataHeap;
    arg._8 = 0x300000;
    arg.buf_size = 0x100000;
    arg.buf_alignment = 0x200;
    arg.size2 = 0x10000;
    arg.thread_priority = sead::ThreadUtil::ConvertPrioritySeadToPlatform(18);
    arg.thread_affinity = sead::CoreIdMask(sead::CoreId::cSub1);
    arg._1c = 0x7000;
    arg.is_demo = sead::EnvUtil::getRomType() == "Show_2017_1st";
    if (sead::EnvUtil::getRomType() == "RID_Demo") {
        arg.is_demo = true;
        arg.save_rid_demo_dir = "Save/RID_Demo/";
    }

    arg._60 = nullptr;
    if (util::getDebugHeap2())
        arg._68 = 0x80000;

    SaveMgr::instance()->init(arg);

    static res::EntryFactory<res::GameData> bgdata_factory{5.0, 0xc0000};
    res::registerEntryFactory(&bgdata_factory, "bgdata");

    mSaveAreaHeap =
        util::DualHeap::create(0x500000, "SaveAreaHeap", mGameDataHeap, nullptr, sizeof(void*),
                               sead::Heap::cHeapDirection_Reverse, false);

    SaveMgr::instance()->loadGameSaveData();

    KingEditor::instance()->registerComponent(this);

    sead::FixedSafeString<1024> gamedata_sarc_path;
    gamedata_sarc_path.format("%s/%s.%s", "GameData", "gamedata", "sarc");
    loadGameData(gamedata_sarc_path);

    sead::FixedSafeString<1024> shop_gamedata_info_path;
    shop_gamedata_info_path.format("%s/%s.byml", "GameData", "ShopGameDataInfo");
    loadShopGameDataInfo(shop_gamedata_info_path);

    mParam.setBuffers(&mFlagBuffer1, &mFlagBuffer);
    mParamBypassPerm.setBuffers(&mFlagBuffer1, &mFlagBuffer);

    mMethodTreeNode.method_tree_mgr = framework->getMethodTreeMgr();
    mMethodTreeNode.node.setPauseFlag(sead::MethodTreeNode::cPause_None);

    mBitFlags.reset(BitFlag::_1);
    unloadResources();
    mBitFlags.set(BitFlag::_1000);
    mNumFlagsToReset = 0;
}

void Manager::loadShopGameDataInfo(const sead::SafeString& path) {
    res::LoadRequest req;
    req.mRequester = "gdtManager";
    req._26 = false;
    if (!sead::DynamicCast<res::Resource>(mShopGameDataInfoHandle.load(path, &req)))
        return;

    auto* res = sead::DynamicCast<sead::DirectResource>(mShopGameDataInfoHandle.getResource());
    if (!res)
        return;

    al::ByamlIter root{res->getRawData()};
    al::ByamlIter iter;
    al::ByamlIter hashes;

    if (root.tryGetIterByKey(&iter, "ShopAreaInfo")) {
        iter.tryGetIterByKey(&mShopAreaInfoValues, "Values");
        if (iter.tryGetIterByKey(&hashes, "Hashes")) {
            mShopAreaInfoHashes = al::ByamlArrayIter(hashes.getRootNode()).getDataTable();
        }
    }
    util::PrintDebugFmt("ShopAreaInfo: %d %d", mShopAreaInfoValues.getSize(), hashes.getSize());

    if (root.tryGetIterByKey(&iter, "SoldOutInfo")) {
        iter.tryGetIterByKey(&mShopSoldOutInfoValues, "Values");
        if (iter.tryGetIterByKey(&hashes, "Hashes")) {
            mShopSoldOutInfoHashes = al::ByamlArrayIter(hashes.getRootNode()).getDataTable();
        }
    }
    util::PrintDebugFmt("SoldOutInfo: %d %d", mShopSoldOutInfoValues.getSize(), hashes.getSize());
}

void Manager::unloadResources() {
    for (s32 i = 0; i < mBgdataHandles.size(); ++i)
        mBgdataHandles[i].requestUnload();

    mGameDataArcHandle.requestUnload();
}

void Manager::addReinitCallback(sead::DelegateEvent<ReinitEvent*>::Slot&) {
    // Stubbed in release builds.
}

void Manager::removeReinitCallback(sead::DelegateEvent<Manager::ReinitEvent*>::Slot& slot) {
    // Stubbed in release builds.
}

void Manager::setCurrentRupeeFlagName(const sead::SafeString& name) {
    getParam().get1().getBuffer()->setCurrentRupeeFlagName(name);
}

void Manager::requestResetAllFlagsToInitial() {
    mBitFlags.set(BitFlag::RequestResetAllFlagsToInitial);
}

namespace {

template <int N>
bool loadAllFlags(Manager* mgr, sead::SafeArray<bool, N>* flags,
                  const sead::SafeString (&names)[N]) {
#ifdef MATCHING_HACK_NX_CLANG
#pragma clang loop unroll(full)
#endif
    for (int i = 0; i < N; ++i) {
        if (!mgr->getParam().get1().getBool(&(*flags)[i], names[i]))
            return false;
    }
    return true;
}

void fixDarkWoodsFlags(Manager* mgr) {
    enum {
        DarkWoods_Giant_Clear,
        DarkWoods_Finish,
    };
    sead::SafeString names[] = {
        "DarkWoods_Giant_Clear",
        "DarkWoods_Finish",
    };
    sead::SafeArray<bool, std::size(names)> flags;
    if (!loadAllFlags(mgr, &flags, names))
        return;
    if (flags[DarkWoods_Giant_Clear] && !flags[DarkWoods_Finish])
        mgr->getParamBypassPerm().get1().setBool(false, names[DarkWoods_Giant_Clear], true);
}

void fixGiantQuestFlags(Manager* mgr) {
    enum {
        giant_ball1,
        giant_ball2,
        giant_ball3,
        giant_dungeon,
        MainField_DgnObj_RemainsLithogragh_A_02_789666109,
        MainField_DgnObj_RemainsLithogragh_A_02_2456751716,
        MainField_DgnObj_RemainsLithogragh_A_02_1822262999,
    };
    sead::SafeString names[] = {
        "giant_ball1",
        "giant_ball2",
        "giant_ball3",
        "giant_dungeon",
        "MainField_DgnObj_RemainsLithogragh_A_02_789666109",
        "MainField_DgnObj_RemainsLithogragh_A_02_2456751716",
        "MainField_DgnObj_RemainsLithogragh_A_02_1822262999",
    };
    sead::SafeArray<bool, std::size(names)> flags;
    if (!loadAllFlags(mgr, &flags, names))
        return;

    if (flags[giant_ball1] && !flags[MainField_DgnObj_RemainsLithogragh_A_02_789666109])
        mgr->setBool(true, names[MainField_DgnObj_RemainsLithogragh_A_02_789666109]);
    if (flags[giant_ball2] && !flags[MainField_DgnObj_RemainsLithogragh_A_02_2456751716])
        mgr->setBool(true, names[MainField_DgnObj_RemainsLithogragh_A_02_2456751716]);
    if (flags[giant_ball3] && !flags[MainField_DgnObj_RemainsLithogragh_A_02_1822262999])
        mgr->setBool(true, names[MainField_DgnObj_RemainsLithogragh_A_02_1822262999]);

    if (flags[giant_ball1] && flags[giant_ball2] && flags[giant_ball3] && !flags[giant_dungeon])
        mgr->getParamBypassPerm().get1().setBool(true, names[giant_dungeon], true);
}

void fixBowOfLightFlag(Manager* mgr) {
    enum { MainField_Weapon_Bow_071_2178255681 };
    sead::SafeString names[] = {"MainField_Weapon_Bow_071_2178255681"};
    sead::SafeArray<bool, std::size(names)> flags;
    if (loadAllFlags(mgr, &flags, names) && flags[MainField_Weapon_Bow_071_2178255681])
        mgr->setBool(false, names[MainField_Weapon_Bow_071_2178255681]);
}

void fixBalladOfHeroesFlags(Manager* mgr) {
    enum {
        BalladOfHeroes_Step02,
        BalladOfHeroes_Step03,
        Defeat_OneHitDungeon001,
        Defeat_OneHitDungeon002,
        Defeat_OneHitDungeon003,
        Defeat_OneHitDungeon004,
        Lock_OneHitDungeon001,
        Lock_OneHitDungeon002,
        Lock_OneHitDungeon003,
        Lock_OneHitDungeon004,
        BalladOfHeroes_Step02_Dungeon01,
        BalladOfHeroes_Step02_Dungeon02,
        BalladOfHeroes_Step02_Dungeon03,
        BalladOfHeroes_Step2_Dungeon4,
    };
    sead::SafeString names[] = {
        "BalladOfHeroes_Step02",
        "BalladOfHeroes_Step03",
        //
        "Defeat_OneHitDungeon001",
        "Defeat_OneHitDungeon002",
        "Defeat_OneHitDungeon003",
        "Defeat_OneHitDungeon004",
        //
        "Lock_OneHitDungeon001",
        "Lock_OneHitDungeon002",
        "Lock_OneHitDungeon003",
        "Lock_OneHitDungeon004",
        //
        "BalladOfHeroes_Step02_Dungeon01",
        "BalladOfHeroes_Step02_Dungeon02",
        "BalladOfHeroes_Step02_Dungeon03",
        "BalladOfHeroes_Step2_Dungeon4",
    };
    sead::SafeArray<bool, std::size(names)> flags;
    if (!loadAllFlags(mgr, &flags, names))
        return;

    if (!flags[BalladOfHeroes_Step02] || flags[BalladOfHeroes_Step03])
        return;

    s8 count = 0;
    bool not_locked = false;

    if (flags[Defeat_OneHitDungeon001]) {
        ++count;
        if (!flags[Lock_OneHitDungeon001])
            not_locked = true;
    }
    if (flags[Defeat_OneHitDungeon002]) {
        ++count;
        if (!flags[Lock_OneHitDungeon002])
            not_locked = true;
    }
    if (flags[Defeat_OneHitDungeon003]) {
        ++count;
        if (!flags[Lock_OneHitDungeon003])
            not_locked = true;
    }
    if (flags[Defeat_OneHitDungeon004]) {
        ++count;
        if (!flags[Lock_OneHitDungeon004])
            not_locked = true;
    }

    if (not_locked) {
        if (count >= 1 && !flags[BalladOfHeroes_Step02_Dungeon01])
            mgr->setBool(true, names[BalladOfHeroes_Step02_Dungeon01]);
        if (count >= 2 && !flags[BalladOfHeroes_Step02_Dungeon02])
            mgr->setBool(true, names[BalladOfHeroes_Step02_Dungeon02]);
        if (count >= 3 && !flags[BalladOfHeroes_Step02_Dungeon03])
            mgr->setBool(true, names[BalladOfHeroes_Step02_Dungeon03]);
        if (count >= 4 && !flags[BalladOfHeroes_Step2_Dungeon4])
            mgr->setBool(true, names[BalladOfHeroes_Step2_Dungeon4]);
    }
}

void fixAllShrinesFlags(Manager* mgr) {
    enum {
        IsGet_Armor_005_Head,
        IsGet_Armor_005_Upper,
        IsGet_Armor_005_Lower,
        CompleteDungeon_Finish,
    };
    sead::SafeString names[] = {
        "IsGet_Armor_005_Head",
        "IsGet_Armor_005_Upper",
        "IsGet_Armor_005_Lower",
        "CompleteDungeon_Finish",
    };
    sead::SafeArray<bool, std::size(names)> flags;
    if (!loadAllFlags(mgr, &flags, names))
        return;

    if (flags[IsGet_Armor_005_Head] && flags[IsGet_Armor_005_Upper] &&
        flags[IsGet_Armor_005_Lower] && !flags[CompleteDungeon_Finish]) {
        mgr->setBool(true, names[CompleteDungeon_Finish]);
    }
}

}  // namespace

void Manager::fixQuestFlags() {
    fixDarkWoodsFlags(this);
    fixGiantQuestFlags(this);
    fixBowOfLightFlag(this);
    fixBalladOfHeroesFlags(this);
    fixAllShrinesFlags(this);

    {
        enum {
            NightStoneBreak,
            NightStoneDungeonAppear,
        };
        sead::SafeString names[] = {
            "NightStoneBreak",
            "NightStoneDungeonAppear",
        };
        sead::SafeArray<bool, std::size(names)> flags;
        if (loadAllFlags(this, &flags, names)) {
            if (flags[NightStoneBreak] && !flags[NightStoneDungeonAppear])
                getParamBypassPerm().get().setBool(false, names[NightStoneBreak], true);
        }
    }

    {
        enum {
            Animal_Forest_Finish,
            HateeluMini_Treasure_Finish,
            Thunder_Sword_Finish,
            Relief_Landing_Finish,
            Shadow_Sign_Finish,
            MouthofDragon_Finish,
            TwoWheels_Finish,
            BloodyMoonRelief_Finish,
            Rito_BrosRock_Finish,
        };
        sead::SafeString names[] = {
            "Animal_Forest_Finish",
            "HateeluMini_Treasure_Finish",
            "Thunder_Sword_Finish",
            "Relief_Landing_Finish",
            "Shadow_Sign_Finish",
            "MouthofDragon_Finish",
            "TwoWheels_Finish",
            "BloodyMoonRelief_Finish",
            // Not a shrine quest
            "Rito_BrosRock_Finish",
        };
        sead::SafeArray<bool, std::size(names)> flags;
        if (loadAllFlags(this, &flags, names)) {
            if (std::all_of(flags.begin(), flags.end(), [](bool b) { return b; }))
                getParamBypassPerm().get().setBool(true, "Npc_Musician_Come", true);
        }
    }
}

void Manager::fixQuestFlagsDlc2() {
    if (uking::aoc::Manager::instance()->hasAoc3())
        return;

    enum {
        Ichigeki_Sword_Appear,
        BalladOfHeroes_Retire_Dungeon04,
        BalladOfHeroes_Step02,
        BalladOfHeroes_Step02_Dungeon01,
        BalladOfHeroes_Step02_Dungeon02,
        BalladOfHeroes_Step02_Dungeon03,
        BalladOfHeroes_Step2_Dungeon4,
        BalladOfHeroes_Step03,
    };
    sead::SafeString names[] = {
        "Ichigeki_Sword_Appear",
        "BalladOfHeroes_Retire_Dungeon04",
        // OhO plateau phase
        "BalladOfHeroes_Step02",
        "BalladOfHeroes_Step02_Dungeon01",
        "BalladOfHeroes_Step02_Dungeon02",
        "BalladOfHeroes_Step02_Dungeon03",
        "BalladOfHeroes_Step2_Dungeon4",
        "BalladOfHeroes_Step03",
    };
    sead::SafeArray<bool, std::size(names)> flags;
    if (!loadAllFlags(this, &flags, names))
        return;

    const bool value_BalladOfHeroes_Step2_Dungeon4 = flags[BalladOfHeroes_Step2_Dungeon4];

    if (!flags[BalladOfHeroes_Step02] || flags[BalladOfHeroes_Step03])
        return;

    setBool(false, names[BalladOfHeroes_Step2_Dungeon4]);
    setBool(false, names[BalladOfHeroes_Step02_Dungeon03]);
    setBool(false, names[BalladOfHeroes_Step02_Dungeon02]);
    setBool(false, names[BalladOfHeroes_Step02_Dungeon01]);
    setBool(false, names[BalladOfHeroes_Step02]);
    if (!value_BalladOfHeroes_Step2_Dungeon4)
        setBool(false, names[BalladOfHeroes_Retire_Dungeon04]);
    setBool(true, names[Ichigeki_Sword_Appear]);

    const char* temp_horse;
    if (getParam().get().getStr64(&temp_horse, "Horse_ActorName", 5) &&
        sead::SafeString(temp_horse) == "GameRomHorseBone_AllDay") {
        setStr64("", "Horse_ActorName", 5);
    }
}

#define GDT_SET_IMPL_(NAME, TRAITS)                                                                \
    /* Setters (by name) */                                                                        \
    bool Manager::NAME(TRAITS::ArgType value, const sead::SafeString& name) {                      \
        return NAME(value, name, false, false);                                                    \
    }                                                                                              \
    bool Manager::NAME##_(TRAITS::ArgType value, const sead::SafeString& name) {                   \
        return NAME(value, name, false, false);                                                    \
    }                                                                                              \
    bool Manager::NAME##NoCheck(TRAITS::ArgType value, const sead::SafeString& name) {             \
        return NAME(value, name, true, false);                                                     \
    }                                                                                              \
    bool Manager::NAME##NoCheck_(TRAITS::ArgType value, const sead::SafeString& name) {            \
        return NAME(value, name, true, false);                                                     \
    }                                                                                              \
    bool Manager::NAME##NoCheckForce(TRAITS::NoCheckForceArgType value,                            \
                                     const sead::SafeString& name) {                               \
        return NAME(value, name, true, true);                                                      \
    }                                                                                              \
    /* Setters for arrays (by name) */                                                             \
    bool Manager::NAME(TRAITS::ArgType value, const sead::SafeString& name, s32 sub_idx) {         \
        return NAME(value, name, false, false, sub_idx);                                           \
    }                                                                                              \
    bool Manager::NAME##_(TRAITS::ArgType value, const sead::SafeString& name, s32 sub_idx) {      \
        return NAME(value, name, false, false, sub_idx);                                           \
    }                                                                                              \
    bool Manager::NAME##NoCheck(TRAITS::ArgType value, const sead::SafeString& name,               \
                                s32 sub_idx) {                                                     \
        return NAME(value, name, true, false, sub_idx);                                            \
    }                                                                                              \
    bool Manager::NAME##NoCheckForce(TRAITS::NoCheckForceArgType value,                            \
                                     const sead::SafeString& name, s32 sub_idx) {                  \
        return NAME(value, name, true, true, sub_idx);                                             \
    }

GDT_SET_IMPL_(setBool, detail::SetterTraits<bool>)
GDT_SET_IMPL_(setS32, detail::SetterTraits<s32>)
GDT_SET_IMPL_(setF32, detail::SetterTraits<f32>)
GDT_SET_IMPL_(setStr, detail::SetterTraits<const char*>)
GDT_SET_IMPL_(setStr64, detail::SetterTraits<const char*>)
GDT_SET_IMPL_(setStr256, detail::SetterTraits<const char*>)
GDT_SET_IMPL_(setVec2f, detail::SetterTraits<sead::Vector2f>)
GDT_SET_IMPL_(setVec3f, detail::SetterTraits<sead::Vector3f>)
GDT_SET_IMPL_(setVec4f, detail::SetterTraits<sead::Vector4f>)

#undef GDT_SET_IMPL_

#define GDT_RESET_IMPL_(NAME)                                                                      \
    bool Manager::NAME(const sead::SafeString& name) {                                             \
        if (mBitFlags.isOn(BitFlag::_40000))                                                       \
            return false;                                                                          \
        return getParam().get1().NAME(name);                                                       \
    }                                                                                              \
    bool Manager::NAME##_(const sead::SafeString& name) { return NAME(name); }                     \
    bool Manager::NAME(const sead::SafeString& name, int sub_idx) {                                \
        if (mBitFlags.isOn(BitFlag::_40000))                                                       \
            return false;                                                                          \
        return getParam().get1().NAME(name, sub_idx);                                              \
    }

GDT_RESET_IMPL_(resetBool)
GDT_RESET_IMPL_(resetS32)
GDT_RESET_IMPL_(resetF32)
GDT_RESET_IMPL_(resetStr)
GDT_RESET_IMPL_(resetStr64)
GDT_RESET_IMPL_(resetStr256)
GDT_RESET_IMPL_(resetVec2f)
GDT_RESET_IMPL_(resetVec3f)
GDT_RESET_IMPL_(resetVec4f)

#undef GDT_RESET_IMPL_

void Manager::incrementS32NoCheck(s32 value, const sead::SafeString& name) {
    if (mBitFlags.isOn(BitFlag::_40000))
        return;

    if (mBitFlags.isOn(BitFlag::_10000)) {
        s32 current = 0;
        if (getParamBypassPerm().get().getS32(&current, name))
            setS32NoCheck(current + value, name);
    } else if (mIncreaseLogger) {
        mIncreaseLogger->addRecord(value, name, -1, true);
    }
}

void Manager::incrementS32(s32 value, const sead::SafeString& name) {
    if (mBitFlags.isOn(BitFlag::_40000))
        return;

    if (mBitFlags.isOn(BitFlag::_10000)) {
        s32 current = 0;
        if (getParam().get().getS32(&current, name))
            setS32(current + value, name);
    } else if (mIncreaseLogger) {
        mIncreaseLogger->addRecord(value, name, -1, false);
    }
}

void Manager::IncreaseLogger::addRecord(s32 value, const sead::SafeString& name, s32 sub_idx,
                                        bool debug) {
    const u32 name_hash = sead::HashCRC32::calcStringHash(name);
    const auto core = sead::CoreInfo::getCurrentCoreId();
    const u32 platform_core_id = sead::CoreInfo::getPlatformCoreId(core);

    Record record;
    record.debug = debug;
    record.name_hash = name_hash;
    record.sub_idx = sub_idx;
    record.value = value;
    ring_buffers[0][platform_core_id].pushBack(record);
}

bool Manager::wasFlagCopied(const sead::SafeString& name) {
    bool value;
    return getParam().get().getBuffer()->getBoolIfCopied(&value, name, false, true) && value != 0;
}

bool Manager::wasFlagNotCopied(const sead::SafeString& name) {
    bool value;
    return getParam().get().getBuffer()->getBoolIfCopied(&value, name, false, true) && !value;
}

void Manager::copyParamToParam1() {
    mFlagBuffer1->copyChangedFlags(*mFlagBuffer, true, false, false);
}

FlagHandle Manager::getRevivalFlagHandle(const sead::SafeString& object_name,
                                         const map::MubinIter& iter) {
    if (mBitFlags.isOn(BitFlag::_40000))
        return InvalidHandle;

    const sead::SafeString& map_name =
        mGetMapNameDelegate ? mGetMapNameDelegate->invoke() : sead::SafeString::cEmptyString;

    u32 hash_id = 0;
    iter.tryGetParamUIntByKey(&hash_id, "HashId");

    sead::FormatFixedSafeString<128> flag_name("%s_%s_%u", map_name.cstr(), object_name.cstr(),
                                               hash_id);
    if (mBitFlags.isOn(BitFlag::_2000))
        return InvalidHandle;
    return getBoolHandle(flag_name);
}

void Manager::allocParam1() {
    auto* parent_heap = OverlayArenaSystem::instance()->getGameDataWorkHeap();
    auto* heap = util::tryCreateDualHeap(0, "param1", parent_heap, nullptr,
                                         sead::Heap::cHeapDirection_Forward, false);
    mFlagBuffer1 = new (heap) TriggerParam;
    mFlagBuffer1->copyAllFlags(*mFlagBuffer, heap, true);
    heap->adjust();
}

bool Manager::getShopInfoIter(u32 hash, al::ByamlIter* out, const al::ByamlIter& iter,
                              const u32* hashes) {
    int a = 0;
    int b = iter.getSize();
    while (a < b) {
        const auto m = (a + b) / 2;
        if (hashes[m] == hash)
            return iter.tryGetIterByIndex(out, m);
        if (hashes[m] < hash)
            a = m + 1;
        else
            b = m;
    }
    return false;
}

void Manager::allocRetryBuffer(sead::Heap* heap) {
    if (mRetryBuffer)
        return;

    auto* buffer_heap = util::tryCreateDualHeap(0x100000, "RetryBuffer", heap, nullptr,
                                                sead::Heap::cHeapDirection_Reverse, false);
    mRetryBuffer = new (buffer_heap) TriggerParam;
    mRetryBuffer->copyPermanentFlags(*mFlagBuffer1, buffer_heap);
    buffer_heap->adjust();
}

void Manager::destroyRetryBuffer() {
    if (mBitFlags.isOn(BitFlag::_80000))
        return;

    if (mRetryBuffer) {
        mRetryBuffer->destroyHeap();
        mRetryBuffer = nullptr;
    }
}

void Manager::syncData(char* data) {
    const sead::SafeString cmd = data;
    if (cmd.compare("SyncStart") == 0) {
        if (util::getDebugHeap()) {
            if (mBitFlags.testAndClear(BitFlag::_100)) {
                mSyncStep = 0;
            }
            mBitFlags.set(BitFlag::_200);
            syncStart();
        }
    } else if (cmd.compare("SyncEnd") == 0) {
        mSyncStep = 0;
        mBitFlags.reset(BitFlag::_100);
        mBitFlags.reset(BitFlag::_200);
    } else {
        syncUpdate(data);
        onChangedByDebug();
    }
}

constexpr size_t ComBufferSize = 0x1a000;

void Manager::syncStart() {
    if (KingEditor::instance()->get88() == 0 || util::getDebugHeap() == nullptr)
        return;

    if (mGameDataComHeap) {
        if (mGameDataComHeap->getFreeSize() < ComBufferSize)
            return;
    } else {
        mGameDataComHeap =
            sead::ExpHeap::tryCreate(ComBufferSize + 0x400, "GameDataCom", util::getDebugHeap(),
                                     sizeof(void*), sead::Heap::cHeapDirection_Forward, false);
        if (!mGameDataComHeap)
            return;
    }

    u8* buffer = new (mGameDataComHeap) u8[ComBufferSize];
    auto* flag_buffer = mFlagBuffer;
    const int step = mSyncStep;
    switch (mSyncStep) {
    case 0:
        doSyncArray<bool>(flag_buffer->mBoolFlags, buffer, "[SyncData][AllData][bool]");
        mSyncStep = step + 1;
        break;
    case 1:
        doSyncArray<s32>(flag_buffer->mS32Flags, buffer, "[SyncData][AllData][s32]");
        mSyncStep = step + 1;
        break;
    case 2:
        doSyncArray<f32>(flag_buffer->mF32Flags, buffer, "[SyncData][AllData][f32]");
        mSyncStep = step + 1;
        break;
    case 3:
        doSyncArrayStr<32>(flag_buffer->mStringFlags, buffer, "[SyncData][AllData][string]");
        mSyncStep = step + 1;
        break;
    case 4:
        doSyncArrayStr<64>(flag_buffer->mString64Flags, buffer, "[SyncData][AllData][string64]");
        mSyncStep = step + 1;
        break;
    case 5:
        doSyncArrayStr<256>(flag_buffer->mString256Flags, buffer, "[SyncData][AllData][string256]");
        mSyncStep = step + 1;
        break;
    case 6:
        doSyncArrayVec<sead::Vector2f>(flag_buffer->mVector2fFlags, buffer,
                                       "[SyncData][AllData][vector2f]", 2);
        mSyncStep = step + 1;
        break;
    case 7:
        doSyncArrayVec<sead::Vector3f>(flag_buffer->mVector3fFlags, buffer,
                                       "[SyncData][AllData][vector3f]", 3);
        mSyncStep = step + 1;
        break;
    case 8:
        doSyncArrayVec<sead::Vector4f>(flag_buffer->mVector4fFlags, buffer,
                                       "[SyncData][AllData][vector4f]", 4);
        mSyncStep = step + 1;
        break;
    case 9:
        doSyncArray<bool>(flag_buffer->mBoolArrayFlags, buffer, "[SyncData][AllData][boolarray]");
        mSyncStep = step + 1;
        break;
    case 10:
        doSyncArray<s32>(flag_buffer->mS32ArrayFlags, buffer, "[SyncData][AllData][s32array]");
        mSyncStep = step + 1;
        break;
    case 11:
        doSyncArray<f32>(flag_buffer->mF32ArrayFlags, buffer, "[SyncData][AllData][f32array]");
        mSyncStep = step + 1;
        break;
    case 12:
        doSyncArrayStr<32>(flag_buffer->mStringArrayFlags, buffer,
                           "[SyncData][AllData][stringarray]");
        mSyncStep = step + 1;
        break;
    case 13:
        doSyncArrayStr<64>(flag_buffer->mString64ArrayFlags, buffer,
                           "[SyncData][AllData][string64array]");
        mSyncStep = step + 1;
        break;
    case 14:
        doSyncArrayStr<256>(flag_buffer->mString256ArrayFlags, buffer,
                            "[SyncData][AllData][string256array]");
        mSyncStep = step + 1;
        break;
    case 15:
        doSyncArrayVec<sead::Vector2f>(flag_buffer->mVector2fArrayFlags, buffer,
                                       "[SyncData][AllData][vector2farray]", 2);
        mSyncStep = step + 1;
        break;
    case 16:
        doSyncArrayVec<sead::Vector3f>(flag_buffer->mVector3fArrayFlags, buffer,
                                       "[SyncData][AllData][vector3farray]", 3);
        mSyncStep = step + 1;
        break;
    case 17:
        doSyncArrayVec<sead::Vector4f>(flag_buffer->mVector4fArrayFlags, buffer,
                                       "[SyncData][AllData][vector4farray]", 4);
        mSyncStep = step + 1;
        break;
    default:
        KingEditor::instance()->log(getName(), "[SendAllData]");
        mBitFlags.reset(BitFlag::SyncFlags);
        mBitFlags.set(BitFlag::_100);
        break;
    }
    util::safeDeleteArray(buffer);
}

// NON_MATCHING: recordFlagChange calls not being merged, or merged in the wrong way
void Manager::syncUpdate(const char* data) {
    const sead::SafeString cmd = data;
    auto it = cmd.tokenBegin("|");
    const auto end = cmd.tokenEnd("|");
    if (it == end)
        return;

    sead::FixedSafeString<256> name;
    it.getAndForward(&name);

    sead::FixedSafeString<256> type;
    it.getAndForward(&type);

    sead::FixedSafeString<256> value;
    it.getAndForward(&value);

    auto* tparam = mFlagBuffer1;
    int idx = -1;
    const u32 pl_core_id = sead::CoreInfo::getPlatformCoreId(sead::CoreInfo::getCurrentCoreId());

    const auto calc_hash = [&] { return sead::HashCRC32::calcStringHash(name); };

    if (type.compare("bool") == 0) {
        auto* flag = tparam->getBoolFlagAndIdx(&idx, calc_hash());
        if (!flag)
            return;

        bool v = false;
        if (value == "true")
            v = true;

        flag->setValue(v);
        recordFlagChange(pl_core_id, tparam, flag->getType(), idx);
        return;
    }

    if (type.compare("s32") == 0) {
        auto* flag = tparam->getS32FlagAndIdx(&idx, calc_hash());
        if (!flag)
            return;

        s32 v = 0;
        sead::StringUtil::tryParseS32(&v, value, sead::StringUtil::CardinalNumber::BaseAuto);
        flag->setValue(v);
        recordFlagChange(pl_core_id, tparam, flag->getType(), idx);
        return;
    }

    if (type.compare("f32") == 0) {
        auto* flag = tparam->getF32FlagAndIdx(&idx, calc_hash());
        if (!flag)
            return;

        f32 v = 0;
        sead::StringUtil::tryParseF32(&v, value);
        flag->setValue(v);
        recordFlagChange(pl_core_id, tparam, flag->getType(), idx);
        return;
    }

    if (type.compare("string") == 0) {
        auto* flag = tparam->getStrFlagAndIdx(&idx, calc_hash());
        if (!flag)
            return;

        flag->setValue(value);
        recordFlagChange(pl_core_id, tparam, flag->getType(), idx);
        return;
    }

    if (type.compare("string64") == 0) {
        auto* flag = tparam->getStr64FlagAndIdx(&idx, calc_hash());
        if (!flag)
            return;

        flag->setValue(value);
        recordFlagChange(pl_core_id, tparam, flag->getType(), idx);
        return;
    }

    if (type.compare("string256") == 0) {
        auto* flag = tparam->getStr256FlagAndIdx(&idx, calc_hash());
        if (!flag)
            return;

        flag->setValue(value);
        recordFlagChange(pl_core_id, tparam, flag->getType(), idx);
        return;
    }

    if (type.compare("vector2f") == 0) {
        auto* flag = tparam->getVec2fFlagAndIdx(&idx, calc_hash());
        if (!flag)
            return;

        sead::Vector2f v;
        parseFloats(value, v.e.data(), v.e.size());
        flag->setValue(v);
        recordFlagChange(pl_core_id, tparam, flag->getType(), idx);
        return;
    }

    if (type.compare("vector3f") == 0) {
        auto* flag = tparam->getVec3fFlagAndIdx(&idx, calc_hash());
        if (!flag)
            return;

        sead::Vector3f v;
        parseFloats(value, v.e.data(), v.e.size());
        flag->setValue(v);
        recordFlagChange(pl_core_id, tparam, flag->getType(), idx);
        return;
    }

    if (type.compare("vector4f") == 0) {
        auto* flag = tparam->getVec4fFlagAndIdx(&idx, calc_hash());
        if (!flag)
            return;

        sead::Vector4f v;
        parseFloats(value, v.e.data(), v.e.size());
        flag->setValue(v);
        recordFlagChange(pl_core_id, tparam, flag->getType(), idx);
        return;
    }

    sead::FixedSafeString<64> sub_idx_str{"-1"};
    if (it != end)
        it.getAndForward(&sub_idx_str);
    const int sub_idx =
        sead::StringUtil::parseS32(sub_idx_str, sead::StringUtil::CardinalNumber::BaseAuto);

    if (type.compare("boolarray") == 0) {
        auto* flag = tparam->getBoolFlagAndIdx(&idx, calc_hash(), sub_idx);
        if (!flag)
            return;

        bool v = false;
        if (value == "true")
            v = true;

        flag->setValue(v);
        recordFlagChange(pl_core_id, tparam, flag->getType(), idx, sub_idx);
        return;
    }

    if (type.compare("s32array") == 0) {
        auto* flag = tparam->getS32FlagAndIdx(&idx, calc_hash(), sub_idx);
        if (!flag)
            return;

        s32 v = 0;
        sead::StringUtil::tryParseS32(&v, value, sead::StringUtil::CardinalNumber::BaseAuto);
        flag->setValue(v);
        recordFlagChange(pl_core_id, tparam, flag->getType(), idx, sub_idx);
        return;
    }

    if (type.compare("f32array") == 0) {
        auto* flag = tparam->getF32FlagAndIdx(&idx, calc_hash(), sub_idx);
        if (!flag)
            return;

        f32 v = 0;
        sead::StringUtil::tryParseF32(&v, value);
        flag->setValue(v);
        recordFlagChange(pl_core_id, tparam, flag->getType(), idx, sub_idx);
        return;
    }

    if (type.compare("stringarray") == 0) {
        auto* flag = tparam->getStrFlagAndIdx(&idx, calc_hash(), sub_idx);
        if (!flag)
            return;

        flag->setValue(value);
        recordFlagChange(pl_core_id, tparam, flag->getType(), idx, sub_idx);
        return;
    }

    if (type.compare("string64array") == 0) {
        auto* flag = tparam->getStr64FlagAndIdx(&idx, calc_hash(), sub_idx);
        if (!flag)
            return;

        flag->setValue(value);
        recordFlagChange(pl_core_id, tparam, flag->getType(), idx, sub_idx);
        return;
    }

    if (type.compare("string256array") == 0) {
        auto* flag = tparam->getStr256FlagAndIdx(&idx, calc_hash(), sub_idx);
        if (!flag)
            return;

        flag->setValue(value);
        recordFlagChange(pl_core_id, tparam, flag->getType(), idx, sub_idx);
        return;
    }

    if (type.compare("vector2farray") == 0) {
        auto* flag = tparam->getVec2fFlagAndIdx(&idx, calc_hash(), sub_idx);
        if (!flag)
            return;

        sead::Vector2f v;
        parseFloats(value, v.e.data(), v.e.size());
        flag->setValue(v);
        recordFlagChange(pl_core_id, tparam, flag->getType(), idx, sub_idx);
        return;
    }

    if (type.compare("vector3farray") == 0) {
        auto* flag = tparam->getVec3fFlagAndIdx(&idx, calc_hash(), sub_idx);
        if (!flag)
            return;

        sead::Vector3f v;
        parseFloats(value, v.e.data(), v.e.size());
        flag->setValue(v);
        recordFlagChange(pl_core_id, tparam, flag->getType(), idx, sub_idx);
        return;
    }

    if (type.compare("vector4farray") == 0) {
        auto* flag = tparam->getVec4fFlagAndIdx(&idx, calc_hash(), sub_idx);
        if (!flag)
            return;

        sead::Vector4f v;
        parseFloats(value, v.e.data(), v.e.size());
        flag->setValue(v);
        recordFlagChange(pl_core_id, tparam, flag->getType(), idx, sub_idx);
        return;
    }
}

void Manager::recordFlagChange(u32 platform_core_id, TriggerParam* tparam, u8 type, const s32& idx,
                               const s32& sub_idx) {
    auto& buffer = tparam->mFlagChangeRecords[platform_core_id].ref();
    buffer[tparam->mFlagChangeRecordIndices[platform_core_id]].type.mValue = type;
    buffer[tparam->mFlagChangeRecordIndices[platform_core_id]].index = idx;
    buffer[tparam->mFlagChangeRecordIndices[platform_core_id]].sub_index = sub_idx;
    ++tparam->mFlagChangeRecordIndices[platform_core_id];
}

void Manager::startSyncOnLoadEnd() {
    if (!mBitFlags.isOn(BitFlag::_100) || mBitFlags.isOn(BitFlag::_200))
        return;

    KingEditor::instance()->log(getName(), "[LoadEnd]");
    mBitFlags.reset(BitFlag::SyncFlags);
    mBitFlags.set(BitFlag::_200);
    mSyncStep = 0;
    syncStart();
}

void Manager::parseFloats(const sead::SafeString& str, f32* values, u32 n) {
    auto it = str.tokenBegin(" ");
    const auto end = str.tokenEnd(" ");
    u32 i = 0;
    while (end != it) {
        sead::FixedSafeString<256> part;
        it.getAndForward(&part);

        f32 value;
        if (!sead::StringUtil::tryParseF32(&value, part))
            value = 0.0;

        values[i++] = value;
        if (i == n)
            break;
    }
}

namespace {
template <typename T>
void writeToBuffer(u8* buffer, u32* written, const T& value) {
    static_assert(std::is_trivially_copyable<T>());
    std::memcpy(buffer + *written, &value, sizeof(value));
    *written += u32(sizeof(value));
}
}  // namespace

template <typename T>
void Manager::doSyncArray(const sead::PtrArray<FlagBase>& array, u8* buffer,
                          const char* description) {
    KingEditor::instance()->log(getName(), "[ArrayStart]");

    u32 offset = 0;
    const auto flush = [&] {
        KingEditor::instance()->log(getName(), description, buffer, offset);
        offset = 0;
    };
    for (FlagBase& flag : array) {
        u32 written = 0;
        writeToBuffer(buffer + offset, &written, flag.getHash());
        if constexpr (std::is_same<bool, T>()) {
            writeToBuffer(buffer + offset, &written, static_cast<Flag<T>&>(flag).getValue());
        } else {
            writeToBuffer(buffer + offset, &written, static_cast<Flag<T>&>(flag).getValueRef());
        }
        offset += written;
        if (offset >= ComBufferSize - written)
            flush();
    }

    if (offset != 0)
        flush();

    KingEditor::instance()->log(getName(), "[ArrayEnd]");
}

template <int N>
void Manager::doSyncArrayStr(const sead::PtrArray<FlagBase>& array, u8* buffer,
                             const char* description, u32 n) {
    KingEditor::instance()->log(getName(), "[ArrayStart]");

    u32 offset = 0;
    const auto flush = [&] {
        KingEditor::instance()->log(getName(), description, buffer, offset);
        offset = 0;
    };
    for (FlagBase& flag : array) {
        const auto& flag_ = static_cast<const Flag<sead::FixedSafeString<N>>&>(flag);
        u8* entry = buffer + offset;

        const u32 hash = flag.getHash();
        std::memcpy(entry, &hash, sizeof(hash));

        const auto len = flag_.getValueRef().calcLength();
        sead::MemUtil::copy(entry + sizeof(hash), flag_.getValueRef().cstr(), len);
        sead::MemUtil::fillZero(entry + u32(sizeof(hash) + len), n - len);

        offset += u32(sizeof(hash) + n);
        if (offset >= ComBufferSize - sizeof(hash) - n)
            flush();
    }

    if (offset != 0)
        flush();

    KingEditor::instance()->log(getName(), "[ArrayEnd]");
}

template <typename T>
void Manager::doSyncArrayVec(const sead::PtrArray<FlagBase>& array, u8* buffer,
                             const char* description, u32 n) {
    KingEditor::instance()->log(getName(), "[ArrayStart]");

    u32 offset = 0;
    const auto flush = [&] {
        KingEditor::instance()->log(getName(), description, buffer, offset);
        offset = 0;
    };
    for (FlagBase& flag : array) {
        const auto& flag_ = static_cast<const Flag<T>&>(flag);
        u32 written = 0;
        writeToBuffer(buffer + offset, &written, flag.getHash());

        for (u32 i = 0; i != n; ++i)
            writeToBuffer(buffer + offset, &written, flag_.getValueRef().e[i]);

        offset += written;
        /// @bug "n" should be "sizeof(f32) * n" instead.
        if (offset >= ComBufferSize - sizeof(u32) - n)
            flush();
    }

    if (offset != 0)
        flush();

    KingEditor::instance()->log(getName(), "[ArrayEnd]");
}

template <typename T>
void Manager::doSyncArray(const sead::PtrArray<sead::PtrArray<FlagBase>>& array, u8* buffer,
                          const char* description) {
    KingEditor::instance()->log(getName(), "[ArrayStart]");

    for (auto& flags : array) {
        u32 written = [&] {
            u32 offset = 0;

            auto it = flags.begin();
            const auto end = flags.end();
            writeToBuffer(buffer, &offset, flags[0]->getHash());

            for (; it != end; ++it) {
                writeToBuffer(buffer, &offset, static_cast<Flag<T>&>(*it).getValueRef());
                if (offset >= ComBufferSize - sizeof(T))
                    break;
            }
            return offset;
        }();

        if (written != 0)
            KingEditor::instance()->log(getName(), description, buffer, written);
    }

    KingEditor::instance()->log(getName(), "[ArrayEnd]");
}

template <int N>
void Manager::doSyncArrayStr(const sead::PtrArray<sead::PtrArray<FlagBase>>& array, u8* buffer,
                             const char* description, u32 n) {
    KingEditor::instance()->log(getName(), "[ArrayStart]");

    for (auto& flags : array) {
        u32 written = [&] {
            u32 offset = 0;

            auto it = flags.begin();
            const auto end = flags.end();
            writeToBuffer(buffer, &offset, flags[0]->getHash());

            for (; it != end; ++it) {
                const auto& flag = static_cast<const Flag<sead::FixedSafeString<N>>&>(*it);

                const auto len = flag.getValueRef().calcLength();
                sead::MemUtil::copy(buffer + offset, flag.getValueRef().cstr(), len);
                sead::MemUtil::fillZero(buffer + u32(offset + len), n - len);
                offset += n;

                if (offset >= u32(ComBufferSize) - n)
                    break;
            }
            return offset;
        }();

        if (written != 0)
            KingEditor::instance()->log(getName(), description, buffer, written);
    }

    KingEditor::instance()->log(getName(), "[ArrayEnd]");
}

template <typename T>
static u32 syncOneVec(Manager*, u8* buffer, const sead::PtrArray<FlagBase>& flags, u32 n) {
    u32 offset = 0;

    auto it = flags.begin();
    const auto end = flags.end();
    writeToBuffer(buffer, &offset, flags[0]->getHash());

    for (; it != end; ++it) {
        for (u32 i = 0; i < n; ++i)
            writeToBuffer(buffer, &offset, static_cast<const Flag<T>&>(*it).getValueRef().e[i]);

        if (offset >= u32(ComBufferSize) - n)
            break;
    }
    return offset;
}

template <typename T>
void Manager::doSyncArrayVec(const sead::PtrArray<sead::PtrArray<FlagBase>>& array, u8* buffer,
                             const char* description, u32 n) {
    KingEditor::instance()->log(getName(), "[ArrayStart]");

    for (auto& flags : array) {
        u32 written = syncOneVec<T>(this, buffer, flags, n);
        if (written != 0)
            KingEditor::instance()->log(getName(), description, buffer, written);
    }

    KingEditor::instance()->log(getName(), "[ArrayEnd]");
}

}  // namespace ksys::gdt

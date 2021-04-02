#include "KingSystem/GameData/gdtManager.h"
#include <algorithm>
#include <devenv/seadEnvUtil.h>
#include <framework/seadFramework.h>
#include <mc/seadCoreInfo.h>
#include <thread/seadThreadUtil.h>
#include <time/seadTickTime.h>
#include "Game/DLC/aocManager.h"
#include "KingSystem/GameData/gdtSaveMgr.h"
#include "KingSystem/GameData/gdtTriggerParam.h"
#include "KingSystem/Resource/resEntryFactory.h"
#include "KingSystem/Resource/resResourceGameData.h"
#include "KingSystem/Resource/resSystem.h"
#include "KingSystem/Utils/HeapUtil.h"
#include "KingSystem/Utils/InitTimeInfo.h"

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

}  // namespace ksys::gdt

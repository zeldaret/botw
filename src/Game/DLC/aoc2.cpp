#include "Game/DLC/aoc2.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/actTag.h"
#include "KingSystem/Utils/InitTimeInfo.h"

namespace uking {

SEAD_ENUM_IMPL(aoc2::HardModeChange)
SEAD_ENUM_IMPL(aoc2::Flag)
SEAD_ENUM_IMPL(aoc2::MultiplierType)
SEAD_SINGLETON_DISPOSER_IMPL(aoc2)

namespace {
struct aoc2StaticData {
    ksys::util::InitConstants init_constants;
    sead::SafeString flag_name_HardMode_HighScore{"HardMode_HighScore"};
    sead::SafeString flag_name_AoC_HardMode_Enabled{"AoC_HardMode_Enabled"};
    sead::SafeString flag_name_IsLastPlayHardMode{"IsLastPlayHardMode"};
};

aoc2StaticData sData;
sead::FixedSafeString<64> sStr{""};
}  // namespace

aoc2::aoc2()
    : mGdtResetSlot{sead::Delegate1<aoc2, ksys::gdt::Manager::ResetEvent*>(
          this, &aoc2::setHardModeEnabledFlag)},
      mGdtReinitSlot{
          sead::Delegate1<aoc2, ksys::gdt::Manager::ReinitEvent*>(this, &aoc2::initFlagHandles)} {
    mMultipliers.fill(0.5);

    setHardModeChange(HardModeChange::IsLastPlayHardMode, true);
    setHardModeChange(HardModeChange::EnableShorterEnemyNotice, true);
    setHardModeChange(HardModeChange::EnableLifeRegen, true);
    setHardModeChange(HardModeChange::DisableNoDeathDamage, true);
    setHardModeChange(HardModeChange::PatchGanonStunLock, true);
    setHardModeChange(HardModeChange::RandomizeGuardianChargeBeam, true);
    setHardModeChange(HardModeChange::ApplyDamageMultiplier, true);
}

void aoc2::setHardModeEnabledFlag(ksys::gdt::Manager::ResetEvent*) {
    ksys::gdt::Manager::instance()->setBool(true, mAoCHardModeEnabledFlag);
    mGdtResetSlot.release();
}

void aoc2::initFlagHandles(ksys::gdt::Manager::ReinitEvent*) {
    auto* gdm = ksys::gdt::Manager::instance();
    mHardModeHighScoreFlag = gdm->getS32Handle(sData.flag_name_HardMode_HighScore);
    mAoCHardModeEnabledFlag = gdm->getBoolHandle(sData.flag_name_AoC_HardMode_Enabled);
    mIsLastPlayHardModeFlag = gdm->getBoolHandle(sData.flag_name_IsLastPlayHardMode);
}

aoc2::~aoc2() {
    mFileHandle.requestUnload2();
    if (_120) {
        // TODO: use the normal operator delete once we figure out what _120 is
        ::operator delete(_120);
        _120 = nullptr;
    }
}

void aoc2::init(sead::Heap*) {
    init_();
}

void aoc2::init_() {
    initFlagHandles();
    ksys::gdt::Manager::instance()->addReinitCallback(mGdtReinitSlot);
}

void aoc2::nerfHpRestore(f32* hp) const {
    *hp = sead::Mathf::max(*hp * getMultiplier(MultiplierType::HpRestore), 1.0f);
}

void aoc2::nerfHpRestore(s32* hp) const {
    *hp = sead::Mathi::max(*hp * getMultiplier(MultiplierType::HpRestore), 1);
}

void aoc2::modifyEnemyNoticeDuration(f32* value) const {
    *value = sead::Mathf::max(*value * getMultiplier(MultiplierType::EnemyNoticeDuration), 0);
}

bool aoc2::shouldApplyMasterModeDamageMultiplier(const ksys::act::ActorConstDataAccess& accessor) {
    if (!accessor.hasProc())
        return false;

    ksys::act::ActorConstDataAccess parent;
    if (accessor.hasConnectedCalcParent() && accessor.acquireConnectedCalcParent(&parent))
        return shouldApplyMasterModeDamageMultiplier(parent);

    if (accessor.hasTag(ksys::act::tags::IsMasterModeDamageMultiplierActor) ||
        (aoc2::instance() && aoc2::instance()->isTestOfStrengthShrine() &&
         accessor.hasTag(ksys::act::tags::AncientGuardTarget))) {
        return true;
    }

    const sead::SafeString& profile = accessor.getProfile();
    const sead::SafeString& name = accessor.getName();

    if (profile == "LastBoss" || profile == "SiteBoss")
        return true;

    if (name == "Enemy_GanonBeast" || name == "GanonShockWave" || name == "EnemyGanonShockWave" ||
        name == "GanonSeaOfFlame" || name == "GanonFlameBall" || name == "GanonPillarOfFlame" ||
        name == "GanonNormalArrow" || name == "GanonSpearForThrowing" || name == "CurseGanonBeam" ||
        name == "GanonBeam" || name == "GanonIceBullet" || name == "GanonThunder" ||
        name == "GanonIronPile" || name == "GanonTornado" || name == "GanonBeastBeam" ||
        name == "SiteBossSeaOfFlame" || name == "SiteBossSeaOfFlameRotate" ||
        name == "SiteBossFlameBall" || name == "SiteBossBigFlameBall" ||
        name == "SiteBossPillarOfFlame" || name == "SiteBossWearFlame" ||
        name == "SiteBossDrawingFlameTornado" || name == "SiteBossGaleArrow" ||
        name == "SiteBossNormalArrow" || name == "SiteBossSpearForThrowing" ||
        name == "SiteBossReflectArrow" || name == "ArrowRainChild" ||
        name == "SiteBossSpearIceBullet" || name == "SiteBossTornado" ||
        name == "LastBossThunder" || name == "Enemy_Assassin_Senior" ||
        name == "AssassinRockBall" || name == "AssassinIronBall") {
        return true;
    }

    return false;
}

void aoc2::buffDamage(s32& damage) {
    damage = damage * 1.5f;
    if (damage == 1) {
        damage = 2;
    }
}

void aoc2::loadIsLastPlayHardModeFlag() {
    bool value{};
    ksys::gdt::Manager::instance()->getBool(mIsLastPlayHardModeFlag, &value);
    const bool x = value;
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
    setFlag(Flag::EnableHardMode, x);
}

void aoc2::loadIsHardModeFlag() {
    bool value{};
    ksys::gdt::Manager::instance()->getBool(mAoCHardModeEnabledFlag, &value);
    const bool x = value;
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
    setFlag(Flag::EnableHardMode, x);
}

void aoc2::storeIsLastPlayHardModeFlag() {
    ksys::gdt::Manager::instance()->setBool(checkFlag(Flag::EnableHardMode),
                                            mIsLastPlayHardModeFlag);
}

void aoc2::resetIsLastPlayHardModeFlag() {
    ksys::gdt::Manager::instance()->setBool(false, "IsLastPlayHardMode");
}

bool aoc2::isTestOfStrengthShrine() const {
    if (mMapType != "CDungeon")
        return false;

    // There are 20 ToS shrines in the base game (070-089).
    if (mMapName.startsWith("Dungeon07") || mMapName.startsWith("Dungeon08"))
        return true;

    // Ruvo Korbah
    if (mMapName == "Dungeon135")
        return true;

    return false;
}

void aoc2::calc() {
    volatile u32 unused = 0;
    static_cast<void>(unused);
}

bool aoc2::rankUpEnemy(const sead::SafeString& actor_name, const ksys::map::Object& obj,
                       const char** new_name) {
    if (obj.getFlags().isOn(ksys::map::Object::Flag::HasUniqueName) ||
        obj.getHardModeFlags().isOn(ksys::map::Object::HardModeFlag::DisableRankup)) {
        return false;
    }

    if (!actor_name.startsWith("Enemy"))
        return false;

    if (isTestOfStrengthShrine())
        return false;

    sead::SafeString next = "";

    /// @bug Yes, this is duplicated and shouldn't exist.
    if (!actor_name.startsWith("Enemy"))
        return false;

    if (actor_name == "Enemy_Assassin_Junior")
        next = "Enemy_Assassin_Middle";
    else if (actor_name == "Enemy_Assassin_Middle")
        next = "Enemy_Assassin_Senior";
    else if (actor_name == "Enemy_Assassin_Shooter_Junior")
        next = "Enemy_Assassin_Shooter_Azito_Junior";

    else if (actor_name == "Enemy_Bokoblin_Junior")
        next = "Enemy_Bokoblin_Middle";
    else if (actor_name == "Enemy_Bokoblin_Middle")
        next = "Enemy_Bokoblin_Senior";
    else if (actor_name == "Enemy_Bokoblin_Senior")
        next = "Enemy_Bokoblin_Dark";
    else if (actor_name == "Enemy_Bokoblin_Dark")
        next = "Enemy_Bokoblin_Gold";

    else if (actor_name == "Enemy_Bokoblin_Guard_Junior")
        next = "Enemy_Bokoblin_Guard_Middle";

    else if (actor_name == "Enemy_Bokoblin_Guard_Junior_Ambush")
        next = "Enemy_Bokoblin_Guard_Middle_Ambush";

    else if (actor_name == "Enemy_Bokoblin_Guard_Junior_TreeHouseTop")
        next = "Enemy_Bokoblin_Guard_Middle_TreeHouseTop";

    /// @bug Yes, this is duplicated and shouldn't exist.
    else if (actor_name == "Enemy_Bokoblin_Guard_Junior_Ambush")
        next = "Enemy_Bokoblin_Guard_Middle_Ambush";

    else if (actor_name == "Enemy_Chuchu_Electric_Junior")
        next = "Enemy_Chuchu_Electric_Middle";
    else if (actor_name == "Enemy_Chuchu_Electric_Middle")
        next = "Enemy_Chuchu_Electric_Senior";

    else if (actor_name == "Enemy_Chuchu_Fire_Junior")
        next = "Enemy_Chuchu_Fire_Middle";
    else if (actor_name == "Enemy_Chuchu_Fire_Middle")
        next = "Enemy_Chuchu_Fire_Senior";

    else if (actor_name == "Enemy_Chuchu_Ice_Junior")
        next = "Enemy_Chuchu_Ice_Middle";
    else if (actor_name == "Enemy_Chuchu_Ice_Middle")
        next = "Enemy_Chuchu_Ice_Senior";

    else if (actor_name == "Enemy_Chuchu_Junior")
        next = "Enemy_Chuchu_Middle";
    else if (actor_name == "Enemy_Chuchu_Middle")
        next = "Enemy_Chuchu_Senior";

    else if (actor_name == "Enemy_Giant_Junior")
        next = "Enemy_Giant_Middle";
    else if (actor_name == "Enemy_Giant_Middle")
        next = "Enemy_Giant_Senior";

    else if (actor_name == "Enemy_Golem_Junior")
        next = "Enemy_Golem_Middle";
    else if (actor_name == "Enemy_Golem_Middle")
        next = "Enemy_Golem_Senior";

    else if (actor_name == "Enemy_Guardian_Mini_Baby")
        next = "Enemy_Guardian_Mini_Junior";
    else if (actor_name == "Enemy_Guardian_Mini_Junior")
        next = "Enemy_Guardian_Mini_Middle";
    else if (actor_name == "Enemy_Guardian_Mini_Middle")
        next = "Enemy_Guardian_Mini_Senior";

    else if (actor_name == "Enemy_Guardian_Mini_Junior_DetachLineBeam")
        next = "Enemy_Guardian_Mini_Middle_DetachLineBeam";

    else if (actor_name == "Enemy_Lizalfos_Junior")
        next = "Enemy_Lizalfos_Middle";
    else if (actor_name == "Enemy_Lizalfos_Middle")
        next = "Enemy_Lizalfos_Senior";
    else if (actor_name == "Enemy_Lizalfos_Senior")
        next = "Enemy_Lizalfos_Dark";
    else if (actor_name == "Enemy_Lizalfos_Dark")
        next = "Enemy_Lizalfos_Gold";

    else if (actor_name == "Enemy_Lizalfos_Guard_Junior")
        next = "Enemy_Lizalfos_Guard_Middle";

    else if (actor_name == "Enemy_Lizalfos_Guard_Junior_LongVisibility")
        next = "Enemy_Lizalfos_Guard_Middle_LongVisibility";

    else if (actor_name == "Enemy_Lizalfos_Junior_Guard_Ambush")
        next = "Enemy_Lizalfos_Middle_Guard_Ambush";

    else if (actor_name == "Enemy_Lynel_Junior")
        next = "Enemy_Lynel_Middle";
    else if (actor_name == "Enemy_Lynel_Middle")
        next = "Enemy_Lynel_Senior";
    else if (actor_name == "Enemy_Lynel_Senior")
        next = "Enemy_Lynel_Dark";
    else if (actor_name == "Enemy_Lynel_Dark")
        next = "Enemy_Lynel_Gold";

    else if (actor_name == "Enemy_Moriblin_Junior")
        next = "Enemy_Moriblin_Middle";
    else if (actor_name == "Enemy_Moriblin_Middle")
        next = "Enemy_Moriblin_Senior";
    else if (actor_name == "Enemy_Moriblin_Senior")
        next = "Enemy_Moriblin_Dark";
    else if (actor_name == "Enemy_Moriblin_Dark")
        next = "Enemy_Moriblin_Gold";

    else if (actor_name == "Enemy_Wizzrobe_Electric")
        next = "Enemy_Wizzrobe_Electric_Senior";
    else if (actor_name == "Enemy_Wizzrobe_Fire")
        next = "Enemy_Wizzrobe_Fire_Senior";
    else if (actor_name == "Enemy_Wizzrobe_Ice")
        next = "Enemy_Wizzrobe_Ice_Senior";

    if (next.isEmpty())
        return false;

    *new_name = next.cstr();
    return true;
}

}  // namespace uking

#include "Game/DLC/aoc2.h"

namespace uking {

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

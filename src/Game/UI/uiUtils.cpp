#include "Game/UI/uiUtils.h"
#include "Game/Actor/actWeapon.h"
#include "Game/DLC/aoc2.h"
#include "Game/UI/uiPauseMenuDataMgr.h"
#include "KingSystem/ActorSystem/actInfoCommon.h"
#include "KingSystem/ActorSystem/actInfoData.h"
#include "KingSystem/Utils/Byaml/Byaml.h"

namespace uking::ui {

bool isMasterSwordItem(const PouchItem& item) {
    return item.getType() == PouchItemType::Sword && isMasterSwordActorName(item.getName());
}

int getItemHitPointRecover(const sead::SafeString& name) {
    auto* info = ksys::act::InfoData::instance();
    if (!info)
        return 0;

    al::ByamlIter iter;
    if (!info->getActorIter(&iter, name.cstr()))
        return 0;
    if (!info->hasTag(iter, ksys::act::tags::CureItem))
        return 0;
    if (!info->hasTag(iter, ksys::act::tags::CanUse))
        return 0;

    int value = ksys::act::getCureItemHitPointRecover(iter);

    if (aoc2::instance() && aoc2::instance()->checkFlag(aoc2::Flag::EnableHardMode) &&
        aoc2::instance()->isHardModeChangeOn(aoc2::HardModeChange::NerfHpRestore)) {
        aoc2::instance()->nerfHpRestore(&value);
    }

    return value;
}

int getWeaponInventoryLife(const sead::SafeString& name) {
    auto* info = ksys::act::InfoData::instance();
    if (!info)
        return 0;
    const int life = ksys::act::getGeneralLife(info, name.cstr());
    return act::WeaponModifierInfo::getLifeMultiplier() * life;
}

bool isMasterSwordActorName(const sead::SafeString& name) {
    return name == "Weapon_Sword_070";
}

}  // namespace uking::ui

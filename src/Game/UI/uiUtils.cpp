#include "Game/UI/uiUtils.h"
#include "Game/Actor/actWeapon.h"
#include "KingSystem/ActorSystem/actInfoCommon.h"
#include "KingSystem/ActorSystem/actInfoData.h"
#include "Game/UI/uiPauseMenuDataMgr.h"

namespace uking::ui {

bool isMasterSwordItem(const PouchItem& item) {
    return item.getType() == PouchItemType::Sword && isMasterSwordActorName(item.getName());
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

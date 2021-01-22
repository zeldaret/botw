#pragma once

#include <prim/seadSafeString.h>
#include "Game/Actor/actWeapon.h"

namespace uking::ui {

class PouchItem;

struct WeaponStats {
    int durability{};
    /// Attack power (for offensive weapons) or guard power (for shields).
    int power{};
    act::WeaponModifierInfo modifier{};
    /// Bow modifier value ("add value") or 0 for weapons that are not bows.
    int bow_add_value{};
};

bool isMasterSwordItem(const PouchItem& item);

int getItemHitPointRecover(const sead::SafeString& name);

void getWeaponStats(const PouchItem& item, WeaponStats* stats);
int getBowActorInfoAddValue(const sead::SafeString& name);

int getWeaponInventoryLife(const sead::SafeString& name);
bool isMasterSwordActorName(const sead::SafeString& name);

// TODO: move these to another translation unit (TBD)
// Do not implement until the location is figured out
bool isOneHitObliteratorActorName(const sead::SafeString& name);
int getItemGeneralLife(const char* name);

// TODO: move this to yet another translation unit (TBD but not the same one as the above)
void addItemForDebug(const sead::SafeString& name, int value);

}  // namespace uking::ui

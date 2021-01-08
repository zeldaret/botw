#pragma once

#include <prim/seadSafeString.h>

namespace uking::ui {

int getWeaponInventoryLife(const sead::SafeString& name);
bool isMasterSwordActorName(const sead::SafeString& name);

}  // namespace uking::ui

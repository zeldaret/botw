#pragma once

#include <prim/seadSafeString.h>

namespace uking::ui {

int getWeaponInventoryLife(const sead::SafeString& name);
bool isMasterSwordActorName(const sead::SafeString& name);

// TODO: move this to another translation unit (TBD)
int getItemGeneralLife(const char* name);

}  // namespace uking::ui

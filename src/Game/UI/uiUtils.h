#pragma once

#include <prim/seadSafeString.h>

namespace uking::ui {

class PouchItem;

bool isMasterSwordItem(const PouchItem& item);
int getWeaponInventoryLife(const sead::SafeString& name);
bool isMasterSwordActorName(const sead::SafeString& name);

// TODO: move this to another translation unit (TBD)
int getItemGeneralLife(const char* name);

// TODO: move this to yet another translation unit (TBD but not the same one as the above)
void addItemForDebug(const sead::SafeString& name, int value);

}  // namespace uking::ui

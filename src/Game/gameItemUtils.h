#pragma once

#include <heap/seadHeap.h>
#include "Game/Actor/actWeapon.h"

// 710073c5b4
void spawnDroppedInventoryItem(const char* name, sead::Heap* heap, int life, bool sleep_after_init,
                               const uking::act::WeaponModifierInfo* weapon_modifiers,
                               bool spawn_via_carry_box, float rotate_y, float rotate_z);

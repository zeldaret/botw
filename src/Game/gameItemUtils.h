#pragma once

namespace sead {
class Heap;
}  // namespace sead
namespace uking::act {
struct WeaponModifierInfo;
}  // namespace uking::act

namespace uking {

enum class SleepAfterInit : bool {
    Yes = true,
    No = false,
};

enum class SpawnViaCarryBox : bool {
    Yes = true,
    No = false,
};

// 710073c5b4
void spawnDroppedInventoryItem(const char* name, sead::Heap* heap, int life,
                               SleepAfterInit sleep_after_init,
                               const uking::act::WeaponModifierInfo* weapon_modifiers,
                               SpawnViaCarryBox spawn_via_carry_box, float rotate_y,
                               float rotate_z);
}  // namespace uking

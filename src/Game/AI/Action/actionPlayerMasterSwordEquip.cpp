#include "Game/AI/Action/actionPlayerMasterSwordEquip.h"

namespace uking::action {

PlayerMasterSwordEquip::PlayerMasterSwordEquip(const InitArg& arg) : PlayerAction(arg) {}

PlayerMasterSwordEquip::~PlayerMasterSwordEquip() = default;

bool PlayerMasterSwordEquip::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

}  // namespace uking::action

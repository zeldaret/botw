#include "Game/AI/Action/actionSetPlayerStateToUnequipAndWait.h"

namespace uking::action {

SetPlayerStateToUnequipAndWait::SetPlayerStateToUnequipAndWait(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

SetPlayerStateToUnequipAndWait::~SetPlayerStateToUnequipAndWait() = default;

bool SetPlayerStateToUnequipAndWait::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SetPlayerStateToUnequipAndWait::loadParams_() {}

}  // namespace uking::action

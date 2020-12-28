#include "Game/AI/Action/actionPlayerSetWakeUpMtx.h"

namespace uking::action {

PlayerSetWakeUpMtx::PlayerSetWakeUpMtx(const InitArg& arg) : ksys::act::ai::Action(arg) {}

PlayerSetWakeUpMtx::~PlayerSetWakeUpMtx() = default;

bool PlayerSetWakeUpMtx::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void PlayerSetWakeUpMtx::loadParams_() {}

}  // namespace uking::action

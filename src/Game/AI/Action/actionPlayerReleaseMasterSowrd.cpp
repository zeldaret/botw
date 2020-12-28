#include "Game/AI/Action/actionPlayerReleaseMasterSowrd.h"

namespace uking::action {

PlayerReleaseMasterSowrd::PlayerReleaseMasterSowrd(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

PlayerReleaseMasterSowrd::~PlayerReleaseMasterSowrd() = default;

bool PlayerReleaseMasterSowrd::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void PlayerReleaseMasterSowrd::loadParams_() {}

}  // namespace uking::action

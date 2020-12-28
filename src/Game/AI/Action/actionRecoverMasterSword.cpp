#include "Game/AI/Action/actionRecoverMasterSword.h"

namespace uking::action {

RecoverMasterSword::RecoverMasterSword(const InitArg& arg) : ksys::act::ai::Action(arg) {}

RecoverMasterSword::~RecoverMasterSword() = default;

bool RecoverMasterSword::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void RecoverMasterSword::loadParams_() {}

}  // namespace uking::action

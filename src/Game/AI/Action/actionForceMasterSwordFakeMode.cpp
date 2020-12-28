#include "Game/AI/Action/actionForceMasterSwordFakeMode.h"

namespace uking::action {

ForceMasterSwordFakeMode::ForceMasterSwordFakeMode(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ForceMasterSwordFakeMode::~ForceMasterSwordFakeMode() = default;

bool ForceMasterSwordFakeMode::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForceMasterSwordFakeMode::loadParams_() {}

}  // namespace uking::action

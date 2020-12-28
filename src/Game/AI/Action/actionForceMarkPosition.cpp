#include "Game/AI/Action/actionForceMarkPosition.h"

namespace uking::action {

ForceMarkPosition::ForceMarkPosition(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForceMarkPosition::~ForceMarkPosition() = default;

bool ForceMarkPosition::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForceMarkPosition::loadParams_() {
    getDynamicParam(&mPinColorIdx_d, "PinColorIdx");
}

}  // namespace uking::action

#include "Game/AI/Action/actionMarkPosition.h"

namespace uking::action {

MarkPosition::MarkPosition(const InitArg& arg) : ksys::act::ai::Action(arg) {}

MarkPosition::~MarkPosition() = default;

bool MarkPosition::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void MarkPosition::loadParams_() {
    getDynamicParam(&mPositionX_d, "PositionX");
    getDynamicParam(&mPositionY_d, "PositionY");
    getDynamicParam(&mPositionZ_d, "PositionZ");
}

}  // namespace uking::action

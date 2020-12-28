#include "Game/AI/Action/actionForceEndPlayerSlow.h"

namespace uking::action {

ForceEndPlayerSlow::ForceEndPlayerSlow(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForceEndPlayerSlow::~ForceEndPlayerSlow() = default;

bool ForceEndPlayerSlow::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForceEndPlayerSlow::loadParams_() {}

}  // namespace uking::action

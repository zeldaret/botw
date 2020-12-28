#include "Game/AI/Action/actionReceiveTerror.h"

namespace uking::action {

ReceiveTerror::ReceiveTerror(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ReceiveTerror::~ReceiveTerror() = default;

bool ReceiveTerror::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ReceiveTerror::loadParams_() {}

}  // namespace uking::action

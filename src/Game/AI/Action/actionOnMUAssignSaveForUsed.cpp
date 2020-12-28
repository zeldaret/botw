#include "Game/AI/Action/actionOnMUAssignSaveForUsed.h"

namespace uking::action {

OnMUAssignSaveForUsed::OnMUAssignSaveForUsed(const InitArg& arg) : ksys::act::ai::Action(arg) {}

OnMUAssignSaveForUsed::~OnMUAssignSaveForUsed() = default;

bool OnMUAssignSaveForUsed::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void OnMUAssignSaveForUsed::loadParams_() {}

}  // namespace uking::action

#include "Game/AI/Action/actionCustomDuckingEndAction.h"

namespace uking::action {

CustomDuckingEndAction::CustomDuckingEndAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

CustomDuckingEndAction::~CustomDuckingEndAction() = default;

bool CustomDuckingEndAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void CustomDuckingEndAction::loadParams_() {}

}  // namespace uking::action

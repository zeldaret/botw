#include "Game/AI/Action/actionSetRetryDataAction.h"

namespace uking::action {

SetRetryDataAction::SetRetryDataAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SetRetryDataAction::~SetRetryDataAction() = default;

bool SetRetryDataAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SetRetryDataAction::loadParams_() {}

}  // namespace uking::action

#include "Game/AI/Action/actionFreeMovingAction.h"

namespace uking::action {

FreeMovingAction::FreeMovingAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

FreeMovingAction::~FreeMovingAction() = default;

bool FreeMovingAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void FreeMovingAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void FreeMovingAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void FreeMovingAction::loadParams_() {}

void FreeMovingAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

#include "Game/AI/Action/actionSetEnableRayHit.h"

namespace uking::action {

SetEnableRayHit::SetEnableRayHit(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SetEnableRayHit::~SetEnableRayHit() = default;

bool SetEnableRayHit::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SetEnableRayHit::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SetEnableRayHit::leave_() {
    ksys::act::ai::Action::leave_();
}

void SetEnableRayHit::loadParams_() {}

void SetEnableRayHit::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

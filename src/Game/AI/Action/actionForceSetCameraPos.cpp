#include "Game/AI/Action/actionForceSetCameraPos.h"

namespace uking::action {

ForceSetCameraPos::ForceSetCameraPos(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForceSetCameraPos::~ForceSetCameraPos() = default;

bool ForceSetCameraPos::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForceSetCameraPos::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForceSetCameraPos::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForceSetCameraPos::loadParams_() {}

void ForceSetCameraPos::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

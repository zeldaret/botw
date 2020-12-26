#include "Game/AI/Action/actionMoveKeyFramed.h"

namespace uking::action {

MoveKeyFramed::MoveKeyFramed(const InitArg& arg) : ksys::act::ai::Action(arg) {}

MoveKeyFramed::~MoveKeyFramed() = default;

bool MoveKeyFramed::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void MoveKeyFramed::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void MoveKeyFramed::leave_() {
    ksys::act::ai::Action::leave_();
}

void MoveKeyFramed::loadParams_() {
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mAxisY_d, "AxisY");
    getDynamicParam(&mAxisZ_d, "AxisZ");
}

void MoveKeyFramed::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

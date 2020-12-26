#include "Game/AI/Action/actionMoveMainRidigBody.h"

namespace uking::action {

MoveMainRidigBody::MoveMainRidigBody(const InitArg& arg) : ksys::act::ai::Action(arg) {}

MoveMainRidigBody::~MoveMainRidigBody() = default;

bool MoveMainRidigBody::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void MoveMainRidigBody::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void MoveMainRidigBody::leave_() {
    ksys::act::ai::Action::leave_();
}

void MoveMainRidigBody::loadParams_() {
    getStaticParam(&mFinLength_s, "FinLength");
    getStaticParam(&mMaxSpeed_s, "MaxSpeed");
    getStaticParam(&mVibrateStopCheck_s, "VibrateStopCheck");
    getStaticParam(&mVibrateCheckFrame_s, "VibrateCheckFrame");
    getStaticParam(&mVibrateMemoryStep_s, "VibrateMemoryStep");
    getStaticParam(&mTargetPosOffset_s, "TargetPosOffset");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getAITreeVariable(&mRefPosVibrateChecker_a, "RefPosVibrateChecker");
}

void MoveMainRidigBody::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

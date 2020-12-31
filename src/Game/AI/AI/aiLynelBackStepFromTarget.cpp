#include "Game/AI/AI/aiLynelBackStepFromTarget.h"

namespace uking::ai {

LynelBackStepFromTarget::LynelBackStepFromTarget(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

LynelBackStepFromTarget::~LynelBackStepFromTarget() = default;

bool LynelBackStepFromTarget::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void LynelBackStepFromTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void LynelBackStepFromTarget::leave_() {
    ksys::act::ai::Ai::leave_();
}

void LynelBackStepFromTarget::loadParams_() {
    getStaticParam(&mMoveDistMin_s, "MoveDistMin");
    getStaticParam(&mMoveDist_s, "MoveDist");
    getStaticParam(&mAddCheckAngle_s, "AddCheckAngle");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai

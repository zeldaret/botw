#include "Game/AI/AI/aiSimpleEscapeFromTarget.h"

namespace uking::ai {

SimpleEscapeFromTarget::SimpleEscapeFromTarget(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SimpleEscapeFromTarget::~SimpleEscapeFromTarget() = default;

bool SimpleEscapeFromTarget::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SimpleEscapeFromTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SimpleEscapeFromTarget::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SimpleEscapeFromTarget::loadParams_() {
    getStaticParam(&mKeepTime_s, "KeepTime");
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mSpaceDist_s, "SpaceDist");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai

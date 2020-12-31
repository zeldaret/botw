#include "Game/AI/AI/aiReflectableEscape.h"

namespace uking::ai {

ReflectableEscape::ReflectableEscape(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ReflectableEscape::~ReflectableEscape() = default;

bool ReflectableEscape::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void ReflectableEscape::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void ReflectableEscape::leave_() {
    ksys::act::ai::Ai::leave_();
}

void ReflectableEscape::loadParams_() {
    getStaticParam(&mEscapeDist_s, "EscapeDist");
    getStaticParam(&mNearDist_s, "NearDist");
    getStaticParam(&mEscapeTimer_s, "EscapeTimer");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai

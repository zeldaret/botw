#include "Game/AI/AI/aiSunazarashiEscapeMove.h"

namespace uking::ai {

SunazarashiEscapeMove::SunazarashiEscapeMove(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SunazarashiEscapeMove::~SunazarashiEscapeMove() = default;

bool SunazarashiEscapeMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SunazarashiEscapeMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SunazarashiEscapeMove::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SunazarashiEscapeMove::loadParams_() {
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai

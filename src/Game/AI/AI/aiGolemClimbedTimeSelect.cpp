#include "Game/AI/AI/aiGolemClimbedTimeSelect.h"

namespace uking::ai {

GolemClimbedTimeSelect::GolemClimbedTimeSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GolemClimbedTimeSelect::~GolemClimbedTimeSelect() = default;

bool GolemClimbedTimeSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GolemClimbedTimeSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void GolemClimbedTimeSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GolemClimbedTimeSelect::loadParams_() {
    getStaticParam(&mLimitTime_s, "LimitTime");
    getAITreeVariable(&mGolemClimbedTime_a, "GolemClimbedTime");
}

}  // namespace uking::ai

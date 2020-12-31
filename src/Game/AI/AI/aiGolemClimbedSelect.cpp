#include "Game/AI/AI/aiGolemClimbedSelect.h"

namespace uking::ai {

GolemClimbedSelect::GolemClimbedSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GolemClimbedSelect::~GolemClimbedSelect() = default;

bool GolemClimbedSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GolemClimbedSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void GolemClimbedSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GolemClimbedSelect::loadParams_() {
    getStaticParam(&mClimbTime_s, "ClimbTime");
    getAITreeVariable(&mGolemClimbedTime_a, "GolemClimbedTime");
}

}  // namespace uking::ai

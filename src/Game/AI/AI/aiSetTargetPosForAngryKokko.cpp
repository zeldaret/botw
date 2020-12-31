#include "Game/AI/AI/aiSetTargetPosForAngryKokko.h"

namespace uking::ai {

SetTargetPosForAngryKokko::SetTargetPosForAngryKokko(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SetTargetPosForAngryKokko::~SetTargetPosForAngryKokko() = default;

bool SetTargetPosForAngryKokko::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SetTargetPosForAngryKokko::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SetTargetPosForAngryKokko::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SetTargetPosForAngryKokko::loadParams_() {
    getStaticParam(&mUpdateTargetInterval_s, "UpdateTargetInterval");
    getStaticParam(&mMaxUpdateNum_s, "MaxUpdateNum");
    getStaticParam(&mAddLength_s, "AddLength");
    getStaticParam(&mHeightOffset_s, "HeightOffset");
    getStaticParam(&mRandRange_s, "RandRange");
    getStaticParam(&mRandRate_s, "RandRate");
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

}  // namespace uking::ai

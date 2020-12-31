#include "Game/AI/AI/aiTargetPosLostCheck.h"

namespace uking::ai {

TargetPosLostCheck::TargetPosLostCheck(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

TargetPosLostCheck::~TargetPosLostCheck() = default;

bool TargetPosLostCheck::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void TargetPosLostCheck::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void TargetPosLostCheck::leave_() {
    ksys::act::ai::Ai::leave_();
}

void TargetPosLostCheck::loadParams_() {
    getStaticParam(&mLostTimer_s, "LostTimer");
    getStaticParam(&mLostVMin_s, "LostVMin");
    getStaticParam(&mLostVMax_s, "LostVMax");
    getStaticParam(&mLostRange_s, "LostRange");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai

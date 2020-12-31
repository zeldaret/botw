#include "Game/AI/AI/aiFishGoToAndNibble.h"

namespace uking::ai {

FishGoToAndNibble::FishGoToAndNibble(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

FishGoToAndNibble::~FishGoToAndNibble() = default;

bool FishGoToAndNibble::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void FishGoToAndNibble::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void FishGoToAndNibble::leave_() {
    ksys::act::ai::Ai::leave_();
}

void FishGoToAndNibble::loadParams_() {
    getStaticParam(&mNumTimeNibbleMin_s, "NumTimeNibbleMin");
    getStaticParam(&mNumTimeNibbleRand_s, "NumTimeNibbleRand");
    getStaticParam(&mDistStartNibble_s, "DistStartNibble");
    getStaticParam(&mDistBackward_s, "DistBackward");
    getStaticParam(&mDepthGiveUp_s, "DepthGiveUp");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

}  // namespace uking::ai

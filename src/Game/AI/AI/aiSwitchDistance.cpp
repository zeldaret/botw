#include "Game/AI/AI/aiSwitchDistance.h"

namespace uking::ai {

SwitchDistance::SwitchDistance(const InitArg& arg) : SwitchAI(arg) {}

SwitchDistance::~SwitchDistance() = default;

bool SwitchDistance::init_(sead::Heap* heap) {
    return SwitchAI::init_(heap);
}

void SwitchDistance::enter_(ksys::act::ai::InlineParamPack* params) {
    SwitchAI::enter_(params);
}

void SwitchDistance::leave_() {
    SwitchAI::leave_();
}

void SwitchDistance::loadParams_() {
    SwitchAI::loadParams_();
    getStaticParam(&mOnDis_s, "OnDis");
    getStaticParam(&mOffsetDis_s, "OffsetDis");
    getStaticParam(&mChangeSeq_s, "ChangeSeq");
}

}  // namespace uking::ai

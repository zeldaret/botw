#include "Game/AI/AI/aiBeamExplodeBase.h"

namespace uking::ai {

BeamExplodeBase::BeamExplodeBase(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

BeamExplodeBase::~BeamExplodeBase() = default;

bool BeamExplodeBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void BeamExplodeBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void BeamExplodeBase::leave_() {
    ksys::act::ai::Ai::leave_();
}

void BeamExplodeBase::loadParams_() {
    getStaticParam(&mMaxDistance_s, "MaxDistance");
    getStaticParam(&mIsDelete_s, "IsDelete");
}

}  // namespace uking::ai

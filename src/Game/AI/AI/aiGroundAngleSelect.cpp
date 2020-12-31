#include "Game/AI/AI/aiGroundAngleSelect.h"

namespace uking::ai {

GroundAngleSelect::GroundAngleSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GroundAngleSelect::~GroundAngleSelect() = default;

bool GroundAngleSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GroundAngleSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void GroundAngleSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GroundAngleSelect::loadParams_() {
    getStaticParam(&mSlopeAngle_s, "SlopeAngle");
    getStaticParam(&mIsCheckEveryFrame_s, "IsCheckEveryFrame");
    getStaticParam(&mIsCheckActorMtx_s, "IsCheckActorMtx");
}

}  // namespace uking::ai

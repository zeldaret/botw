#include "Game/AI/AI/aiSubsAngleSelect.h"

namespace uking::ai {

SubsAngleSelect::SubsAngleSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SubsAngleSelect::~SubsAngleSelect() = default;

bool SubsAngleSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SubsAngleSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SubsAngleSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SubsAngleSelect::loadParams_() {
    getStaticParam(&mSubsAngle_s, "SubsAngle");
    getStaticParam(&mCheckOnce_s, "CheckOnce");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getStaticParam(&mYRotOnly_s, "YRotOnly");
}

}  // namespace uking::ai

#include "Game/AI/AI/aiTwnObjDlcFlightTrainingTarget.h"

namespace uking::ai {

TwnObjDlcFlightTrainingTarget::TwnObjDlcFlightTrainingTarget(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

TwnObjDlcFlightTrainingTarget::~TwnObjDlcFlightTrainingTarget() = default;

bool TwnObjDlcFlightTrainingTarget::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void TwnObjDlcFlightTrainingTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void TwnObjDlcFlightTrainingTarget::leave_() {
    ksys::act::ai::Ai::leave_();
}

void TwnObjDlcFlightTrainingTarget::loadParams_() {
    getStaticParam(&mLimitTime_s, "LimitTime");
}

}  // namespace uking::ai

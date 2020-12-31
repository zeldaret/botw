#include "Game/AI/AI/aiChmVolRateCheck.h"

namespace uking::ai {

ChmVolRateCheck::ChmVolRateCheck(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ChmVolRateCheck::~ChmVolRateCheck() = default;

bool ChmVolRateCheck::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void ChmVolRateCheck::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void ChmVolRateCheck::leave_() {
    ksys::act::ai::Ai::leave_();
}

void ChmVolRateCheck::loadParams_() {
    getStaticParam(&mVolTh_s, "VolTh");
    getStaticParam(&mDebugScale_s, "DebugScale");
    getStaticParam(&mDebugDraw_s, "DebugDraw");
    getStaticParam(&mIsInvalidBreakJudge_s, "IsInvalidBreakJudge");
    getMapUnitParam(&mFreezeTarget_m, "FreezeTarget");
    getMapUnitParam(&mIceBreakScale_m, "IceBreakScale");
}

}  // namespace uking::ai

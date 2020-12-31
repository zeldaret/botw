#include "Game/AI/AI/aiChmVolRateCheckBlankOk.h"

namespace uking::ai {

ChmVolRateCheckBlankOk::ChmVolRateCheckBlankOk(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ChmVolRateCheckBlankOk::~ChmVolRateCheckBlankOk() = default;

bool ChmVolRateCheckBlankOk::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void ChmVolRateCheckBlankOk::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void ChmVolRateCheckBlankOk::leave_() {
    ksys::act::ai::Ai::leave_();
}

void ChmVolRateCheckBlankOk::loadParams_() {
    getStaticParam(&mVolTh_s, "VolTh");
    getStaticParam(&mDebugScale_s, "DebugScale");
    getStaticParam(&mDebugDraw_s, "DebugDraw");
    getStaticParam(&mIsInvalidBreakJudge_s, "IsInvalidBreakJudge");
    getMapUnitParam(&mFreezeTarget_m, "FreezeTarget");
    getMapUnitParam(&mIceBreakScale_m, "IceBreakScale");
}

}  // namespace uking::ai

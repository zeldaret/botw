#include "Game/Actor/AI/aiBezierRailMove.h"

namespace uking::ai {

BezierRailMove::BezierRailMove(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

BezierRailMove::~BezierRailMove() = default;

bool BezierRailMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void BezierRailMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void BezierRailMove::leave_() {
    ksys::act::ai::Ai::leave_();
}

void BezierRailMove::loadParams_() {
    getStaticParam(&mIsIgnoreNoWaitStopPoint_s, "IsIgnoreNoWaitStopPoint");
}

}  // namespace uking::ai

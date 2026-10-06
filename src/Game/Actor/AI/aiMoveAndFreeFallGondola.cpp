#include "Game/Actor/AI/aiMoveAndFreeFallGondola.h"

namespace uking::ai {

MoveAndFreeFallGondola::MoveAndFreeFallGondola(const InitArg& arg) : BezierRailMove(arg) {}

MoveAndFreeFallGondola::~MoveAndFreeFallGondola() = default;

bool MoveAndFreeFallGondola::init_(sead::Heap* heap) {
    return BezierRailMove::init_(heap);
}

void MoveAndFreeFallGondola::enter_(ksys::act::ai::InlineParamPack* params) {
    BezierRailMove::enter_(params);
}

void MoveAndFreeFallGondola::leave_() {
    BezierRailMove::leave_();
}

void MoveAndFreeFallGondola::loadParams_() {
    BezierRailMove::loadParams_();
    getMapUnitParam(&mRailMoveSpeed_m, "RailMoveSpeed");
    getMapUnitParam(&mGondolaRailOffsetTime_m, "GondolaRailOffsetTime");
}

}  // namespace uking::ai

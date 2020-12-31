#include "Game/AI/AI/aiRailMove.h"

namespace uking::ai {

RailMove::RailMove(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

RailMove::~RailMove() = default;

bool RailMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void RailMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void RailMove::leave_() {
    ksys::act::ai::Ai::leave_();
}

void RailMove::loadParams_() {
    getStaticParam(&mIsIgnoreNoWaitStopPoint_s, "IsIgnoreNoWaitStopPoint");
}

}  // namespace uking::ai

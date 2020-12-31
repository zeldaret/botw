#include "Game/AI/AI/aiTrolleyOnRail.h"

namespace uking::ai {

TrolleyOnRail::TrolleyOnRail(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

TrolleyOnRail::~TrolleyOnRail() = default;

bool TrolleyOnRail::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void TrolleyOnRail::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void TrolleyOnRail::leave_() {
    ksys::act::ai::Ai::leave_();
}

void TrolleyOnRail::loadParams_() {
    getDynamicParam(&mRailDist_d, "RailDist");
    getDynamicParam(&mVelocityReduce_d, "VelocityReduce");
    getDynamicParam(&mRailPos_d, "RailPos");
    getDynamicParam(&mRailDir_d, "RailDir");
}

}  // namespace uking::ai

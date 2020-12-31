#include "Game/AI/AI/aiTrolleyGrabbedByMagnet.h"

namespace uking::ai {

TrolleyGrabbedByMagnet::TrolleyGrabbedByMagnet(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

TrolleyGrabbedByMagnet::~TrolleyGrabbedByMagnet() = default;

bool TrolleyGrabbedByMagnet::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void TrolleyGrabbedByMagnet::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void TrolleyGrabbedByMagnet::leave_() {
    ksys::act::ai::Ai::leave_();
}

void TrolleyGrabbedByMagnet::loadParams_() {
    getDynamicParam(&mRailDist_d, "RailDist");
    getDynamicParam(&mRailPos_d, "RailPos");
    getDynamicParam(&mRailDir_d, "RailDir");
}

}  // namespace uking::ai

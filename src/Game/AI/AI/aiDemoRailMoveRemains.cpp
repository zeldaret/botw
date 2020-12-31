#include "Game/AI/AI/aiDemoRailMoveRemains.h"

namespace uking::ai {

DemoRailMoveRemains::DemoRailMoveRemains(const InitArg& arg) : RailMoveRemains(arg) {}

DemoRailMoveRemains::~DemoRailMoveRemains() = default;

bool DemoRailMoveRemains::init_(sead::Heap* heap) {
    return RailMoveRemains::init_(heap);
}

void DemoRailMoveRemains::enter_(ksys::act::ai::InlineParamPack* params) {
    RailMoveRemains::enter_(params);
}

void DemoRailMoveRemains::leave_() {
    RailMoveRemains::leave_();
}

void DemoRailMoveRemains::loadParams_() {
    RailMoveRemains::loadParams_();
    getDynamicParam(&mDynSpeedScale_d, "DynSpeedScale");
    getDynamicParam(&mDynInitPosByRailRatio_d, "DynInitPosByRailRatio");
}

}  // namespace uking::ai

#include "Game/AI/AI/aiRailMoveObjectOneWay.h"

namespace uking::ai {

RailMoveObjectOneWay::RailMoveObjectOneWay(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

RailMoveObjectOneWay::~RailMoveObjectOneWay() = default;

bool RailMoveObjectOneWay::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void RailMoveObjectOneWay::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void RailMoveObjectOneWay::leave_() {
    ksys::act::ai::Ai::leave_();
}

void RailMoveObjectOneWay::loadParams_() {
    getStaticParam(&mASKeyName_On_s, "ASKeyName_On");
    getStaticParam(&mASKeyName_Off_s, "ASKeyName_Off");
}

}  // namespace uking::ai

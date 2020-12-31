#include "Game/AI/AI/aiHomePosDistanceSelector.h"

namespace uking::ai {

HomePosDistanceSelector::HomePosDistanceSelector(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

HomePosDistanceSelector::~HomePosDistanceSelector() = default;

bool HomePosDistanceSelector::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void HomePosDistanceSelector::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void HomePosDistanceSelector::leave_() {
    ksys::act::ai::Ai::leave_();
}

void HomePosDistanceSelector::loadParams_() {
    getStaticParam(&mBoundaryDistance_s, "BoundaryDistance");
}

}  // namespace uking::ai

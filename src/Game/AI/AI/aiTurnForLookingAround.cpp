#include "Game/AI/AI/aiTurnForLookingAround.h"

namespace uking::ai {

TurnForLookingAround::TurnForLookingAround(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

TurnForLookingAround::~TurnForLookingAround() = default;

bool TurnForLookingAround::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void TurnForLookingAround::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void TurnForLookingAround::leave_() {
    ksys::act::ai::Ai::leave_();
}

void TurnForLookingAround::loadParams_() {
    getStaticParam(&mAngle_s, "Angle");
}

}  // namespace uking::ai

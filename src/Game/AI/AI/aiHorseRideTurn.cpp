#include "Game/AI/AI/aiHorseRideTurn.h"

namespace uking::ai {

HorseRideTurn::HorseRideTurn(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

HorseRideTurn::~HorseRideTurn() = default;

bool HorseRideTurn::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void HorseRideTurn::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void HorseRideTurn::leave_() {
    ksys::act::ai::Ai::leave_();
}

void HorseRideTurn::loadParams_() {
    getStaticParam(&mFinAngle_s, "FinAngle");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai

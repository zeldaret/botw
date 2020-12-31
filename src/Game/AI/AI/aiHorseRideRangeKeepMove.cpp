#include "Game/AI/AI/aiHorseRideRangeKeepMove.h"

namespace uking::ai {

HorseRideRangeKeepMove::HorseRideRangeKeepMove(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

HorseRideRangeKeepMove::~HorseRideRangeKeepMove() = default;

bool HorseRideRangeKeepMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void HorseRideRangeKeepMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void HorseRideRangeKeepMove::leave_() {
    ksys::act::ai::Ai::leave_();
}

void HorseRideRangeKeepMove::loadParams_() {
    getStaticParam(&mOutDist_s, "OutDist");
    getStaticParam(&mBaseDist_s, "BaseDist");
}

}  // namespace uking::ai

#include "Game/AI/AI/aiHorseEscapeRouteRailAI.h"

namespace uking::ai {

HorseEscapeRouteRailAI::HorseEscapeRouteRailAI(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

HorseEscapeRouteRailAI::~HorseEscapeRouteRailAI() = default;

bool HorseEscapeRouteRailAI::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void HorseEscapeRouteRailAI::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void HorseEscapeRouteRailAI::leave_() {
    ksys::act::ai::Ai::leave_();
}

void HorseEscapeRouteRailAI::loadParams_() {
    getStaticParam(&mCount_s, "Count");
    getStaticParam(&mUpdatePosDistance_s, "UpdatePosDistance");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai

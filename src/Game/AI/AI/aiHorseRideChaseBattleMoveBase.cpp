#include "Game/AI/AI/aiHorseRideChaseBattleMoveBase.h"

namespace uking::ai {

HorseRideChaseBattleMoveBase::HorseRideChaseBattleMoveBase(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

HorseRideChaseBattleMoveBase::~HorseRideChaseBattleMoveBase() = default;

bool HorseRideChaseBattleMoveBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void HorseRideChaseBattleMoveBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void HorseRideChaseBattleMoveBase::leave_() {
    ksys::act::ai::Ai::leave_();
}

void HorseRideChaseBattleMoveBase::loadParams_() {
    getStaticParam(&mSlowDownDist_s, "SlowDownDist");
    getStaticParam(&mSpeedUpDist_s, "SpeedUpDist");
    getStaticParam(&mBaseDist_s, "BaseDist");
    getStaticParam(&mOutDist_s, "OutDist");
}

}  // namespace uking::ai

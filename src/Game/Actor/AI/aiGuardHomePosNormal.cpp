#include "Game/Actor/AI/aiGuardHomePosNormal.h"

namespace uking::ai {

GuardHomePosNormal::GuardHomePosNormal(const InitArg& arg) : LandHumEnemyNormal(arg) {}

GuardHomePosNormal::~GuardHomePosNormal() = default;

bool GuardHomePosNormal::init_(sead::Heap* heap) {
    return LandHumEnemyNormal::init_(heap);
}

void GuardHomePosNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    LandHumEnemyNormal::enter_(params);
}

void GuardHomePosNormal::leave_() {
    LandHumEnemyNormal::leave_();
}

void GuardHomePosNormal::loadParams_() {
    LandHumEnemyNormal::loadParams_();
}

}  // namespace uking::ai

#include "Game/AI/Action/actionEatForSunazarashiSPC.h"

namespace uking::action {

EatForSunazarashiSPC::EatForSunazarashiSPC(const InitArg& arg) : HorseEatAction(arg) {}

EatForSunazarashiSPC::~EatForSunazarashiSPC() = default;

bool EatForSunazarashiSPC::init_(sead::Heap* heap) {
    return HorseEatAction::init_(heap);
}

void EatForSunazarashiSPC::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseEatAction::enter_(params);
}

void EatForSunazarashiSPC::leave_() {
    HorseEatAction::leave_();
}

void EatForSunazarashiSPC::loadParams_() {
    HorseEatAction::loadParams_();
    getAITreeVariable(&mPrevEatActorName_a, "PrevEatActorName");
}

void EatForSunazarashiSPC::calc_() {
    HorseEatAction::calc_();
}

}  // namespace uking::action

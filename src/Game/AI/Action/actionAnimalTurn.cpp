#include "Game/AI/Action/actionAnimalTurn.h"

namespace uking::action {

AnimalTurn::AnimalTurn(const InitArg& arg) : PlayASForAnimalUnit(arg) {}

AnimalTurn::~AnimalTurn() = default;

bool AnimalTurn::init_(sead::Heap* heap) {
    return PlayASForAnimalUnit::init_(heap);
}

void AnimalTurn::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayASForAnimalUnit::enter_(params);
}

void AnimalTurn::leave_() {
    PlayASForAnimalUnit::leave_();
}

void AnimalTurn::loadParams_() {
    PlayASForAnimalUnit::loadParams_();
    getStaticParam(&mAnimPlayRate_s, "AnimPlayRate");
    getStaticParam(&mFinishAngleRange_s, "FinishAngleRange");
    getStaticParam(&mRotateAngleMax_s, "RotateAngleMax");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void AnimalTurn::calc_() {
    PlayASForAnimalUnit::calc_();
}

}  // namespace uking::action

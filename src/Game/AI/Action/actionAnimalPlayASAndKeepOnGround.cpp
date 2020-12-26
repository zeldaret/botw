#include "Game/AI/Action/actionAnimalPlayASAndKeepOnGround.h"

namespace uking::action {

AnimalPlayASAndKeepOnGround::AnimalPlayASAndKeepOnGround(const InitArg& arg)
    : PlayASForAnimalUnit(arg) {}

AnimalPlayASAndKeepOnGround::~AnimalPlayASAndKeepOnGround() = default;

bool AnimalPlayASAndKeepOnGround::init_(sead::Heap* heap) {
    return PlayASForAnimalUnit::init_(heap);
}

void AnimalPlayASAndKeepOnGround::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayASForAnimalUnit::enter_(params);
}

void AnimalPlayASAndKeepOnGround::leave_() {
    PlayASForAnimalUnit::leave_();
}

void AnimalPlayASAndKeepOnGround::loadParams_() {
    PlayASForAnimalUnit::loadParams_();
    getStaticParam(&mDownImpulseScale_s, "DownImpulseScale");
    getStaticParam(&mIsUseDownImpulse_s, "IsUseDownImpulse");
    getAITreeVariable(&mIsChangeableStateFreeFall_a, "IsChangeableStateFreeFall");
}

void AnimalPlayASAndKeepOnGround::calc_() {
    PlayASForAnimalUnit::calc_();
}

}  // namespace uking::action

#include "Game/AI/Action/actionAirOctaFloatBase.h"

namespace uking::action {

AirOctaFloatBase::AirOctaFloatBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

AirOctaFloatBase::~AirOctaFloatBase() = default;

bool AirOctaFloatBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void AirOctaFloatBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void AirOctaFloatBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void AirOctaFloatBase::loadParams_() {
    getStaticParam(&mAmplitude_s, "Amplitude");
    getStaticParam(&mGoalDistance_s, "GoalDistance");
    getStaticParam(&mGoalInSuccessEnd_s, "GoalInSuccessEnd");
    getAITreeVariable(&mAirOctaDataMgr_a, "AirOctaDataMgr");
}

void AirOctaFloatBase::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

#include "Game/Actor/Action/actionAirOctaMoveBase.h"

namespace uking::action {

AirOctaMoveBase::AirOctaMoveBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

AirOctaMoveBase::~AirOctaMoveBase() = default;

bool AirOctaMoveBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void AirOctaMoveBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void AirOctaMoveBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void AirOctaMoveBase::loadParams_() {
    getStaticParam(&mAmplitude_s, "Amplitude");
    getStaticParam(&mGoalDistance_s, "GoalDistance");
    getStaticParam(&mGoalInSuccessEnd_s, "GoalInSuccessEnd");
    getAITreeVariable(&mAirOctaDataMgr_a, "AirOctaDataMgr");
}

void AirOctaMoveBase::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

#include "Game/Actor/Action/actionAirOctaFloat.h"

namespace uking::action {

AirOctaFloat::AirOctaFloat(const InitArg& arg) : AirOctaMoveBase(arg) {}

AirOctaFloat::~AirOctaFloat() = default;

bool AirOctaFloat::init_(sead::Heap* heap) {
    return AirOctaMoveBase::init_(heap);
}

void AirOctaFloat::enter_(ksys::act::ai::InlineParamPack* params) {
    AirOctaMoveBase::enter_(params);
}

void AirOctaFloat::leave_() {
    AirOctaMoveBase::leave_();
}

void AirOctaFloat::loadParams_() {
    AirOctaMoveBase::loadParams_();
}

void AirOctaFloat::calc_() {
    AirOctaMoveBase::calc_();
}

}  // namespace uking::action

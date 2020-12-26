#include "Game/AI/Action/actionAirOctaFloat.h"

namespace uking::action {

AirOctaFloat::AirOctaFloat(const InitArg& arg) : AirOctaFloatBase(arg) {}

AirOctaFloat::~AirOctaFloat() = default;

bool AirOctaFloat::init_(sead::Heap* heap) {
    return AirOctaFloatBase::init_(heap);
}

void AirOctaFloat::enter_(ksys::act::ai::InlineParamPack* params) {
    AirOctaFloatBase::enter_(params);
}

void AirOctaFloat::leave_() {
    AirOctaFloatBase::leave_();
}

void AirOctaFloat::loadParams_() {
    AirOctaFloatBase::loadParams_();
}

void AirOctaFloat::calc_() {
    AirOctaFloatBase::calc_();
}

}  // namespace uking::action

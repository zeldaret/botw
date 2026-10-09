#include "Game/Actor/Action/actionElectricParalysis.h"

namespace uking::action {

ElectricParalysis::ElectricParalysis(const InitArg& arg) : StopBase(arg) {}

ElectricParalysis::~ElectricParalysis() = default;

bool ElectricParalysis::init_(sead::Heap* heap) {
    return StopBase::init_(heap);
}

void ElectricParalysis::enter_(ksys::act::ai::InlineParamPack* params) {
    StopBase::enter_(params);
}

void ElectricParalysis::leave_() {
    StopBase::leave_();
}

void ElectricParalysis::loadParams_() {
    StopBase::loadParams_();
    getStaticParam(&mASName_s, "ASName");
}

void ElectricParalysis::calc_() {
    StopBase::calc_();
}

}  // namespace uking::action

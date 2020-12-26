#include "Game/AI/Action/actionSetInstantTemperture.h"

namespace uking::action {

SetInstantTemperture::SetInstantTemperture(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SetInstantTemperture::~SetInstantTemperture() = default;

bool SetInstantTemperture::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SetInstantTemperture::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SetInstantTemperture::leave_() {
    ksys::act::ai::Action::leave_();
}

void SetInstantTemperture::loadParams_() {}

void SetInstantTemperture::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

#include "Game/AI/Action/actionForkGravityScaleChange.h"

namespace uking::action {

ForkGravityScaleChange::ForkGravityScaleChange(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkGravityScaleChange::~ForkGravityScaleChange() = default;

bool ForkGravityScaleChange::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkGravityScaleChange::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkGravityScaleChange::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkGravityScaleChange::loadParams_() {
    getStaticParam(&mScale_s, "Scale");
}

void ForkGravityScaleChange::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

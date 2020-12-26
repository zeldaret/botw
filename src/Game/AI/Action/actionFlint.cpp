#include "Game/AI/Action/actionFlint.h"

namespace uking::action {

Flint::Flint(const InitArg& arg) : ksys::act::ai::Action(arg) {}

Flint::~Flint() = default;

bool Flint::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void Flint::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void Flint::leave_() {
    ksys::act::ai::Action::leave_();
}

void Flint::loadParams_() {
    getStaticParam(&mRadius_s, "Radius");
    getStaticParam(&mLife_s, "Life");
    getStaticParam(&mSetDelete_s, "SetDelete");
}

void Flint::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

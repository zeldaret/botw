#include "Game/AI/Action/actionBasicSignalChangeDamping.h"

namespace uking::action {

BasicSignalChangeDamping::BasicSignalChangeDamping(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

BasicSignalChangeDamping::~BasicSignalChangeDamping() = default;

bool BasicSignalChangeDamping::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void BasicSignalChangeDamping::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void BasicSignalChangeDamping::leave_() {
    ksys::act::ai::Action::leave_();
}

void BasicSignalChangeDamping::loadParams_() {
    getStaticParam(&mLinearDamping_s, "LinearDamping");
    getStaticParam(&mAngularDamping_s, "AngularDamping");
}

void BasicSignalChangeDamping::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

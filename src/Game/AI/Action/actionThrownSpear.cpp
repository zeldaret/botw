#include "Game/AI/Action/actionThrownSpear.h"

namespace uking::action {

ThrownSpear::ThrownSpear(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ThrownSpear::~ThrownSpear() = default;

void ThrownSpear::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ThrownSpear::leave_() {
    ksys::act::ai::Action::leave_();
}

void ThrownSpear::loadParams_() {
    getStaticParam(&mRotSpeedZ_s, "RotSpeedZ");
}

void ThrownSpear::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

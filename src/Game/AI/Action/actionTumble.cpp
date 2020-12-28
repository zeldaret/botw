#include "Game/AI/Action/actionTumble.h"

namespace uking::action {

Tumble::Tumble(const InitArg& arg) : ksys::act::ai::Action(arg) {}

Tumble::~Tumble() = default;

void Tumble::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void Tumble::leave_() {
    ksys::act::ai::Action::leave_();
}

void Tumble::loadParams_() {}

void Tumble::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

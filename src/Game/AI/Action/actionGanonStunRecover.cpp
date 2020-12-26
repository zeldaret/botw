#include "Game/AI/Action/actionGanonStunRecover.h"

namespace uking::action {

GanonStunRecover::GanonStunRecover(const InitArg& arg) : ksys::act::ai::Action(arg) {}

GanonStunRecover::~GanonStunRecover() = default;

bool GanonStunRecover::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void GanonStunRecover::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void GanonStunRecover::leave_() {
    ksys::act::ai::Action::leave_();
}

void GanonStunRecover::loadParams_() {}

void GanonStunRecover::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

#include "Game/AI/Action/actionSSMagneStickAcceptorReject.h"

namespace uking::action {

SSMagneStickAcceptorReject::SSMagneStickAcceptorReject(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

SSMagneStickAcceptorReject::~SSMagneStickAcceptorReject() = default;

bool SSMagneStickAcceptorReject::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SSMagneStickAcceptorReject::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SSMagneStickAcceptorReject::leave_() {
    ksys::act::ai::Action::leave_();
}

void SSMagneStickAcceptorReject::loadParams_() {}

void SSMagneStickAcceptorReject::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

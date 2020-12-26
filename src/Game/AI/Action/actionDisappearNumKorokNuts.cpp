#include "Game/AI/Action/actionDisappearNumKorokNuts.h"

namespace uking::action {

DisappearNumKorokNuts::DisappearNumKorokNuts(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DisappearNumKorokNuts::~DisappearNumKorokNuts() = default;

bool DisappearNumKorokNuts::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DisappearNumKorokNuts::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void DisappearNumKorokNuts::leave_() {
    ksys::act::ai::Action::leave_();
}

void DisappearNumKorokNuts::loadParams_() {}

void DisappearNumKorokNuts::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

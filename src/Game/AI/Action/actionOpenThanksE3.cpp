#include "Game/AI/Action/actionOpenThanksE3.h"

namespace uking::action {

OpenThanksE3::OpenThanksE3(const InitArg& arg) : ksys::act::ai::Action(arg) {}

OpenThanksE3::~OpenThanksE3() = default;

bool OpenThanksE3::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void OpenThanksE3::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void OpenThanksE3::leave_() {
    ksys::act::ai::Action::leave_();
}

void OpenThanksE3::loadParams_() {}

void OpenThanksE3::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

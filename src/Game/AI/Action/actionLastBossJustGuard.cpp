#include "Game/AI/Action/actionLastBossJustGuard.h"

namespace uking::action {

LastBossJustGuard::LastBossJustGuard(const InitArg& arg) : ksys::act::ai::Action(arg) {}

LastBossJustGuard::~LastBossJustGuard() = default;

bool LastBossJustGuard::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void LastBossJustGuard::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void LastBossJustGuard::leave_() {
    ksys::act::ai::Action::leave_();
}

void LastBossJustGuard::loadParams_() {}

void LastBossJustGuard::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

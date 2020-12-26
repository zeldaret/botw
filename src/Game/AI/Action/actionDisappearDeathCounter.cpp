#include "Game/AI/Action/actionDisappearDeathCounter.h"

namespace uking::action {

DisappearDeathCounter::DisappearDeathCounter(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DisappearDeathCounter::~DisappearDeathCounter() = default;

bool DisappearDeathCounter::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DisappearDeathCounter::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void DisappearDeathCounter::leave_() {
    ksys::act::ai::Action::leave_();
}

void DisappearDeathCounter::loadParams_() {}

void DisappearDeathCounter::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

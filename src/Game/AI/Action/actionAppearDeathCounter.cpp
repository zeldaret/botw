#include "Game/AI/Action/actionAppearDeathCounter.h"

namespace uking::action {

AppearDeathCounter::AppearDeathCounter(const InitArg& arg) : ksys::act::ai::Action(arg) {}

AppearDeathCounter::~AppearDeathCounter() = default;

bool AppearDeathCounter::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void AppearDeathCounter::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void AppearDeathCounter::leave_() {
    ksys::act::ai::Action::leave_();
}

void AppearDeathCounter::loadParams_() {}

void AppearDeathCounter::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

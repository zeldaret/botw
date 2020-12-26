#include "Game/AI/Action/actionMotorcycleWaitUntilFellOver.h"

namespace uking::action {

MotorcycleWaitUntilFellOver::MotorcycleWaitUntilFellOver(const InitArg& arg)
    : MotorcycleWait(arg) {}

MotorcycleWaitUntilFellOver::~MotorcycleWaitUntilFellOver() = default;

bool MotorcycleWaitUntilFellOver::init_(sead::Heap* heap) {
    return MotorcycleWait::init_(heap);
}

void MotorcycleWaitUntilFellOver::enter_(ksys::act::ai::InlineParamPack* params) {
    MotorcycleWait::enter_(params);
}

void MotorcycleWaitUntilFellOver::leave_() {
    MotorcycleWait::leave_();
}

void MotorcycleWaitUntilFellOver::loadParams_() {
    MotorcycleWait::loadParams_();
}

void MotorcycleWaitUntilFellOver::calc_() {
    MotorcycleWait::calc_();
}

}  // namespace uking::action

#include "Game/AI/Action/actionIncreasePlayerMaxHeart.h"

namespace uking::action {

IncreasePlayerMaxHeart::IncreasePlayerMaxHeart(const InitArg& arg) : ksys::act::ai::Action(arg) {}

IncreasePlayerMaxHeart::~IncreasePlayerMaxHeart() = default;

bool IncreasePlayerMaxHeart::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void IncreasePlayerMaxHeart::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void IncreasePlayerMaxHeart::leave_() {
    ksys::act::ai::Action::leave_();
}

void IncreasePlayerMaxHeart::loadParams_() {
    getDynamicParam(&mValue_d, "Value");
    getDynamicParam(&mIsMoveCenter_d, "IsMoveCenter");
}

void IncreasePlayerMaxHeart::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

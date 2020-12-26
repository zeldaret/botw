#include "Game/AI/Action/actionIchigekiHeartDecrease.h"

namespace uking::action {

IchigekiHeartDecrease::IchigekiHeartDecrease(const InitArg& arg) : ksys::act::ai::Action(arg) {}

IchigekiHeartDecrease::~IchigekiHeartDecrease() = default;

bool IchigekiHeartDecrease::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void IchigekiHeartDecrease::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void IchigekiHeartDecrease::leave_() {
    ksys::act::ai::Action::leave_();
}

void IchigekiHeartDecrease::loadParams_() {
    getDynamicParam(&mUseFrame_d, "UseFrame");
    getDynamicParam(&mIsUseConstSpeed_d, "IsUseConstSpeed");
}

void IchigekiHeartDecrease::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

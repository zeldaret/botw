#include "Game/AI/Action/actionIchigekiHeartUiOpen.h"

namespace uking::action {

IchigekiHeartUiOpen::IchigekiHeartUiOpen(const InitArg& arg) : ksys::act::ai::Action(arg) {}

IchigekiHeartUiOpen::~IchigekiHeartUiOpen() = default;

bool IchigekiHeartUiOpen::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void IchigekiHeartUiOpen::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void IchigekiHeartUiOpen::leave_() {
    ksys::act::ai::Action::leave_();
}

void IchigekiHeartUiOpen::loadParams_() {}

void IchigekiHeartUiOpen::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

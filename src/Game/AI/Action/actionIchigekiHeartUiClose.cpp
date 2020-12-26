#include "Game/AI/Action/actionIchigekiHeartUiClose.h"

namespace uking::action {

IchigekiHeartUiClose::IchigekiHeartUiClose(const InitArg& arg) : ksys::act::ai::Action(arg) {}

IchigekiHeartUiClose::~IchigekiHeartUiClose() = default;

bool IchigekiHeartUiClose::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void IchigekiHeartUiClose::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void IchigekiHeartUiClose::leave_() {
    ksys::act::ai::Action::leave_();
}

void IchigekiHeartUiClose::loadParams_() {}

void IchigekiHeartUiClose::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

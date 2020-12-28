#include "Game/AI/Action/actionIchigekiHeartUiClose.h"

namespace uking::action {

IchigekiHeartUiClose::IchigekiHeartUiClose(const InitArg& arg) : ksys::act::ai::Action(arg) {}

IchigekiHeartUiClose::~IchigekiHeartUiClose() = default;

bool IchigekiHeartUiClose::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void IchigekiHeartUiClose::loadParams_() {}

}  // namespace uking::action

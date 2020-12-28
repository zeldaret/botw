#include "Game/AI/Action/actionIchigekiHeartUiOpen.h"

namespace uking::action {

IchigekiHeartUiOpen::IchigekiHeartUiOpen(const InitArg& arg) : ksys::act::ai::Action(arg) {}

IchigekiHeartUiOpen::~IchigekiHeartUiOpen() = default;

bool IchigekiHeartUiOpen::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void IchigekiHeartUiOpen::loadParams_() {}

}  // namespace uking::action

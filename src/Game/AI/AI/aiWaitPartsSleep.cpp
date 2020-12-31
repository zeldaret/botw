#include "Game/AI/AI/aiWaitPartsSleep.h"

namespace uking::ai {

WaitPartsSleep::WaitPartsSleep(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WaitPartsSleep::~WaitPartsSleep() = default;

bool WaitPartsSleep::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void WaitPartsSleep::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void WaitPartsSleep::leave_() {
    ksys::act::ai::Ai::leave_();
}

void WaitPartsSleep::loadParams_() {}

}  // namespace uking::ai

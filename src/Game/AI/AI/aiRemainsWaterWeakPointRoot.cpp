#include "Game/AI/AI/aiRemainsWaterWeakPointRoot.h"

namespace uking::ai {

RemainsWaterWeakPointRoot::RemainsWaterWeakPointRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

RemainsWaterWeakPointRoot::~RemainsWaterWeakPointRoot() = default;

bool RemainsWaterWeakPointRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void RemainsWaterWeakPointRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void RemainsWaterWeakPointRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void RemainsWaterWeakPointRoot::loadParams_() {}

}  // namespace uking::ai

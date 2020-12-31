#include "Game/AI/AI/aiIbutsuWaterFallRoot.h"

namespace uking::ai {

IbutsuWaterFallRoot::IbutsuWaterFallRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

IbutsuWaterFallRoot::~IbutsuWaterFallRoot() = default;

bool IbutsuWaterFallRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void IbutsuWaterFallRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void IbutsuWaterFallRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void IbutsuWaterFallRoot::loadParams_() {}

}  // namespace uking::ai

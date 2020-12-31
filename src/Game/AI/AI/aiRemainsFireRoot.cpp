#include "Game/AI/AI/aiRemainsFireRoot.h"

namespace uking::ai {

RemainsFireRoot::RemainsFireRoot(const InitArg& arg) : RemainsRoot(arg) {}

RemainsFireRoot::~RemainsFireRoot() = default;

bool RemainsFireRoot::init_(sead::Heap* heap) {
    return RemainsRoot::init_(heap);
}

void RemainsFireRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    RemainsRoot::enter_(params);
}

void RemainsFireRoot::leave_() {
    RemainsRoot::leave_();
}

void RemainsFireRoot::loadParams_() {
    RemainsRoot::loadParams_();
    getStaticParam(&mTargetBoneName_s, "TargetBoneName");
}

}  // namespace uking::ai

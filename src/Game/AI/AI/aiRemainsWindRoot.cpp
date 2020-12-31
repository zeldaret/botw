#include "Game/AI/AI/aiRemainsWindRoot.h"

namespace uking::ai {

RemainsWindRoot::RemainsWindRoot(const InitArg& arg) : RemainsRoot(arg) {}

RemainsWindRoot::~RemainsWindRoot() = default;

bool RemainsWindRoot::init_(sead::Heap* heap) {
    return RemainsRoot::init_(heap);
}

void RemainsWindRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    RemainsRoot::enter_(params);
}

void RemainsWindRoot::leave_() {
    RemainsRoot::leave_();
}

void RemainsWindRoot::loadParams_() {
    RemainsRoot::loadParams_();
}

}  // namespace uking::ai

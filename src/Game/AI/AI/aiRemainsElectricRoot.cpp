#include "Game/AI/AI/aiRemainsElectricRoot.h"

namespace uking::ai {

RemainsElectricRoot::RemainsElectricRoot(const InitArg& arg) : RemainsRoot(arg) {}

RemainsElectricRoot::~RemainsElectricRoot() = default;

bool RemainsElectricRoot::init_(sead::Heap* heap) {
    return RemainsRoot::init_(heap);
}

void RemainsElectricRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    RemainsRoot::enter_(params);
}

void RemainsElectricRoot::leave_() {
    RemainsRoot::leave_();
}

void RemainsElectricRoot::loadParams_() {
    RemainsRoot::loadParams_();
}

}  // namespace uking::ai

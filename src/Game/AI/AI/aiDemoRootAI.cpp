#include "Game/AI/AI/aiDemoRootAI.h"

namespace uking::ai {

DemoRootAI::DemoRootAI(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

DemoRootAI::~DemoRootAI() = default;

bool DemoRootAI::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void DemoRootAI::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void DemoRootAI::leave_() {
    ksys::act::ai::Ai::leave_();
}

void DemoRootAI::loadParams_() {}

}  // namespace uking::ai

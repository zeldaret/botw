#include "KingSystem/ActorSystem/aiDemoRootAI.h"

namespace ksys::act::ai {

DemoRootAI::DemoRootAI(const InitArg& arg) : Ai(arg) {}

DemoRootAI::~DemoRootAI() = default;

bool DemoRootAI::init_(sead::Heap* heap) {
    return Ai::init_(heap);
}

void DemoRootAI::enter_(InlineParamPack* params) {
    Ai::enter_(params);
}

void DemoRootAI::leave_() {
    Ai::leave_();
}

void DemoRootAI::loadParams_() {}

}  // namespace ksys::act::ai

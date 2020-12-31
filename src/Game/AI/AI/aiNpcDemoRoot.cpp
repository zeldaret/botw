#include "Game/AI/AI/aiNpcDemoRoot.h"

namespace uking::ai {

NpcDemoRoot::NpcDemoRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

NpcDemoRoot::~NpcDemoRoot() = default;

bool NpcDemoRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void NpcDemoRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void NpcDemoRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void NpcDemoRoot::loadParams_() {}

}  // namespace uking::ai

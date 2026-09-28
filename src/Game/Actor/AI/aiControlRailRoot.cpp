#include "Game/Actor/AI/aiControlRailRoot.h"

namespace uking::ai {

ControlRailRoot::ControlRailRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ControlRailRoot::~ControlRailRoot() = default;

bool ControlRailRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void ControlRailRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void ControlRailRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void ControlRailRoot::loadParams_() {}

}  // namespace uking::ai

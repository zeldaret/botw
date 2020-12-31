#include "Game/AI/AI/aiTerminalEnduranceWarpRoot.h"

namespace uking::ai {

TerminalEnduranceWarpRoot::TerminalEnduranceWarpRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

TerminalEnduranceWarpRoot::~TerminalEnduranceWarpRoot() = default;

bool TerminalEnduranceWarpRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void TerminalEnduranceWarpRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void TerminalEnduranceWarpRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void TerminalEnduranceWarpRoot::loadParams_() {}

}  // namespace uking::ai

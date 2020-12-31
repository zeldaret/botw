#include "Game/AI/AI/aiGolemRWeakPointRoot.h"

namespace uking::ai {

GolemRWeakPointRoot::GolemRWeakPointRoot(const InitArg& arg) : GolemWeakPointRoot(arg) {}

GolemRWeakPointRoot::~GolemRWeakPointRoot() = default;

bool GolemRWeakPointRoot::init_(sead::Heap* heap) {
    return GolemWeakPointRoot::init_(heap);
}

void GolemRWeakPointRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    GolemWeakPointRoot::enter_(params);
}

void GolemRWeakPointRoot::leave_() {
    GolemWeakPointRoot::leave_();
}

void GolemRWeakPointRoot::loadParams_() {
    GolemWeakPointRoot::loadParams_();
}

}  // namespace uking::ai

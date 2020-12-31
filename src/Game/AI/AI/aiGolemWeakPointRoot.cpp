#include "Game/AI/AI/aiGolemWeakPointRoot.h"

namespace uking::ai {

GolemWeakPointRoot::GolemWeakPointRoot(const InitArg& arg) : WeakPointRoot(arg) {}

GolemWeakPointRoot::~GolemWeakPointRoot() = default;

bool GolemWeakPointRoot::init_(sead::Heap* heap) {
    return WeakPointRoot::init_(heap);
}

void GolemWeakPointRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    WeakPointRoot::enter_(params);
}

void GolemWeakPointRoot::leave_() {
    WeakPointRoot::leave_();
}

void GolemWeakPointRoot::loadParams_() {
    WeakPointRoot::loadParams_();
}

}  // namespace uking::ai

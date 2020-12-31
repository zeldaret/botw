#include "Game/AI/AI/aiWarpSafeTagRoot.h"

namespace uking::ai {

WarpSafeTagRoot::WarpSafeTagRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WarpSafeTagRoot::~WarpSafeTagRoot() = default;

bool WarpSafeTagRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void WarpSafeTagRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void WarpSafeTagRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void WarpSafeTagRoot::loadParams_() {}

}  // namespace uking::ai

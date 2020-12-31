#include "Game/AI/AI/aiWarpTagRoot.h"

namespace uking::ai {

WarpTagRoot::WarpTagRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WarpTagRoot::~WarpTagRoot() = default;

bool WarpTagRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void WarpTagRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void WarpTagRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void WarpTagRoot::loadParams_() {}

}  // namespace uking::ai

#include "Game/AI/AI/aiKeeseHangOnCeil.h"

namespace uking::ai {

KeeseHangOnCeil::KeeseHangOnCeil(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

KeeseHangOnCeil::~KeeseHangOnCeil() = default;

bool KeeseHangOnCeil::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void KeeseHangOnCeil::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void KeeseHangOnCeil::leave_() {
    ksys::act::ai::Ai::leave_();
}

void KeeseHangOnCeil::loadParams_() {}

}  // namespace uking::ai

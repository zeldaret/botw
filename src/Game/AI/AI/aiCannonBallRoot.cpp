#include "Game/AI/AI/aiCannonBallRoot.h"

namespace uking::ai {

CannonBallRoot::CannonBallRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

CannonBallRoot::~CannonBallRoot() = default;

bool CannonBallRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void CannonBallRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void CannonBallRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void CannonBallRoot::loadParams_() {}

}  // namespace uking::ai

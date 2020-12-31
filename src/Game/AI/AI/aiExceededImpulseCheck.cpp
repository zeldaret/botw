#include "Game/AI/AI/aiExceededImpulseCheck.h"

namespace uking::ai {

ExceededImpulseCheck::ExceededImpulseCheck(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ExceededImpulseCheck::~ExceededImpulseCheck() = default;

bool ExceededImpulseCheck::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void ExceededImpulseCheck::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void ExceededImpulseCheck::leave_() {
    ksys::act::ai::Ai::leave_();
}

void ExceededImpulseCheck::loadParams_() {}

}  // namespace uking::ai

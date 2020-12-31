#include "Game/AI/AI/aiExplodeCheck.h"

namespace uking::ai {

ExplodeCheck::ExplodeCheck(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ExplodeCheck::~ExplodeCheck() = default;

bool ExplodeCheck::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void ExplodeCheck::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void ExplodeCheck::leave_() {
    ksys::act::ai::Ai::leave_();
}

void ExplodeCheck::loadParams_() {}

}  // namespace uking::ai

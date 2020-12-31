#include "Game/AI/AI/aiInvincibleHiddenOctarock.h"

namespace uking::ai {

InvincibleHiddenOctarock::InvincibleHiddenOctarock(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

InvincibleHiddenOctarock::~InvincibleHiddenOctarock() = default;

bool InvincibleHiddenOctarock::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void InvincibleHiddenOctarock::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void InvincibleHiddenOctarock::leave_() {
    ksys::act::ai::Ai::leave_();
}

void InvincibleHiddenOctarock::loadParams_() {}

}  // namespace uking::ai

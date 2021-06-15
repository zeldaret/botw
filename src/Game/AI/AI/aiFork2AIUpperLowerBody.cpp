#include "Game/AI/AI/aiFork2AIUpperLowerBody.h"

namespace uking::ai {

Fork2AIUpperLowerBody::Fork2AIUpperLowerBody(const InitArg& arg) : ForkAI(arg) {}

Fork2AIUpperLowerBody::~Fork2AIUpperLowerBody() = default;

bool Fork2AIUpperLowerBody::init_(sead::Heap* heap) {
    return ForkAI::init_(heap);
}

void Fork2AIUpperLowerBody::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkAI::enter_(params);
}

void Fork2AIUpperLowerBody::calc_() {}

void Fork2AIUpperLowerBody::leave_() {
    ForkAI::leave_();
}

void Fork2AIUpperLowerBody::loadParams_() {}

}  // namespace uking::ai

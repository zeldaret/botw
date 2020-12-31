#include "Game/AI/AI/aiRegistedActorNumTwoSelectBase.h"

namespace uking::ai {

RegistedActorNumTwoSelectBase::RegistedActorNumTwoSelectBase(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

RegistedActorNumTwoSelectBase::~RegistedActorNumTwoSelectBase() = default;

bool RegistedActorNumTwoSelectBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void RegistedActorNumTwoSelectBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void RegistedActorNumTwoSelectBase::leave_() {
    ksys::act::ai::Ai::leave_();
}

void RegistedActorNumTwoSelectBase::loadParams_() {
    getAITreeVariable(&mRegistedActorUnit_a, "RegistedActorUnit");
}

}  // namespace uking::ai

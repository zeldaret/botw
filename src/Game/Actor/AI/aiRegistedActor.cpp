#include "Game/Actor/AI/aiRegistedActor.h"

namespace uking::ai {

RegistedActor::RegistedActor(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

RegistedActor::~RegistedActor() = default;

bool RegistedActor::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void RegistedActor::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void RegistedActor::leave_() {
    ksys::act::ai::Ai::leave_();
}

void RegistedActor::loadParams_() {
    getAITreeVariable(&mRegistedActorUnit_a, "RegistedActorUnit");
}

}  // namespace uking::ai

#include "Game/Actor/AI/aiRegistedActorNumTwoSelect.h"

namespace uking::ai {

RegistedActorNumTwoSelect::RegistedActorNumTwoSelect(const InitArg& arg) : RegistedActor(arg) {}

RegistedActorNumTwoSelect::~RegistedActorNumTwoSelect() = default;

bool RegistedActorNumTwoSelect::init_(sead::Heap* heap) {
    return RegistedActor::init_(heap);
}

void RegistedActorNumTwoSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    RegistedActor::enter_(params);
}

void RegistedActorNumTwoSelect::leave_() {
    RegistedActor::leave_();
}

void RegistedActorNumTwoSelect::loadParams_() {
    RegistedActor::loadParams_();
    getStaticParam(&mNum_s, "Num");
}

}  // namespace uking::ai

#include "Game/AI/AI/aiKokkoAngry.h"

namespace uking::ai {

KokkoAngry::KokkoAngry(const InitArg& arg) : CreateActorWithTarget(arg) {}

KokkoAngry::~KokkoAngry() = default;

bool KokkoAngry::init_(sead::Heap* heap) {
    return CreateActorWithTarget::init_(heap);
}

void KokkoAngry::enter_(ksys::act::ai::InlineParamPack* params) {
    CreateActorWithTarget::enter_(params);
}

void KokkoAngry::leave_() {
    CreateActorWithTarget::leave_();
}

void KokkoAngry::loadParams_() {
    CreateActorWithTarget::loadParams_();
}

}  // namespace uking::ai

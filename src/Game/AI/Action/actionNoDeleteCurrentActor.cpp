#include "Game/AI/Action/actionNoDeleteCurrentActor.h"

namespace uking::action {

NoDeleteCurrentActor::NoDeleteCurrentActor(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NoDeleteCurrentActor::~NoDeleteCurrentActor() = default;

bool NoDeleteCurrentActor::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void NoDeleteCurrentActor::loadParams_() {}

}  // namespace uking::action

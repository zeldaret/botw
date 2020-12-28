#include "Game/AI/Action/actionSetTreasure.h"

namespace uking::action {

SetTreasure::SetTreasure(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SetTreasure::~SetTreasure() = default;

bool SetTreasure::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SetTreasure::loadParams_() {
    getDynamicParam(&mActorName_d, "ActorName");
    getAITreeVariable(&mDropActorName_a, "DropActorName");
}

}  // namespace uking::action

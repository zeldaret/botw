#include "Game/AI/Action/actionSetHorseFamiliarityPassedFlag.h"

namespace uking::action {

SetHorseFamiliarityPassedFlag::SetHorseFamiliarityPassedFlag(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

SetHorseFamiliarityPassedFlag::~SetHorseFamiliarityPassedFlag() = default;

bool SetHorseFamiliarityPassedFlag::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SetHorseFamiliarityPassedFlag::loadParams_() {}

}  // namespace uking::action

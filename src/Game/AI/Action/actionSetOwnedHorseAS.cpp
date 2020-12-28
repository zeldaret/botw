#include "Game/AI/Action/actionSetOwnedHorseAS.h"

namespace uking::action {

SetOwnedHorseAS::SetOwnedHorseAS(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SetOwnedHorseAS::~SetOwnedHorseAS() = default;

bool SetOwnedHorseAS::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SetOwnedHorseAS::loadParams_() {
    getDynamicParam(&mASName_d, "ASName");
}

}  // namespace uking::action

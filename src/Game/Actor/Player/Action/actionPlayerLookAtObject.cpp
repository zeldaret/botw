#include "Game/Actor/Player/Action/actionPlayerLookAtObject.h"

namespace uking::action {

PlayerLookAtObject::PlayerLookAtObject(const InitArg& arg) : TurnAndLookToObjBase(arg) {}

PlayerLookAtObject::~PlayerLookAtObject() = default;

bool PlayerLookAtObject::init_(sead::Heap* heap) {
    return TurnAndLookToObjBase::init_(heap);
}

void PlayerLookAtObject::loadParams_() {
    TurnAndLookToObjBase::loadParams_();
}

}  // namespace uking::action

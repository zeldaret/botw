#include "Game/AI/Action/actionPlayerLookAtObject.h"

namespace uking::action {

PlayerLookAtObject::PlayerLookAtObject(const InitArg& arg) : LookAtObjectBase(arg) {}

PlayerLookAtObject::~PlayerLookAtObject() = default;

bool PlayerLookAtObject::init_(sead::Heap* heap) {
    return LookAtObjectBase::init_(heap);
}

void PlayerLookAtObject::loadParams_() {
    LookAtObjectBase::loadParams_();
}

}  // namespace uking::action

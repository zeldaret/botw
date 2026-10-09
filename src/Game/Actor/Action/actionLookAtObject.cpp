#include "Game/Actor/Action/actionLookAtObject.h"

namespace uking::action {

LookAtObject::LookAtObject(const InitArg& arg) : TurnAndLookToObjBase(arg) {}

LookAtObject::~LookAtObject() = default;

bool LookAtObject::init_(sead::Heap* heap) {
    return TurnAndLookToObjBase::init_(heap);
}

void LookAtObject::loadParams_() {
    TurnAndLookToObjBase::loadParams_();
}

}  // namespace uking::action

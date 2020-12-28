#include "Game/AI/Action/actionLookAtObject.h"

namespace uking::action {

LookAtObject::LookAtObject(const InitArg& arg) : LookAtObjectBase(arg) {}

LookAtObject::~LookAtObject() = default;

bool LookAtObject::init_(sead::Heap* heap) {
    return LookAtObjectBase::init_(heap);
}

void LookAtObject::loadParams_() {
    LookAtObjectBase::loadParams_();
}

}  // namespace uking::action

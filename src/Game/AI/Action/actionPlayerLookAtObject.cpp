#include "Game/AI/Action/actionPlayerLookAtObject.h"

namespace uking::action {

PlayerLookAtObject::PlayerLookAtObject(const InitArg& arg) : LookAtObjectBase(arg) {}

PlayerLookAtObject::~PlayerLookAtObject() = default;

bool PlayerLookAtObject::init_(sead::Heap* heap) {
    return LookAtObjectBase::init_(heap);
}

void PlayerLookAtObject::enter_(ksys::act::ai::InlineParamPack* params) {
    LookAtObjectBase::enter_(params);
}

void PlayerLookAtObject::leave_() {
    LookAtObjectBase::leave_();
}

void PlayerLookAtObject::loadParams_() {
    LookAtObjectBase::loadParams_();
}

void PlayerLookAtObject::calc_() {
    LookAtObjectBase::calc_();
}

}  // namespace uking::action

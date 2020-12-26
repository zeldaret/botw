#include "Game/AI/Action/actionLookAtObject.h"

namespace uking::action {

LookAtObject::LookAtObject(const InitArg& arg) : LookAtObjectBase(arg) {}

LookAtObject::~LookAtObject() = default;

bool LookAtObject::init_(sead::Heap* heap) {
    return LookAtObjectBase::init_(heap);
}

void LookAtObject::enter_(ksys::act::ai::InlineParamPack* params) {
    LookAtObjectBase::enter_(params);
}

void LookAtObject::leave_() {
    LookAtObjectBase::leave_();
}

void LookAtObject::loadParams_() {
    LookAtObjectBase::loadParams_();
}

void LookAtObject::calc_() {
    LookAtObjectBase::calc_();
}

}  // namespace uking::action

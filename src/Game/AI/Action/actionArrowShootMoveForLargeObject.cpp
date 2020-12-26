#include "Game/AI/Action/actionArrowShootMoveForLargeObject.h"

namespace uking::action {

ArrowShootMoveForLargeObject::ArrowShootMoveForLargeObject(const InitArg& arg)
    : ArrowShootMove(arg) {}

ArrowShootMoveForLargeObject::~ArrowShootMoveForLargeObject() = default;

bool ArrowShootMoveForLargeObject::init_(sead::Heap* heap) {
    return ArrowShootMove::init_(heap);
}

void ArrowShootMoveForLargeObject::enter_(ksys::act::ai::InlineParamPack* params) {
    ArrowShootMove::enter_(params);
}

void ArrowShootMoveForLargeObject::leave_() {
    ArrowShootMove::leave_();
}

void ArrowShootMoveForLargeObject::loadParams_() {
    ArrowShootMove::loadParams_();
    getStaticParam(&mRayCastDist_s, "RayCastDist");
    getStaticParam(&mCallSEKeyAtStick_s, "CallSEKeyAtStick");
    getDynamicParam(&mIsReInitShoot_d, "IsReInitShoot");
}

void ArrowShootMoveForLargeObject::calc_() {
    ArrowShootMove::calc_();
}

}  // namespace uking::action

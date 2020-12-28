#include "Game/AI/Action/actionArrowShootMoveForLargeObject.h"

namespace uking::action {

ArrowShootMoveForLargeObject::ArrowShootMoveForLargeObject(const InitArg& arg)
    : ArrowShootMove(arg) {}

ArrowShootMoveForLargeObject::~ArrowShootMoveForLargeObject() = default;

void ArrowShootMoveForLargeObject::enter_(ksys::act::ai::InlineParamPack* params) {
    ArrowShootMove::enter_(params);
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

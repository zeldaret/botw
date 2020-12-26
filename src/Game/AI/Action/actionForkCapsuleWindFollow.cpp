#include "Game/AI/Action/actionForkCapsuleWindFollow.h"

namespace uking::action {

ForkCapsuleWindFollow::ForkCapsuleWindFollow(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkCapsuleWindFollow::~ForkCapsuleWindFollow() = default;

bool ForkCapsuleWindFollow::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkCapsuleWindFollow::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkCapsuleWindFollow::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkCapsuleWindFollow::loadParams_() {
    getStaticParam(&mRadius_s, "Radius");
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mLength_s, "Length");
    getStaticParam(&mDir_s, "Dir");
}

void ForkCapsuleWindFollow::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

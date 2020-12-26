#include "Game/AI/Action/actionGelJumpTackle.h"

namespace uking::action {

GelJumpTackle::GelJumpTackle(const InitArg& arg) : JumpTackle(arg) {}

GelJumpTackle::~GelJumpTackle() = default;

bool GelJumpTackle::init_(sead::Heap* heap) {
    return JumpTackle::init_(heap);
}

void GelJumpTackle::enter_(ksys::act::ai::InlineParamPack* params) {
    JumpTackle::enter_(params);
}

void GelJumpTackle::leave_() {
    JumpTackle::leave_();
}

void GelJumpTackle::loadParams_() {
    JumpTackle::loadParams_();
    getStaticParam(&mSubASSlot_s, "SubASSlot");
    getStaticParam(&mBodyRotSpeed_s, "BodyRotSpeed");
    getStaticParam(&mIsEnableCloth_s, "IsEnableCloth");
    getStaticParam(&mSubAS_s, "SubAS");
    getStaticParam(&mLeaveSubAS_s, "LeaveSubAS");
}

void GelJumpTackle::calc_() {
    JumpTackle::calc_();
}

}  // namespace uking::action

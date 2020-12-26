#include "Game/AI/Action/actionKokkoMoveWithJump.h"

namespace uking::action {

KokkoMoveWithJump::KokkoMoveWithJump(const InitArg& arg) : KokkoMove(arg) {}

KokkoMoveWithJump::~KokkoMoveWithJump() = default;

bool KokkoMoveWithJump::init_(sead::Heap* heap) {
    return KokkoMove::init_(heap);
}

void KokkoMoveWithJump::enter_(ksys::act::ai::InlineParamPack* params) {
    KokkoMove::enter_(params);
}

void KokkoMoveWithJump::leave_() {
    KokkoMove::leave_();
}

void KokkoMoveWithJump::loadParams_() {
    KokkoMove::loadParams_();
    getStaticParam(&mJumpSpeed_s, "JumpSpeed");
    getStaticParam(&mJumpDir_s, "JumpDir");
    getDynamicParam(&mIsJump_d, "IsJump");
}

void KokkoMoveWithJump::calc_() {
    KokkoMove::calc_();
}

}  // namespace uking::action

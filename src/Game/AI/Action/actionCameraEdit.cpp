#include "Game/AI/Action/actionCameraEdit.h"

namespace uking::action {

CameraEdit::CameraEdit(const InitArg& arg) : ActionEx(arg) {}

CameraEdit::~CameraEdit() = default;

bool CameraEdit::init_(sead::Heap* heap) {
    return ActionEx::init_(heap);
}

void CameraEdit::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionEx::enter_(params);
}

void CameraEdit::leave_() {
    ActionEx::leave_();
}

void CameraEdit::loadParams_() {
    getStaticParam(&mNormal_s, "Normal");
    getStaticParam(&mLockOn_s, "LockOn");
    getStaticParam(&mWall_s, "Wall");
    getStaticParam(&mNormalSubject_s, "NormalSubject");
    getStaticParam(&mBow_s, "Bow");
    getStaticParam(&mBowSquat_s, "BowSquat");
    getStaticParam(&mBowLockOn_s, "BowLockOn");
    // FIXME: CALL _ZNK4ksys3act2ai10ActionBase7getNameEv @ 0x7100d165fc
}

void CameraEdit::calc_() {
    ActionEx::calc_();
}

}  // namespace uking::action

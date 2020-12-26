#include "Game/AI/Action/actionCameraEventMovePos.h"

namespace uking::action {

CameraEventMovePos::CameraEventMovePos(const InitArg& arg) : CameraEventMovePosBase(arg) {}

CameraEventMovePos::~CameraEventMovePos() = default;

bool CameraEventMovePos::init_(sead::Heap* heap) {
    return CameraEventMovePosBase::init_(heap);
}

void CameraEventMovePos::enter_(ksys::act::ai::InlineParamPack* params) {
    CameraEventMovePosBase::enter_(params);
}

void CameraEventMovePos::leave_() {
    CameraEventMovePosBase::leave_();
}

void CameraEventMovePos::loadParams_() {
    getStaticParam(&mBowFlag_s, "BowFlag");
}

void CameraEventMovePos::calc_() {
    CameraEventMovePosBase::calc_();
}

}  // namespace uking::action

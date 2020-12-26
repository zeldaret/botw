#include "Game/AI/Action/actionCameraEventAnim.h"

namespace uking::action {

CameraEventAnim::CameraEventAnim(const InitArg& arg) : CameraEventAnimBase(arg) {}

CameraEventAnim::~CameraEventAnim() = default;

bool CameraEventAnim::init_(sead::Heap* heap) {
    return CameraEventAnimBase::init_(heap);
}

void CameraEventAnim::enter_(ksys::act::ai::InlineParamPack* params) {
    CameraEventAnimBase::enter_(params);
}

void CameraEventAnim::leave_() {
    CameraEventAnimBase::leave_();
}

void CameraEventAnim::loadParams_() {
    getStaticParam(&mBowFlag_s, "BowFlag");
}

void CameraEventAnim::calc_() {
    CameraEventAnimBase::calc_();
}

}  // namespace uking::action

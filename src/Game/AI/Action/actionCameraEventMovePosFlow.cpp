#include "Game/AI/Action/actionCameraEventMovePosFlow.h"

namespace uking::action {

CameraEventMovePosFlow::CameraEventMovePosFlow(const InitArg& arg) : CameraEventMovePosBase(arg) {}

CameraEventMovePosFlow::~CameraEventMovePosFlow() = default;

bool CameraEventMovePosFlow::init_(sead::Heap* heap) {
    return CameraEventMovePosBase::init_(heap);
}

void CameraEventMovePosFlow::enter_(ksys::act::ai::InlineParamPack* params) {
    CameraEventMovePosBase::enter_(params);
}

void CameraEventMovePosFlow::leave_() {
    CameraEventMovePosBase::leave_();
}

void CameraEventMovePosFlow::loadParams_() {
    getStaticParam(&mBowFlag_s, "BowFlag");
}

void CameraEventMovePosFlow::calc_() {
    CameraEventMovePosBase::calc_();
}

}  // namespace uking::action

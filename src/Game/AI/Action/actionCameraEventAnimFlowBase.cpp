#include "Game/AI/Action/actionCameraEventAnimFlowBase.h"

namespace uking::action {

CameraEventAnimFlowBase::CameraEventAnimFlowBase(const InitArg& arg) : CameraEventAnimBase(arg) {}

CameraEventAnimFlowBase::~CameraEventAnimFlowBase() = default;

bool CameraEventAnimFlowBase::init_(sead::Heap* heap) {
    return CameraEventAnimBase::init_(heap);
}

void CameraEventAnimFlowBase::enter_(ksys::act::ai::InlineParamPack* params) {
    CameraEventAnimBase::enter_(params);
}

void CameraEventAnimFlowBase::leave_() {
    CameraEventAnimBase::leave_();
}

void CameraEventAnimFlowBase::loadParams_() {
    getStaticParam(&mBowFlag_s, "BowFlag");
}

void CameraEventAnimFlowBase::calc_() {
    CameraEventAnimBase::calc_();
}

}  // namespace uking::action

#include "Game/AI/Action/actionCameraEventAnimFlow.h"

namespace uking::action {

CameraEventAnimFlow::CameraEventAnimFlow(const InitArg& arg) : CameraEventAnimFlowBase(arg) {}

CameraEventAnimFlow::~CameraEventAnimFlow() = default;

bool CameraEventAnimFlow::init_(sead::Heap* heap) {
    return CameraEventAnimFlowBase::init_(heap);
}

void CameraEventAnimFlow::enter_(ksys::act::ai::InlineParamPack* params) {
    CameraEventAnimFlowBase::enter_(params);
}

void CameraEventAnimFlow::leave_() {
    CameraEventAnimFlowBase::leave_();
}

void CameraEventAnimFlow::loadParams_() {
    getStaticParam(&mBowFlag_s, "BowFlag");
}

void CameraEventAnimFlow::calc_() {
    CameraEventAnimFlowBase::calc_();
}

}  // namespace uking::action

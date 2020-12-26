#include "Game/AI/Action/actionCameraEventAnimFlowAbs.h"

namespace uking::action {

CameraEventAnimFlowAbs::CameraEventAnimFlowAbs(const InitArg& arg) : CameraEventAnimFlowBase(arg) {}

CameraEventAnimFlowAbs::~CameraEventAnimFlowAbs() = default;

bool CameraEventAnimFlowAbs::init_(sead::Heap* heap) {
    return CameraEventAnimFlowBase::init_(heap);
}

void CameraEventAnimFlowAbs::enter_(ksys::act::ai::InlineParamPack* params) {
    CameraEventAnimFlowBase::enter_(params);
}

void CameraEventAnimFlowAbs::leave_() {
    CameraEventAnimFlowBase::leave_();
}

void CameraEventAnimFlowAbs::loadParams_() {
    getStaticParam(&mBowFlag_s, "BowFlag");
}

void CameraEventAnimFlowAbs::calc_() {
    CameraEventAnimFlowBase::calc_();
}

}  // namespace uking::action

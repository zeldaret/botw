#include "Game/AI/Action/actionCameraEventAnimFlowForMapTower.h"

namespace uking::action {

CameraEventAnimFlowForMapTower::CameraEventAnimFlowForMapTower(const InitArg& arg)
    : CameraEventAnimFlow(arg) {}

CameraEventAnimFlowForMapTower::~CameraEventAnimFlowForMapTower() = default;

bool CameraEventAnimFlowForMapTower::init_(sead::Heap* heap) {
    return CameraEventAnimFlow::init_(heap);
}

void CameraEventAnimFlowForMapTower::enter_(ksys::act::ai::InlineParamPack* params) {
    CameraEventAnimFlow::enter_(params);
}

void CameraEventAnimFlowForMapTower::leave_() {
    CameraEventAnimFlow::leave_();
}

void CameraEventAnimFlowForMapTower::loadParams_() {
    getStaticParam(&mBowFlag_s, "BowFlag");
}

void CameraEventAnimFlowForMapTower::calc_() {
    CameraEventAnimFlow::calc_();
}

}  // namespace uking::action

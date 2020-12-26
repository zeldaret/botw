#include "Game/AI/Action/actionCameraEventSavePoint.h"

namespace uking::action {

CameraEventSavePoint::CameraEventSavePoint(const InitArg& arg) : CameraAction(arg) {}

CameraEventSavePoint::~CameraEventSavePoint() = default;

bool CameraEventSavePoint::init_(sead::Heap* heap) {
    return CameraAction::init_(heap);
}

void CameraEventSavePoint::enter_(ksys::act::ai::InlineParamPack* params) {
    CameraAction::enter_(params);
}

void CameraEventSavePoint::leave_() {
    CameraAction::leave_();
}

void CameraEventSavePoint::loadParams_() {
    getStaticParam(&mBowFlag_s, "BowFlag");
}

void CameraEventSavePoint::calc_() {
    CameraAction::calc_();
}

}  // namespace uking::action

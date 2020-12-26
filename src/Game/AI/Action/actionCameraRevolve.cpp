#include "Game/AI/Action/actionCameraRevolve.h"

namespace uking::action {

CameraRevolve::CameraRevolve(const InitArg& arg) : CameraAction(arg) {}

CameraRevolve::~CameraRevolve() = default;

bool CameraRevolve::init_(sead::Heap* heap) {
    return CameraAction::init_(heap);
}

void CameraRevolve::enter_(ksys::act::ai::InlineParamPack* params) {
    CameraAction::enter_(params);
}

void CameraRevolve::leave_() {
    CameraAction::leave_();
}

void CameraRevolve::loadParams_() {
    getStaticParam(&mBowFlag_s, "BowFlag");
}

void CameraRevolve::calc_() {
    CameraAction::calc_();
}

}  // namespace uking::action

#include "Game/AI/Action/actionCameraAbyss.h"

namespace uking::action {

CameraAbyss::CameraAbyss(const InitArg& arg) : CameraAction(arg) {}

CameraAbyss::~CameraAbyss() = default;

bool CameraAbyss::init_(sead::Heap* heap) {
    return CameraAction::init_(heap);
}

void CameraAbyss::enter_(ksys::act::ai::InlineParamPack* params) {
    CameraAction::enter_(params);
}

void CameraAbyss::leave_() {
    CameraAction::leave_();
}

void CameraAbyss::loadParams_() {
    getStaticParam(&mBowFlag_s, "BowFlag");
}

void CameraAbyss::calc_() {
    CameraAction::calc_();
}

}  // namespace uking::action

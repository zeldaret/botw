#include "Game/AI/Action/actionCameraHorse.h"

namespace uking::action {

CameraHorse::CameraHorse(const InitArg& arg) : CameraAction(arg) {}

CameraHorse::~CameraHorse() = default;

bool CameraHorse::init_(sead::Heap* heap) {
    return CameraAction::init_(heap);
}

void CameraHorse::enter_(ksys::act::ai::InlineParamPack* params) {
    CameraAction::enter_(params);
}

void CameraHorse::leave_() {
    CameraAction::leave_();
}

void CameraHorse::loadParams_() {
    getStaticParam(&mBowFlag_s, "BowFlag");
}

void CameraHorse::calc_() {
    CameraAction::calc_();
}

}  // namespace uking::action

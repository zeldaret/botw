#include "Game/AI/Action/actionCameraAction.h"

namespace uking::action {

CameraAction::CameraAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

CameraAction::~CameraAction() = default;

bool CameraAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void CameraAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void CameraAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void CameraAction::loadParams_() {
    getStaticParam(&mBowFlag_s, "BowFlag");
}

void CameraAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

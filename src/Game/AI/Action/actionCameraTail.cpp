#include "Game/AI/Action/actionCameraTail.h"

namespace uking::action {

CameraTail::CameraTail(const InitArg& arg) : CameraAction(arg) {}

CameraTail::~CameraTail() = default;

bool CameraTail::init_(sead::Heap* heap) {
    return CameraAction::init_(heap);
}

void CameraTail::enter_(ksys::act::ai::InlineParamPack* params) {
    CameraAction::enter_(params);
}

void CameraTail::leave_() {
    CameraAction::leave_();
}

void CameraTail::loadParams_() {
    getStaticParam(&mBowFlag_s, "BowFlag");
}

void CameraTail::calc_() {
    CameraAction::calc_();
}

}  // namespace uking::action

#include "Game/AI/AI/aiCameraAI.h"

namespace uking::ai {

CameraAI::CameraAI(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

CameraAI::~CameraAI() = default;

bool CameraAI::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void CameraAI::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void CameraAI::leave_() {
    ksys::act::ai::Ai::leave_();
}

void CameraAI::loadParams_() {}

}  // namespace uking::ai

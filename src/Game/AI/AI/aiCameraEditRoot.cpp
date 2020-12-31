#include "Game/AI/AI/aiCameraEditRoot.h"

namespace uking::ai {

CameraEditRoot::CameraEditRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool CameraEditRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

}  // namespace uking::ai

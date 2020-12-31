#include "Game/AI/AI/aiViewfrustumCheckTagRoot.h"

namespace uking::ai {

ViewfrustumCheckTagRoot::ViewfrustumCheckTagRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ViewfrustumCheckTagRoot::~ViewfrustumCheckTagRoot() = default;

bool ViewfrustumCheckTagRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void ViewfrustumCheckTagRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void ViewfrustumCheckTagRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void ViewfrustumCheckTagRoot::loadParams_() {
    getMapUnitParam(&mAllwaysOnDisFromPlayer_m, "AllwaysOnDisFromPlayer");
    getMapUnitParam(&mAllwaysOnCamDir_m, "AllwaysOnCamDir");
}

}  // namespace uking::ai

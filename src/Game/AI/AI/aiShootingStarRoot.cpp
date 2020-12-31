#include "Game/AI/AI/aiShootingStarRoot.h"

namespace uking::ai {

ShootingStarRoot::ShootingStarRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ShootingStarRoot::~ShootingStarRoot() = default;

bool ShootingStarRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void ShootingStarRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void ShootingStarRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void ShootingStarRoot::loadParams_() {}

}  // namespace uking::ai

#include "Game/AI/AI/aiWholeDungeonRotateTag.h"

namespace uking::ai {

WholeDungeonRotateTag::WholeDungeonRotateTag(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WholeDungeonRotateTag::~WholeDungeonRotateTag() = default;

bool WholeDungeonRotateTag::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void WholeDungeonRotateTag::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void WholeDungeonRotateTag::leave_() {
    ksys::act::ai::Ai::leave_();
}

void WholeDungeonRotateTag::loadParams_() {
    getMapUnitParam(&mTiltAngle_m, "TiltAngle");
}

}  // namespace uking::ai

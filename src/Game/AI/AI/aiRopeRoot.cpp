#include "Game/AI/AI/aiRopeRoot.h"

namespace uking::ai {

RopeRoot::RopeRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

RopeRoot::~RopeRoot() = default;

bool RopeRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void RopeRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void RopeRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void RopeRoot::loadParams_() {
    getMapUnitParam(&mRopeFlag_m, "RopeFlag");
    getMapUnitParam(&mRopeAlwaysUpdateRigidParam_m, "RopeAlwaysUpdateRigidParam");
}

}  // namespace uking::ai

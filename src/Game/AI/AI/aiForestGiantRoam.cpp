#include "Game/AI/AI/aiForestGiantRoam.h"

namespace uking::ai {

ForestGiantRoam::ForestGiantRoam(const InitArg& arg) : BokoblinRoam(arg) {}

ForestGiantRoam::~ForestGiantRoam() = default;

bool ForestGiantRoam::init_(sead::Heap* heap) {
    return BokoblinRoam::init_(heap);
}

void ForestGiantRoam::enter_(ksys::act::ai::InlineParamPack* params) {
    BokoblinRoam::enter_(params);
}

void ForestGiantRoam::leave_() {
    BokoblinRoam::leave_();
}

void ForestGiantRoam::loadParams_() {
    BokoblinRoam::loadParams_();
    getStaticParam(&mReturnHomeDist_s, "ReturnHomeDist");
}

}  // namespace uking::ai

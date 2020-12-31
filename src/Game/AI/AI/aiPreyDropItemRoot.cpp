#include "Game/AI/AI/aiPreyDropItemRoot.h"

namespace uking::ai {

PreyDropItemRoot::PreyDropItemRoot(const InitArg& arg) : PreyRoot(arg) {}

PreyDropItemRoot::~PreyDropItemRoot() = default;

bool PreyDropItemRoot::init_(sead::Heap* heap) {
    return PreyRoot::init_(heap);
}

void PreyDropItemRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    PreyRoot::enter_(params);
}

void PreyDropItemRoot::leave_() {
    PreyRoot::leave_();
}

void PreyDropItemRoot::loadParams_() {
    PreyRoot::loadParams_();
    getStaticParam(&mMaxDropCount_s, "MaxDropCount");
    getStaticParam(&mForceDeleteInterval_s, "ForceDeleteInterval");
    getStaticParam(&mInitialVelocity_s, "InitialVelocity");
}

}  // namespace uking::ai

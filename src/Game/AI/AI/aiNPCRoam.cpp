#include "Game/AI/AI/aiNPCRoam.h"

namespace uking::ai {

NPCRoam::NPCRoam(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

NPCRoam::~NPCRoam() = default;

bool NPCRoam::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void NPCRoam::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void NPCRoam::leave_() {
    ksys::act::ai::Ai::leave_();
}

void NPCRoam::loadParams_() {
    getStaticParam(&mWaitFrame_s, "WaitFrame");
    getStaticParam(&mWaitFrameRand_s, "WaitFrameRand");
    getStaticParam(&mRadius_s, "Radius");
    getStaticParam(&mWalkDistMin_s, "WalkDistMin");
    getStaticParam(&mWalkDistMax_s, "WalkDistMax");
    getDynamicParam(&mWaitASName_d, "WaitASName");
    getDynamicParam(&mBasisPos_d, "BasisPos");
}

}  // namespace uking::ai

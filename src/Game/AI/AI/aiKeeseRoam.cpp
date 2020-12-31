#include "Game/AI/AI/aiKeeseRoam.h"

namespace uking::ai {

KeeseRoam::KeeseRoam(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

KeeseRoam::~KeeseRoam() = default;

bool KeeseRoam::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void KeeseRoam::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void KeeseRoam::leave_() {
    ksys::act::ai::Ai::leave_();
}

void KeeseRoam::loadParams_() {
    getStaticParam(&mMinOffsetY_s, "MinOffsetY");
    getStaticParam(&mMaxOffsetY_s, "MaxOffsetY");
    getStaticParam(&mRoamRadius_s, "RoamRadius");
    getStaticParam(&mMinMoveDist_s, "MinMoveDist");
    getStaticParam(&mMaxMoveDist_s, "MaxMoveDist");
    getStaticParam(&mNoWaitRatio_s, "NoWaitRatio");
    getDynamicParam(&mCentralPos_d, "CentralPos");
}

}  // namespace uking::ai

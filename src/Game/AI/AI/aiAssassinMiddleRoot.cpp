#include "Game/AI/AI/aiAssassinMiddleRoot.h"

namespace uking::ai {

AssassinMiddleRoot::AssassinMiddleRoot(const InitArg& arg) : EnemyRoot(arg) {}

AssassinMiddleRoot::~AssassinMiddleRoot() = default;

bool AssassinMiddleRoot::init_(sead::Heap* heap) {
    return EnemyRoot::init_(heap);
}

void AssassinMiddleRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyRoot::enter_(params);
}

void AssassinMiddleRoot::leave_() {
    EnemyRoot::leave_();
}

void AssassinMiddleRoot::loadParams_() {
    EnemyRoot::loadParams_();
    getStaticParam(&mPodModelUnitIdx_s, "PodModelUnitIdx");
    getStaticParam(&mPodNodeName_s, "PodNodeName");
    getStaticParam(&mSheathOffset_s, "SheathOffset");
    getStaticParam(&mMagicUsePartsName_s, "MagicUsePartsName");
}

}  // namespace uking::ai

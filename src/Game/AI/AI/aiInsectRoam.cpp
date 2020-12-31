#include "Game/AI/AI/aiInsectRoam.h"

namespace uking::ai {

InsectRoam::InsectRoam(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

InsectRoam::~InsectRoam() = default;

bool InsectRoam::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void InsectRoam::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void InsectRoam::leave_() {
    ksys::act::ai::Ai::leave_();
}

void InsectRoam::loadParams_() {
    getStaticParam(&mTerritoryRadius_s, "TerritoryRadius");
    getStaticParam(&mTerritoryRadiusRnd_s, "TerritoryRadiusRnd");
    getStaticParam(&mMoveDist_s, "MoveDist");
    getStaticParam(&mMoveSpeed_s, "MoveSpeed");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai

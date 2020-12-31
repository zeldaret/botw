#include "Game/AI/AI/aiGuardianMiniViewWait.h"

namespace uking::ai {

GuardianMiniViewWait::GuardianMiniViewWait(const InitArg& arg) : ViewWait(arg) {}

GuardianMiniViewWait::~GuardianMiniViewWait() = default;

void GuardianMiniViewWait::enter_(ksys::act::ai::InlineParamPack* params) {
    ViewWait::enter_(params);
}

void GuardianMiniViewWait::leave_() {
    ViewWait::leave_();
}

void GuardianMiniViewWait::loadParams_() {
    ViewWait::loadParams_();
    getStaticParam(&mASSlotRight_s, "ASSlotRight");
    getStaticParam(&mASSlotLeft_s, "ASSlotLeft");
    getStaticParam(&mASSlotBack_s, "ASSlotBack");
    getStaticParam(&mRootNodeName_s, "RootNodeName");
    getStaticParam(&mArm1NodeName_s, "Arm1NodeName");
    getStaticParam(&mArm2NodeName_s, "Arm2NodeName");
    getStaticParam(&mArm3NodeName_s, "Arm3NodeName");
    getStaticParam(&mIsPartialBind_s, "IsPartialBind");
}

}  // namespace uking::ai

#include "Game/AI/AI/aiGolemReaction.h"

namespace uking::ai {

GolemReaction::GolemReaction(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GolemReaction::~GolemReaction() = default;

bool GolemReaction::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GolemReaction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void GolemReaction::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GolemReaction::loadParams_() {
    getStaticParam(&mClimbLimitTime_s, "ClimbLimitTime");
    getStaticParam(&mClampRestClimbTime_s, "ClampRestClimbTime");
    getStaticParam(&mIgnoreBombTime_s, "IgnoreBombTime");
    getStaticParam(&mRightArmTgtBodyName_s, "RightArmTgtBodyName");
    getStaticParam(&mLeftArmTgtBodyName_s, "LeftArmTgtBodyName");
    getStaticParam(&mBreakArmLXLinkKey_s, "BreakArmLXLinkKey");
    getStaticParam(&mBodyArmLName1_s, "BodyArmLName1");
    getStaticParam(&mBodyArmLName2_s, "BodyArmLName2");
    getStaticParam(&mChmArmLName_s, "ChmArmLName");
    getStaticParam(&mArmLMaterialName_s, "ArmLMaterialName");
    getStaticParam(&mBreakArmRXLinkKey_s, "BreakArmRXLinkKey");
    getStaticParam(&mBodyArmRName1_s, "BodyArmRName1");
    getStaticParam(&mBodyArmRName2_s, "BodyArmRName2");
    getStaticParam(&mChmArmRName_s, "ChmArmRName");
    getStaticParam(&mArmRMaterialName_s, "ArmRMaterialName");
    getAITreeVariable(&mGolemClimbedTime_a, "GolemClimbedTime");
    getAITreeVariable(&mGolemChemicalController_a, "GolemChemicalController");
}

}  // namespace uking::ai

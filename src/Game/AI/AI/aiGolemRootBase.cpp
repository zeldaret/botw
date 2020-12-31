#include "Game/AI/AI/aiGolemRootBase.h"

namespace uking::ai {

GolemRootBase::GolemRootBase(const InitArg& arg) : EnemyRoot(arg) {}

GolemRootBase::~GolemRootBase() = default;

bool GolemRootBase::init_(sead::Heap* heap) {
    return EnemyRoot::init_(heap);
}

void GolemRootBase::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyRoot::enter_(params);
}

void GolemRootBase::leave_() {
    EnemyRoot::leave_();
}

void GolemRootBase::loadParams_() {
    EnemyRoot::loadParams_();
    getStaticParam(&mShaderASTargetBone_s, "ShaderASTargetBone");
    getStaticParam(&mBodyShaderSeqBank_s, "BodyShaderSeqBank");
    getStaticParam(&mArmRShaderSeqBank_s, "ArmRShaderSeqBank");
    getStaticParam(&mArmLShaderSeqBank_s, "ArmLShaderSeqBank");
    getStaticParam(&mUpperArmL_PartsKey_s, "UpperArmL_PartsKey");
    getStaticParam(&mLowerArmL_PartsKey_s, "LowerArmL_PartsKey");
    getStaticParam(&mUpperArmR_PartsKey_s, "UpperArmR_PartsKey");
    getStaticParam(&mLowerArmR_PartsKey_s, "LowerArmR_PartsKey");
    getStaticParam(&mChemicalFieldKey_s, "ChemicalFieldKey");
    getStaticParam(&mBodyDeactiveAS_s, "BodyDeactiveAS");
    getStaticParam(&mArmRDeactiveAS_s, "ArmRDeactiveAS");
    getStaticParam(&mArmLDeactiveAS_s, "ArmLDeactiveAS");
    getStaticParam(&mBodyActiveAS_s, "BodyActiveAS");
    getStaticParam(&mArmRActiveAS_s, "ArmRActiveAS");
    getStaticParam(&mArmLActiveAS_s, "ArmLActiveAS");
    getStaticParam(&mBodyMimicAS_s, "BodyMimicAS");
    getStaticParam(&mArmRMimicAS_s, "ArmRMimicAS");
    getStaticParam(&mArmLMimicAS_s, "ArmLMimicAS");
    getMapUnitParam(&mGolemTextureName_m, "GolemTextureName");
    getAITreeVariable(&mGolemChemicalController_a, "GolemChemicalController");
}

}  // namespace uking::ai

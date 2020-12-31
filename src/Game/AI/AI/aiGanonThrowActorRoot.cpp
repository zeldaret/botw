#include "Game/AI/AI/aiGanonThrowActorRoot.h"

namespace uking::ai {

GanonThrowActorRoot::GanonThrowActorRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GanonThrowActorRoot::~GanonThrowActorRoot() = default;

bool GanonThrowActorRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GanonThrowActorRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void GanonThrowActorRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GanonThrowActorRoot::loadParams_() {
    getStaticParam(&mAttackDamage_s, "AttackDamage");
    getStaticParam(&mAtMinDamage_s, "AtMinDamage");
    getStaticParam(&mAddAtackPower_s, "AddAtackPower");
    getStaticParam(&mIsThrowQuick_s, "IsThrowQuick");
    getStaticParam(&mIsWaitBulletDelete_s, "IsWaitBulletDelete");
    getStaticParam(&mIsSetSystemGroupHandler_s, "IsSetSystemGroupHandler");
    getStaticParam(&mIsSendDeleteMessageAtLeave_s, "IsSendDeleteMessageAtLeave");
    getStaticParam(&mThrowActorName_s, "ThrowActorName");
    getStaticParam(&mRegisterPartsName_s, "RegisterPartsName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mViewPos_d, "ViewPos");
}

}  // namespace uking::ai

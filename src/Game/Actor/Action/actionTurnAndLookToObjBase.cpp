#include "Game/Actor/Action/actionTurnAndLookToObjBase.h"

namespace uking::action {

TurnAndLookToObjBase::TurnAndLookToObjBase(const InitArg& arg) : PlayerAction(arg) {}

TurnAndLookToObjBase::~TurnAndLookToObjBase() = default;

bool TurnAndLookToObjBase::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

void TurnAndLookToObjBase::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void TurnAndLookToObjBase::leave_() {
    PlayerAction::leave_();
}

void TurnAndLookToObjBase::loadParams_() {
    getDynamicParam(&mObjectId_d, "ObjectId");
    getDynamicParam(&mFaceId_d, "FaceId");
    getDynamicParam(&mTurnDirection_d, "TurnDirection");
    getDynamicParam(&mIsValid_d, "IsValid");
    getDynamicParam(&mActorName_d, "ActorName");
    getDynamicParam(&mUniqueName_d, "UniqueName");
    getDynamicParam(&mPosOffset_d, "PosOffset");
    getDynamicParam(&mTurnPosition_d, "TurnPosition");
}

void TurnAndLookToObjBase::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action

#pragma once

#include "Game/AI/Action/actionPlayerAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class LookAtObjectBase : public PlayerAction {
    SEAD_RTTI_OVERRIDE(LookAtObjectBase, PlayerAction)
public:
    explicit LookAtObjectBase(const InitArg& arg);
    ~LookAtObjectBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x78
    int* mObjectId_d{};
    // dynamic_param at offset 0x80
    int* mFaceId_d{};
    // dynamic_param at offset 0x88
    float* mTurnDirection_d{};
    // dynamic_param at offset 0x90
    bool* mIsValid_d{};
    // dynamic_param at offset 0x98
    sead::SafeString mActorName_d{};
    // dynamic_param at offset 0xa8
    sead::SafeString mUniqueName_d{};
    // dynamic_param at offset 0xb8
    sead::Vector3f* mPosOffset_d{};
    // dynamic_param at offset 0xc0
    sead::Vector3f* mTurnPosition_d{};
};

}  // namespace uking::action

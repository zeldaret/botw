#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkStalEnemyGrabOwnPart : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForkStalEnemyGrabOwnPart, ksys::act::ai::Action)
public:
    explicit ForkStalEnemyGrabOwnPart(const InitArg& arg);
    ~ForkStalEnemyGrabOwnPart() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mSeqBank_s{};
    // static_param at offset 0x28
    const int* mTargetBone_s{};
    // static_param at offset 0x30
    sead::SafeString mBoneName_s{};
    // dynamic_param at offset 0x40
    int* mPartIndex_d{};
};

}  // namespace uking::action

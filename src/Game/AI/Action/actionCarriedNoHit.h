#pragma once

#include "Game/AI/Action/actionCarried.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CarriedNoHit : public Carried {
    SEAD_RTTI_OVERRIDE(CarriedNoHit, Carried)
public:
    explicit CarriedNoHit(const InitArg& arg);
    ~CarriedNoHit() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mBindType_s{};
    // static_param at offset 0x28
    const float* mFailDistance_s{};
    // static_param at offset 0x30
    const bool* mIsCreateItem_s{};
    // static_param at offset 0x38
    const bool* mIsRecoverCharCtrlAxis_s{};
    // static_param at offset 0x40
    const bool* mIsUseConstraint_s{};
    // static_param at offset 0x48
    const bool* mIsOnBaseLink_s{};
    // static_param at offset 0x50
    const bool* mIsChangeable_s{};
    // static_param at offset 0x58
    sead::SafeString mHoldOnXLinkKey_s{};
};

}  // namespace uking::action

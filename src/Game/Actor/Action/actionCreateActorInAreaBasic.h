#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CreateActorInAreaBasic : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(CreateActorInAreaBasic, ksys::act::ai::Action)
public:
    explicit CreateActorInAreaBasic(const InitArg& arg);
    ~CreateActorInAreaBasic() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mCreateBasePosNum_s{};
    // static_param at offset 0x28
    const float* mCreateNewActorIntervalFirst_s{};
    // static_param at offset 0x30
    const float* mCreateNewActorInterval_s{};
    // static_param at offset 0x38
    const float* mCreateContinueTime_s{};
    // static_param at offset 0x40
    const float* mAfterWaitTime_s{};
    // static_param at offset 0x48
    const bool* mIsAllowCreateNoSafeArea_s{};
    // static_param at offset 0x50
    sead::SafeString mCreateActorName_s{};
    // static_param at offset 0x60
    const sead::Vector3f* mBaseOffset_s{};
    // static_param at offset 0x68
    const sead::Vector3f* mCreateRandArea_s{};
    // static_param at offset 0x70
    const sead::Vector3f* mProhibitedCreateArea_s{};
};

}  // namespace uking::action

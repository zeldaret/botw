#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class DoorRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(DoorRoot, ksys::act::ai::Ai)
public:
    explicit DoorRoot(const InitArg& arg);
    ~DoorRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mCloseWaitFrame_s{};
    // static_param at offset 0x40
    const bool* mIsCheckBack_s{};
    // static_param at offset 0x48
    sead::SafeString mOpen_L_AS_s{};
    // static_param at offset 0x58
    sead::SafeString mOpen_R_AS_s{};
    // static_param at offset 0x68
    sead::SafeString mClose_L_AS_s{};
    // static_param at offset 0x78
    sead::SafeString mClose_R_AS_s{};
    // map_unit_param at offset 0x88
    sead::SafeString mNpcCanOpenFlag_m{};
    // aitree_variable at offset 0x98
    bool* mIsOpenDoor_a{};
    // aitree_variable at offset 0xa0
    bool* mIsOpenToInside_a{};
};

}  // namespace uking::ai

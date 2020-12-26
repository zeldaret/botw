#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkAnimalASPlay : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForkAnimalASPlay, ksys::act::ai::Action)
public:
    explicit ForkAnimalASPlay(const InitArg& arg);
    ~ForkAnimalASPlay() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mAllowChangeableFrame_s{};
    // static_param at offset 0x28
    const int* mSelectNextGearType_s{};
    // static_param at offset 0x30
    const int* mSelectNextGear_s{};
    // static_param at offset 0x38
    const bool* mIsIgnoreSameAS_s{};
    // static_param at offset 0x40
    sead::SafeString mASKeyName_s{};
};

}  // namespace uking::action

#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class HideHover : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(HideHover, ksys::act::ai::Action)
public:
    explicit HideHover(const InitArg& arg);
    ~HideHover() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mTimer_s{};
    // static_param at offset 0x28
    const bool* mIsKeepLifeGage_s{};
    // static_param at offset 0x30
    const bool* mIsChangeable_s{};
    // static_param at offset 0x38
    sead::SafeString mEffectName_s{};
};

}  // namespace uking::action

#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class HorseDie : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(HorseDie, ksys::act::ai::Action)
public:
    explicit HorseDie(const InitArg& arg);
    ~HorseDie() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mDyingFrames_s{};
    // static_param at offset 0x28
    const bool* mCheckIfStable_s{};
    // static_param at offset 0x30
    sead::SafeString mASName_s{};
};

}  // namespace uking::action

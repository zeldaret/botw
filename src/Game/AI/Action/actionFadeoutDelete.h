#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class FadeoutDelete : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(FadeoutDelete, ksys::act::ai::Action)
public:
    explicit FadeoutDelete(const InitArg& arg);
    ~FadeoutDelete() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mFadeoutTime_s{};
    // static_param at offset 0x28
    const int* mDeleteType_s{};
};

}  // namespace uking::action

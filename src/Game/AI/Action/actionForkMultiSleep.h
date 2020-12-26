#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkMultiSleep : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForkMultiSleep, ksys::act::ai::Action)
public:
    explicit ForkMultiSleep(const InitArg& arg);
    ~ForkMultiSleep() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mNum_s{};
    // static_param at offset 0x28
    sead::SafeString mPartsBaseName_s{};
};

}  // namespace uking::action

#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AscendingCurrent : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(AscendingCurrent, ksys::act::ai::Action)
public:
    explicit AscendingCurrent(const InitArg& arg);
    ~AscendingCurrent() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mWindSpeed_s{};
};

}  // namespace uking::action

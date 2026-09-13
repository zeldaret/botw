#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ThrownSpear : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ThrownSpear, ksys::act::ai::Action)
public:
    explicit ThrownSpear(const InitArg& arg);
    ~ThrownSpear() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mRotSpeedZ_s{};
};

}  // namespace uking::action

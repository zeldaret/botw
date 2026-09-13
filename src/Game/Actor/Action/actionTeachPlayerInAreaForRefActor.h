#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class TeachPlayerInAreaForRefActor : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(TeachPlayerInAreaForRefActor, ksys::act::ai::Action)
public:
    explicit TeachPlayerInAreaForRefActor(const InitArg& arg);
    ~TeachPlayerInAreaForRefActor() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mNextTimer_s{};
};

}  // namespace uking::action

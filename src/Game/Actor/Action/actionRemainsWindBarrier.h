#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class RemainsWindBarrier : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(RemainsWindBarrier, ksys::act::ai::Action)
public:
    explicit RemainsWindBarrier(const InitArg& arg);
    ~RemainsWindBarrier() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action

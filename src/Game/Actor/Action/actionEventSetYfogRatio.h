#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EventSetYfogRatio : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(EventSetYfogRatio, ksys::act::ai::Action)
public:
    explicit EventSetYfogRatio(const InitArg& arg);
    ~EventSetYfogRatio() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    float* mYfogRatio_d{};
};

}  // namespace uking::action

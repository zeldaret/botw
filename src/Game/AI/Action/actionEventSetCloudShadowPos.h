#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EventSetCloudShadowPos : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(EventSetCloudShadowPos, ksys::act::ai::Action)
public:
    explicit EventSetCloudShadowPos(const InitArg& arg);
    ~EventSetCloudShadowPos() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    float* msetPos_x_d{};
    // dynamic_param at offset 0x28
    float* msetPos_y_d{};
};

}  // namespace uking::action

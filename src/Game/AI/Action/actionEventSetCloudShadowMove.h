#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EventSetCloudShadowMove : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(EventSetCloudShadowMove, ksys::act::ai::Action)
public:
    explicit EventSetCloudShadowMove(const InitArg& arg);
    ~EventSetCloudShadowMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    float* msetSpeed_x_d{};
    // dynamic_param at offset 0x28
    float* msetSpeed_y_d{};
};

}  // namespace uking::action
